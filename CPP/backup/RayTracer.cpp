#include <limits>
#include "../inc/RayTracer.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
bool RayTracer::addScatter_notHit(Scatter *scatter) {
	scatter_not_hit_list.push_back(scatter);
	return true;
}


// TODO: not yet completed
bool RayTracer::rmScatter_notHit(Scatter *scatter) {
	return false;
}


Vec3f RayTracer::trace(const Camera *camera, double x, double y, int depth) const {
	Ray ray = camera->getRay(x, y);
	return trace(&ray, depth);
}


Vec3f RayTracer::trace(const Ray *ray, int depth) const {
	// init scatter record
	RecordScatter scatter_record;
	scatter_record.parent		= nullptr;
	scatter_record.scene		= scene;
	scatter_record.scatter		= nullptr;
	scatter_record.depth		= depth;

	scatter_record.record_hit.ray = *ray;

	// TODO: use cuda in future
	return trace(&scatter_record);
}


// TODO: return nothing is still ok, as the result is already in the ScatterRecord *record
Vec3f RayTracer::trace(RecordScatter *record) const {
	// depth limit check
	if (record->depth <= 0)			return Vec3f();

	// first check if scatter exist or not
	if (record->scatter == nullptr)	return Vec3f();

	// first check if hit something or nothing
	// if hit, use scatter list in hitted object material
	// else, use scatter list in scatter_not_hit
	record->is_hit = scene->hit(&(record->record_hit));
	
	const std::vector<Scatter*>	*scatter_list;
	if (record->is_hit) {
		const Material *material	= &(record->record_hit.object->material);
		scatter_list				= &(material->scatter_list);

	} else {
		scatter_list				= &(scatter_not_hit_list);

	}

	// foreach scatter, check if needed to fire a new ray or not
	int		loop_count		= 0;
	bool	is_loop_started	= false;

	for (auto *scatter : *scatter_list) {

		// check if there is no threshold left for parent
		if (record->threshold.isZero()) break;

		// for equal split
		loop_count		= 0;
		is_loop_started	= false;
		SCATTER_LOOP:

		RecordScatter scatter_record;
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

		if (state == SCATTER_SPLIT) {
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
