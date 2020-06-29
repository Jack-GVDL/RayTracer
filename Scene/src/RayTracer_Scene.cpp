#include "../inc/RayTracer_Scene.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// TODO: missing uniqueness checking
bool Scene::addHitable(SceneObject_Hitable *hitable) {
	hitable_list.push_back(hitable);
	return true;
}


// TODO: not yet completed
bool Scene::rmHitable(SceneObject_Hitable *hitable) {
	return false;
}


// TODO: missing uniqueness checking
bool Scene::addLight(SceneObject_Light *light) {
	light_list.push_back(light);
	return true;
}


// TODO: not yet completed
bool Scene::rmLight(SceneObject_Light *light) {
	return false;
}


bool Scene::hit(const Ray *ray, float t_min, float t_max, HitRecord *record) const {
	HitRecord	temp_record;
	bool		is_hit			= false;
	double		closest			= t_max;

	for (auto *hitable : hitable_list) {
		if (!hitable->hit(ray, t_min, closest, &temp_record)) continue;

		is_hit	= true;
		closest	= temp_record.distance;
		*record	= temp_record;
	}

	return is_hit;
}


// Static Function Implementation
// ...
