#include "RayTracer_SceneObject_Light.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// directional light
double SceneObject_Light_Directional::getDistanceAttenuation(const Vec3f &point) const {
	// distance to light is inf., so f(di) goes to 0
	return 1.0;
}


Vec3f SceneObject_Light_Directional::getShadowAttenuation(const Vec3f &point) const {
	// variable preparation
	const Vec3f &ray_dir			= getDirection(point);
	Vec3f       point_light			= point;
	Vec3f       intensity_result	= Vec3f(1.0, 1.0, 1.0);

	// first push the ray a little bit forward to prevent hit the same point
	point_light = point_light + ray_dir * RAY_EPSILON;
	while (!intensity_result.isZero()) {
		
		// check if no intersect or intersection is behind the light source
		HitRecord hit_record;
		
	}
}


// point light


// Static Function Implementation
// ...
