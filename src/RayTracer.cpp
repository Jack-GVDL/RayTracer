#include <limits>
#include "../inc/RayTracer.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
Vec3f RayTracer::trace(const Camera *camera, double x, double y, int depth) const {
	Ray ray = camera->getRay(x, y);
	return trace(&ray, depth);
}


Vec3f RayTracer::trace(const Ray *ray, int depth) const {
	// init scatter record
	ScatterRecord scatter_record;
	scatter_record.parent		= nullptr;
	scatter_record.scene		= scene;
	scatter_record.scatter		= scatter;
	scatter_record.depth		= depth;
	scatter_record.ray			= *ray;

	// TODO: currently not to use cuda so recursion is ok
	return trace(&scatter_record);
}


// TODO: return nothing is still ok, as the result is already in the ScatterRecord *record
Vec3f RayTracer::trace(ScatterRecord *record) const {
	// depth limit check
	if (record->depth <= 0) return Vec3f();

	// first check if scatter exist or not
	if (record->scatter == nullptr) return Vec3f();

	// first check if hit something or not
	// HitRecord hit_record;
	if (scene->hit(&(record->ray), 0.0, std::numeric_limits<float>::max(), &(record->hit_record)))	record->is_hit = true;
	else																	record->is_hit = false;

	// foreach scatter, check if needed to fire a new ray or not
	int		loop_count		= 0;
	bool	is_loop_started	= false;

	for (auto *scatter : record->scatter->scatter_list) {

		// check if there is no threshold left for parent
		if (record->thresh.isZero()) break;

		// for equal split
		loop_count		= 0;
		is_loop_started	= false;
		SCATTER_LOOP:

		ScatterRecord scatter_record;
		ScatterState state = scatter->scatter(&scatter_record, record);

		// nothing to deal with current scatter
		// skip it
		if (state == SCATTER_NONE) {
			continue;
		}

		// add result intensity to parent intensity immediate
		if (state == SCATTER_YIELD) {
			const Vec3f &result = scatter_record.intensity.clamp(0, 1);
			record->intensity	+= result * record->thresh;
			break;
		}

		if (state == SCATTER_EQUAL_SPLIT) {
			if (!is_loop_started) {
				is_loop_started	= true;
				loop_count		= scatter->loop_count;
			}

			const Vec3f &result = trace(&scatter_record).clamp(0, 1);
			record->intensity	+= result;

			loop_count--;
			if (loop_count != 0) goto SCATTER_LOOP;
			record->thresh = 0;
			break;
		}

		// if (state == SCATTER_NEXT)
		// fire a new ray and obtain the result
		const Vec3f &result	= trace(&scatter_record).clamp(0, 1);
		record->intensity	+= result;

	}

	return record->intensity;
}


// Static Function Implementation
// ...
