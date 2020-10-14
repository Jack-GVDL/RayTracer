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
__device__ Light_Directional::Light_Directional() {
}


__device__ Light_Directional::~Light_Directional() {
}


__device__ void Light_Directional::setOrientation(const Vec3f &orientation) {
	this->orientation = orientation;
}


__device__ fp_t Light_Directional::getAttenuation(const Vec3f &point) const {
	return 1.0;
}


__device__ fp_t Light_Directional::getDistance(const Vec3f &point) const {
	return FLOAT_MAX;
}


__device__ Vec3f Light_Directional::getColor(const Vec3f &point) const {
	return color;
}


__device__ Vec3f Light_Directional::getDirection(const Vec3f &point) const {
	return orientation;
}


// Static Function Implementation
// ...
