#include "../inc/RayTracer_SceneObject_Hitable_Sphere.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
bool SceneObject_Sphere::hit(const Ray *r, float t_min, float t_max, HitRecord *record) const {
	Vec3f oc = r->getPosition() - center;

	float a = RayTracer::dot(r->getDirection() , r->getDirection());
	float b = RayTracer::dot(oc, r->getDirection());
	float c = RayTracer::dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	// no intersection
	if (discriminant <= 0) return false;

	// ...
	float temp;

	temp = (-b - sqrt(b * b - a * c)) / a;
	if (temp < t_max && temp > t_min) {
		record->distance	= temp;
		record->point		= r->pointAt(record->distance);
		record->normal		= (record->point - center) / radius;
		record->object		= (SceneObject_Hitable*)this;
		return true;
	}

	temp = (-b + sqrt(b * b - a * c)) / a;
	if (temp < t_max && temp > t_min) {
		record->distance	= temp;
		record->point		= r->pointAt(record->distance);
		record->normal		= (record->point - center) / radius;
		record->object		= (SceneObject_Hitable*)this;
		return true;
	}

	return false;
}


// Static Function Implementation
// ...
