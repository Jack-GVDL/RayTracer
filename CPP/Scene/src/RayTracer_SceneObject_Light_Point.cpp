#include "../inc/RayTracer_SceneObject_Light_Point.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
SceneObject_Light_Point::SceneObject_Light_Point() {
}


SceneObject_Light_Point::~SceneObject_Light_Point() {
}


void SceneObject_Light_Point::setAttenuation(const Vec3f &coeff) {
	this->attenuation = coeff;
}


fp_t SceneObject_Light_Point::getAttenuation(const Vec3f &point) const {
	const fp_t		coeff_1	= attenuation[0];
	const fp_t		coeff_2	= attenuation[1];
	const fp_t		coeff_3	= attenuation[2];

	const fp_t		d2		= (point - origin).lengthSquared();
	const fp_t		d1		= sqrt(d2);
	const fp_t		result	= coeff_1 + coeff_2 * d1 + coeff_3 * d2;

	// do not divide by zero
	return result == 0 ? 1 : std::min<fp_t>(1 / result, 1);
}


fp_t SceneObject_Light_Point::getDistance(const Vec3f &point) const {
	return (origin - point).length();
}


Vec3f SceneObject_Light_Point::getColor(const Vec3f &point) const {
	return color;
}


Vec3f SceneObject_Light_Point::getDirection(const Vec3f &point) const {
	return (origin - point).normalize();
}


// Static Function Implementation
// ...
