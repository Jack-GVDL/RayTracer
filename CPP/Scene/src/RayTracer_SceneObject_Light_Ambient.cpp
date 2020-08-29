#include "../inc/RayTracer_SceneObject_Light_Ambient.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
// TODO: backup
// Vec3f SceneObject_Light_Ambient::getShadowAttenuation(const Scene *scene, const Vec3f &point) const {
// 	return Vec3f(0);
// }
// 
// 
// fp_t  SceneObject_Light_Ambient::getDistanceAttenuation(const Vec3f &point) const {
// 	return 0;
// }


fp_t SceneObject_Light_Ambient::getAttenuation(const Vec3f &point) const {
	return 1.0;
}


fp_t SceneObject_Light_Ambient::getDistance(const Vec3f &point) const {
	return std::numeric_limits<fp_t>::max();
}


Vec3f SceneObject_Light_Ambient::getColor(const Vec3f &point) const {
	return color;
}


Vec3f SceneObject_Light_Ambient::getDirection(const Vec3f &point) const {
	return Vec3f(0);
}


// Static Function Implementation
// ...
