#include "../inc/RayTracer_Scene.cuh"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// TODO: missing uniqueness checking
__device__ error_t Scene::addHitable(SceneObject_Hitable *hitable) {
	hitable_list.push_back(hitable);
	return ERROR_NO;
}


// TODO: not yet completed
__device__ error_t Scene::rmHitable(SceneObject_Hitable *hitable) {
	return ERROR_ANY;
}


// TODO: missing uniqueness checking
__device__ error_t Scene::addLight(SceneObject_Light *light) {
	light_list.push_back(light);
	return ERROR_NO;
}


// TODO: not yet completed
__device__ error_t Scene::rmLight(SceneObject_Light *light) {
	return ERROR_ANY;
}


// TODO: missing uniqueness checking
__device__ error_t Scene::addAmbientLight(SceneObject_Light *light) {
	ambient_list.push_back(light);
	return ERROR_NO;
}


// TODO: not yet completed
__device__ error_t Scene::rmAmbientLight(SceneObject_Light *light) {
	return ERROR_ANY;
}


__device__ Vec3f Scene::getAmbientIntensity() const {
	Vec3f result = Vec3f(0);
	for (auto *light : ambient_list) result += light->getColor(Vec3f());
	return result;
}


__device__ int8_t Scene::hit(RecordHit_Extend *record) const {
	RecordHit	temp_record;
	int8_t		is_hit			= 0;
	fp_t		closest			= record->length_max;

	// set ray
	temp_record.ray = record->record.ray;

	// search for hitable in child
	for (auto *hitable : hitable_list) {
		
		if (!hitable->hit(&temp_record, record->length_min, closest)) continue;
		// if (temp_record.distance > closest) continue;

		is_hit			= 1;
		closest			= temp_record.distance;
		record->record	= temp_record;
	}

	return is_hit;
}


// Static Function Implementation
// ...
