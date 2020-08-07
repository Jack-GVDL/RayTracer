#include <algorithm>
#include "../inc/RayTracer_SceneObject_Hitable_AABB.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
// TODO: missing uniqueness check
bool Hitable_AABB::addHitable(SceneObject_Hitable *hitable) {
	// add to list
	hitable_list.push_back(hitable);
	
	// update bounding box
	for (int i = 0; i < 3; i++) {
		bounding_min[i]	= std::min<double>(bounding_min[i], hitable->bounding_min[i]);
		bounding_max[i]	= std::max<double>(bounding_max[i], hitable->bounding_max[i]);
	}
	
	return true;
}


// TODO: not yet completed
bool Hitable_AABB::rmHitable(SceneObject_Hitable *hitable) {
	// rm from list
	// ...

	// update bounding box
	// need to go through for all child bounding box
	// ...

	return false;
}


// only return hit child and never return self
bool Hitable_AABB::hit(RecordHit *record, double t_min, double t_max) const {
	// check if hit self bounding box
	const Vec3f	ray_pos	= record->ray.getPosition();
	const Vec3f	ray_dir	= record->ray.getDirection();

	for (int i = 0; i < 3; i++) {

		double	inv_d	= 1.0 / ray_dir[i];
		double	t0		= (bounding_min[i] - ray_pos[i]) * inv_d;
		double	t1		= (bounding_max[i] - ray_pos[i]) * inv_d;

		if (inv_d < 0.0) std::swap(t0, t1);
		double temp_min	= std::min<double>(t0, t_min);
		double temp_max	= std::max<double>(t1, t_max);

		if (temp_max <= temp_min) return false;
	}

	// check child
	RecordHit	temp_record;
	bool		is_hit			= false;
	double		closest			= t_max;

	// set ray
	temp_record.ray = record->ray;

	// search for hit in child
	for (auto *hitable : hitable_list) {
		if (!hitable->hit(&temp_record, t_min, closest)) continue;

		is_hit		= true;
		closest		= temp_record.distance;
		*record		= temp_record;
	}

	// there must be a hit
	return true;
}


// Static Function Implementation
// ...
