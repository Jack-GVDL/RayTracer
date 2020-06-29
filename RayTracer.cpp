#include "RayTracer.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
Vec3f RayTracer::trace(const Camera *camera, int x, int y, int depth) const {
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
	scatter_record.thresh		= Vec3f(1.0, 1.0, 1.0);
	scatter_record.intensity	= Vec3f(0.0, 0.0, 0.0);

	// TODO: currently not to use cuda so recursion is ok
	return trace(&scatter_record);
}


// TODO: return nothing is still ok, as the result is already in the ScatterRecord *record
Vec3f RayTracer::trace(ScatterRecord *record) const {
	// first check if hit something or not
	HitRecord hit_record;
	if (scene->hit(&(record->ray), 0.0, MAXFLOAT, &hit_record))	record->is_hit = true;
	else														record->is_hit = false;
	
	// foreach scatter, check if needed to fire a new ray or not
	for (auto *scatter : record->scatter->scatter_list) {
		
		ScatterRecord scatter_record;
		ScatterState state = scatter->scatter(&scatter_record, record);

		// nothing to deal with current scatter
		// skip it
		if (state == SCATTER_NONE) {
			continue;
		}

		// add result intensity to parent intensity immediate
		if (state == SCATTER_YIELD) {
			const Vec3f &result = scatter_record.intensity;
			record->intensity	= result * scatter_record.thresh;
			continue;
		}

		// if (state == SCATTER_NEXT)
		// fire a new ray and obtain the result
		const Vec3f &result	= trace(&scatter_record);
		record->intensity	+= result * scatter_record.thresh;
	}

	return record->intensity;
}


// Static Function Implementation
// ...
