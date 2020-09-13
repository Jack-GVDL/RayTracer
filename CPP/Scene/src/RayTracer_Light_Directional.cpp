#include "../inc/RayTracer_Light_Directional.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
SceneObject_Light_Directional::SceneObject_Light_Directional() {
}


SceneObject_Light_Directional::~SceneObject_Light_Directional() {
}


void SceneObject_Light_Directional::setOrientation(const Vec3f &orientation) {
	this->orientation = orientation;
}


fp_t SceneObject_Light_Directional::getAttenuation(const Vec3f &point) const {
	return 1.0;
}


fp_t SceneObject_Light_Directional::getDistance(const Vec3f &point) const {
	return std::numeric_limits<fp_t>::max();
}


Vec3f SceneObject_Light_Directional::getColor(const Vec3f &point) const {
	return color;
}


Vec3f SceneObject_Light_Directional::getDirection(const Vec3f &point) const {
	return orientation;
}


// Static Function Implementation
// ...
