#include "../inc/RayTracer_SceneObject_Hitable_Sphere.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
void SceneObject_Sphere::setCenter(const Vec3f &center) {
	this->origin	= center;
	this->center	= center;
	// updateBoundingBox();
}


void SceneObject_Sphere::setRadius(double radius) {
	this->radius	= radius;
	// updateBoundingBox();
}


bool SceneObject_Sphere::hit(RecordHit *record, double t_min, double t_max) const {
	const Ray	*ray	= &(record->ray);
	Vec3f		oc		= ray->getPosition() - center;

	float a = VecMath::dot(ray->getDirection() , ray->getDirection());
	float b = VecMath::dot(oc, ray->getDirection());
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
	record->point		= ray->pointAt(record->distance);
	record->normal		= (record->point - center).normalize();
	record->object		= (SceneObject_Hitable*)this;

	// adjust normal
	// normal and incident ray should somehow "opposite"
	VecMath::reverseNormal_incidentRay(record->normal, ray->getDirection());

	return true;
}


void SceneObject_Sphere::updateBoundingBox() {
	bounding_min	= center - Vec3f(radius);
	bounding_max	= center + Vec3f(radius);
}


// Static Function Implementation
// ...
