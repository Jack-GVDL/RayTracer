#include <limits>
#include "../inc/RayTracer_SceneObject_Hitable.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
bool SceneObject_Hitable::hit(const Ray *ray, HitRecord *record) const {
	return hit(ray, 0.0, std::numeric_limits<float>::max(), record);
}


bool SceneObject_Hitable::hit(const Ray *ray, float t_max, HitRecord *record) const {
	return hit(ray, 0.0, t_max, record);
}


bool SceneObject_HitableList::hit(const Ray *ray, float t_min, float t_max, HitRecord *record) const {
	HitRecord	temp_record;
	bool		is_hit			= false;
	double		closest			= t_max;

	for (int i = 0; i < (int)(hitable_list.size()); i++) {
		if (!hitable_list[i]->hit(ray, t_min, closest, &temp_record)) continue;

		is_hit	= true;
		closest	= temp_record.distance;
		*record = temp_record;  // TODO: not sure if this can be copy constructor or not
	}

	return is_hit;
}


bool SceneObject_HitableList::addHitable(SceneObject_Hitable *hitable) {
	hitable_list.push_back(hitable);
	addChild((SceneElement*)hitable);
	return true;
}


// TODO: not yet completed
bool SceneObject_HitableList::rmHitable(SceneObject_Hitable *hitable) {
	return false;
}


// Static Function Implementation
// ...
