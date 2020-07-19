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

	float a = VecMath::dot(r->getDirection() , r->getDirection());
	float b = VecMath::dot(oc, r->getDirection());
	float c = VecMath::dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	// no intersection
	if (discriminant <= 0) return false;

	// find the length of the ray
	// check if the ray is hit within the range
	double ray_length;

	ray_length = (-b - sqrt(b * b - a * c)) / a;
	if (ray_length < t_max && ray_length > t_min) goto RAY_HIT;

	ray_length = (-b + sqrt(b * b - a * c)) / a;
	if (ray_length < t_max && ray_length > t_min) goto RAY_HIT;

	return false;

	// ray hit the object within the range
	// need to set the content of hit record
	RAY_HIT:
	record->distance	= ray_length;
	record->point		= r->pointAt(record->distance);
	record->normal		= (record->point - center).normalize();
	record->object		= (SceneObject_Hitable*)this;

	// adjust the normal
	VecMath::reverseNormal_incidentRay(record->normal, r->getDirection());

	return true;
}


// Static Function Implementation
// ...
