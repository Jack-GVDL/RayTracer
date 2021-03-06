#include "../inc/RayTracer_Scene.cuh"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
__device__ Scene::Scene() {
}


__device__ Scene::~Scene() {
}


__device__ error_t Scene::allocateHitable(void *memory, int32_t size) {
	// free old
	cudaFree(hitable_list);

	// set new
	hitable_list	= (SceneObject_Hitable**)memory;
	hitable_size	= size;
	hitable_index	= 0;

	// backup
	/*
	// free old
	cudaFree(hitable_list);

	// allocate new
	cudaMalloc(&hitable_list, size * sizeof(SceneObject_Hitable*));
	hitable_size	= size;
	hitable_index	= 0;
	*/

	return ERROR_NO;
}


// TODO: missing uniqueness checking
__device__ error_t Scene::addHitable(SceneObject_Hitable *hitable) {
	if (hitable_index == hitable_size) return ERROR_ANY;

	hitable_list[hitable_index] = hitable;
	hitable_index++;
	return ERROR_NO;
}


// TODO: not yet completed
__device__ error_t Scene::rmHitable(SceneObject_Hitable *hitable) {
	return ERROR_ANY;
}


__device__ error_t Scene::allocateLight(void *memory, int32_t size) {
	// free old
	cudaFree(light_list);

	// set new
	light_list		= (SceneObject_Light**)memory;
	light_size		= size;
	light_index		= 0;

	// backup
	/*
	// free old
	cudaFree(light_list);

	// allocate new
	cudaMalloc(&light_list, size * sizeof(SceneObject_Light*));
	light_size	= size;
	light_index	= 0;
	*/

	return ERROR_NO;
}


// TODO: missing uniqueness checking
__device__ error_t Scene::addLight(SceneObject_Light *light) {
	if (light_index == light_size) return ERROR_ANY;

	light_list[light_index] = light;
	light_index++;
	return ERROR_NO;
}


// TODO: not yet completed
__device__ error_t Scene::rmLight(SceneObject_Light *light) {
	return ERROR_ANY;
}


__device__ error_t Scene::allocateAmbient(void *memory, int32_t size) {
	// free old
	cudaFree(ambient_list);

	// set new
	ambient_list	= (SceneObject_Light**)memory;
	ambient_size	= size;
	ambient_index	= 0;

	// backup
	/*
	// free old
	cudaFree(ambient_list);

	// allocate new
	cudaMalloc(&ambient_list, size * sizeof(SceneObject_Light*));
	ambient_size	= size;
	ambient_index	= 0;
	*/

	return ERROR_NO;
}


// TODO: missing uniqueness checking
__device__ error_t Scene::addAmbient(SceneObject_Light *light) {
	if (ambient_index == ambient_size) return ERROR_ANY;

	ambient_list[ambient_index] = light;
	ambient_index++;
	return ERROR_NO;
}


// TODO: not yet completed
__device__ error_t Scene::rmAmbient(SceneObject_Light *light) {
	return ERROR_ANY;
}


__device__ Vec3f Scene::getAmbientIntensity() const {
	Vec3f result = Vec3f(0);

	for (int32_t i = 0; i < ambient_index; ++i) {
		SceneObject_Light *light = ambient_list[i];
		result += light->getColor(Vec3f());
	}

	return result;
}


__device__ int8_t Scene::hit(RecordHit_Extend *record) const {
	RecordHit	temp_record;
	int8_t		is_hit			= 0;
	fp_t		closest			= record->length_max;

	// set ray
	temp_record.ray = record->record.ray;

	// search for hitable in child
	for (int32_t i = 0; i < hitable_index; ++i) {
		SceneObject_Hitable *hitable = hitable_list[i];
		
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
