#include "../inc/RayTracer_SceneObject_Hitable.cuh"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// hitable
__device__ SceneObject_Hitable::SceneObject_Hitable() {
}


__device__ SceneObject_Hitable::~SceneObject_Hitable() {
}


__device__ void SceneObject_Hitable::setMaterial(Material *material) {
	this->material = material;
}


__device__ int8_t SceneObject_Hitable::hit(RecordHit *record) const {
	return hit(record, FLOAT_MAX);
}


__device__ int8_t SceneObject_Hitable::hit(RecordHit *record, fp_t t_max) const {
	return hit(record, 0.0, t_max);
}


// Static Function Implementation
// ...
