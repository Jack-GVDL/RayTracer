#include "../inc/RayTracer_Light_Directional.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
__device__ SceneObject_Light_Directional::SceneObject_Light_Directional() {
}


__device__ SceneObject_Light_Directional::~SceneObject_Light_Directional() {
}


__device__ void SceneObject_Light_Directional::setOrientation(const Vec3f &orientation) {
	this->orientation = orientation;
}


__device__ fp_t SceneObject_Light_Directional::getAttenuation(const Vec3f &point) const {
	return 1.0;
}


__device__ fp_t SceneObject_Light_Directional::getDistance(const Vec3f &point) const {
	return std::numeric_limits<fp_t>::max();
}


__device__ Vec3f SceneObject_Light_Directional::getColor(const Vec3f &point) const {
	return color;
}


__device__ Vec3f SceneObject_Light_Directional::getDirection(const Vec3f &point) const {
	return orientation;
}


// Static Function Implementation
// ...
