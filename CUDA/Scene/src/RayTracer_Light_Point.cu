#include "../inc/RayTracer_Light_Point.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
__device__ Light_Point::Light_Point() {
}


__device__ Light_Point::~Light_Point() {
}


__device__ void Light_Point::setAttenuation(const Vec3f &coeff) {
	this->attenuation = coeff;
}


__device__ fp_t Light_Point::getAttenuation(const Vec3f &point) const {
	const fp_t		coeff_1	= attenuation[0];
	const fp_t		coeff_2	= attenuation[1];
	const fp_t		coeff_3	= attenuation[2];

	const fp_t		d2		= (point - origin).lengthSquared();
	const fp_t		d1		= sqrt(d2);
	const fp_t		result	= coeff_1 + coeff_2 * d1 + coeff_3 * d2;

	// do not divide by zero
	return result == 0 ? 1 : min<fp_t>(1 / result, 1);
}


__device__ fp_t Light_Point::getDistance(const Vec3f &point) const {
	return (origin - point).length();
}


__device__ Vec3f Light_Point::getColor(const Vec3f &point) const {
	return color;
}


__device__ Vec3f Light_Point::getDirection(const Vec3f &point) const {
	return (origin - point).normalize();
}


// Static Function Implementation
// ...
