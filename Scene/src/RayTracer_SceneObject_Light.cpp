#include "../../Utility/Utility.hpp"
#include "../inc/RayTracer_SceneObject_Light.hpp"
#include "../inc/RayTracer_SceneObject_Hitable.hpp"
#include "../inc/RayTracer_Scene.hpp"


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


Vec3f SceneObject_Light_Directional::getShadowAttenuation(const Scene *scene, const Vec3f &point) const {
	// variable preparation
	const Vec3f &direction	= getDirection(point);
	Vec3f       point_cur	= point;
	Vec3f       intensity	= Vec3f(1.0, 1.0, 1.0);

	// TODO: should move this part to scatter
	// first push the ray a little bit forward to prevent hit the same point
	point_cur = point_cur + direction * RAY_EPSILON;
	while (!intensity.isZero()) {
		
		// check if no intersection or intersection is behind the light source
		HitRecord	hit_record;
		Ray			ray	= Ray(point_cur, direction);
		if (!scene->hit(&ray, 0.0, MAXFLOAT, &hit_record)) return intensity;
		
		// new intensity *= transmissive
		const Material &material = hit_record.object->material;
		intensity *= material.transmissive;

		// push the ray froward a little bit
		point_cur = hit_record.point + direction * RAY_EPSILON;

	}

	return intensity;
}


Vec3f SceneObject_Light_Directional::getColor(const Vec3f &point) const {
	return color;
}


Vec3f SceneObject_Light_Directional::getDirection(const Vec3f &point) const {
	return -orientation;
}


// point light
double SceneObject_Light_Point::getDistanceAttenuation(const Vec3f &point) const {
	return 1.0;
}


Vec3f SceneObject_Light_Point::getShadowAttenuation(const Scene *scene, const Vec3f &point) const {
	// variable preparation
	const Vec3f &direction	= getDirection(point);
	Vec3f		point_cur	= point;
	Vec3f		intensity	= Vec3f();

	// TODO: should move this part to scatter
	// first push the ray a little bit forward to prevent hit the same point
	point_cur = point_cur + direction * RAY_EPSILON;
	while (!intensity.isZero()) {

		// check if no intersection or intersection is behind the light source
		HitRecord	hit_record;
		Ray			ray = Ray(point_cur, direction);
		if (!scene->hit(&ray, 0.0, MAXFLOAT, &hit_record)) return intensity;

		// new intensity *= transmissive
		const Material &material = hit_record.object->material;
		intensity *= material.transmissive;

		// push the ray forward a little bit
		point_cur = hit_record.point + direction * RAY_EPSILON;

	}

	return intensity;
}


Vec3f SceneObject_Light_Point::getColor(const Vec3f &point) const {
	return color;
}


Vec3f SceneObject_Light_Point::getDirection(const Vec3f &point) const {
	return (origin - point).normalize();
}


// point light


// Static Function Implementation
// ...
