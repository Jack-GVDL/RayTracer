#include "../inc/RayTracer_SceneElement.cuh"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
__device__ SceneElement() {
}


__device__ ~SceneElement() {
}


__device__ void SceneElement::setOrigin(const Vec3f &origin) {
	this->origin = origin;
}


__device__ error_t SceneElement::addChild(SceneElement *scene) {
	child.push_back(scene);
	return ERROR_NO;
}


// TODO: not yet completed
__device__ error_t SceneElement::rmChild(SceneElement *scene) {
	return ERROR_ANY;
}


// Static Function Implementation
// ...
