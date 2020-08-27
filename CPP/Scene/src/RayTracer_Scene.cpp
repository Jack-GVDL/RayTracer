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


// TODO: missing uniqueness checking
bool Scene::addAmbientLight(SceneObject_Light *light) {
	ambient_list.push_back(light);
	return true;
}


// TODO: not yet completed
bool Scene::rmAmbientLight(SceneObject_Light *light) {
	return false;
}


Vec3f Scene::getAmbientIntensity() const {
	Vec3f result = Vec3f(0);
	for (auto *light : ambient_list) result += light->getColor(Vec3f());
	return result;
}



bool Scene::hit(RecordHit *record) const {
	RecordHit	temp_record;
	bool		is_hit			= false;
	fp_t		closest			= std::numeric_limits<fp_t>::max();

	// set ray
	temp_record.ray = record->ray;

	// search for hitable in child
	for (auto *hitable : hitable_list) {
		if (!hitable->hit(&temp_record, 0.0, closest)) continue;
		// if (temp_record.distance > closest) continue;

		is_hit			= true;
		closest			= temp_record.distance;
		*record			= temp_record;
	}

	return is_hit;
}


// Static Function Implementation
// ...
