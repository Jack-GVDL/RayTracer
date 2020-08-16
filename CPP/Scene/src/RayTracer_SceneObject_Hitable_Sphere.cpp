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
// hitable
void Hitable_Sphere::setCenter(const Vec3f &center) {
	this->origin	= center;
	this->center	= center;
	updateBoundingBox();
}


void Hitable_Sphere::setRadius(double radius) {
	this->radius	= radius;
	updateBoundingBox();
}


bool Hitable_Sphere::hit(RecordHit *record, double t_min, double t_max) const {
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


void Hitable_Sphere::updateBoundingBox() {
	bounding_min	= center - Vec3f(radius);
	bounding_max	= center + Vec3f(radius);
}


// mapper
void Mapper_Sphere::setSphere(Hitable_Sphere *sphere) {
	this->sphere = sphere;
}


// TODO: not yet completed
void Mapper_Sphere::map(Vec3f &vector) const {
	if (sphere == nullptr) return;

	// get displacement from center of sphere
	Vec3f dis = vector - sphere->center;

	// map on to 2d plane
	// no z-axis
	double dis_radius = sqrt(dis[0] * dis[0] + dis[2] * dis[2]);

	vector[0]	= atan(dis[0] / std::abs(dis[2])) / M_PI;
	vector[1]	= atan(dis[1] / dis_radius) / M_PI * 2;
	vector[2]	= 0;

	// x-axis adjustment
	if (dis[2] < 0) {
		if (dis[0] > 0)	vector[0]	= 1 - vector[0];
		else			vector[0]	= -1 + vector[0];
	}
}


// texture
void Texture_Mapper_Sphere::setSphere(Hitable_Sphere *sphere) {
	this->sphere = sphere;
}


void Texture_Mapper_Sphere::setPixel(const Vec3f &point, const Vec3f &pixel) {

}


void Texture_Mapper_Sphere::_getPixel_(Vec3f &dst, const Vec3f &src) const {
	if (sphere == nullptr) return;

	// get displacement from center of sphere
	Vec3f dis = src - sphere->center;

	// map on to 2d plane
	// no z-axis
	double dis_radius = sqrt(dis[0] * dis[0] + dis[2] * dis[2]);

	dst[0]	= atan(dis[0] / std::abs(dis[2])) / M_PI;
	dst[1]	= atan(dis[1] / dis_radius) / M_PI * 2;
	dst[2]	= 0;

	// x-axis adjustment
	if (dis[2] < 0) {
		if (dis[0] > 0)	dst[0]	= 1 - dst[0];
		else			dst[0]	= -1 + dst[0];
	}
}


// Static Function Implementation
// ...
