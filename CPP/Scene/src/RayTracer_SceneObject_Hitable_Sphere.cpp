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


void Hitable_Sphere::setRadius(fp_t radius) {
	this->radius	= radius;
	updateBoundingBox();
}


bool Hitable_Sphere::hit(RecordHit *record, fp_t t_min, fp_t t_max) const {
	const Ray	*ray	= &(record->ray);
	Vec3f		oc		= ray->getPosition() - center;

	fp_t	a = VecMath::dot(ray->getDirection() , ray->getDirection());
	fp_t	b = VecMath::dot(oc, ray->getDirection());
	fp_t	c = VecMath::dot(oc, oc) - radius * radius;
	fp_t	discriminant = b * b - a * c;

	// no intersection
	if (discriminant <= 0) return false;

	// find the length of the ray
	// check if the ray is hit within the range
	fp_t ray_length;

	ray_length = (-b - sqrt(b * b - a * c)) / a;
	if (ray_length < t_max && ray_length > t_min) goto RAY_HIT;

	ray_length = (-b + sqrt(b * b - a * c)) / a;
	if (ray_length < t_max && ray_length > t_min) goto RAY_HIT;

	return false;

	// ray hit the object within the range
	// need to set the content of hit record
	RAY_HIT:
	record->distance	= ray_length;
	record->point		= ray->pointAt(ray_length);
	record->normal		= (record->point - center).normalize();
	record->object		= (SceneObject_Hitable*)this;

	// adjust normal
	// normal and incident ray should somehow "opposite"
	VecMath::reverseNormal_incidentRay(record->normal, ray->getDirection());

	return true;
}


void Hitable_Sphere::updateBoundingBox() {
	bounding.setBounding(center - Vec3f(radius), center + Vec3f(radius));
}


// texture - mapper
void Texture_Mapper_Sphere::setSphere(Hitable_Sphere *sphere) {
	this->sphere = sphere;
}


void Texture_Mapper_Sphere::setPixel(const Vec3f &point, const Vec3f &pixel) {

}


void Texture_Mapper_Sphere::_getPixel_(Vec3f &dst, Vec3f *src) const {
	if (sphere == nullptr) {
		dst = Vec3f();
		return;
	}

	// get displacement from center of sphere
	Vec3f dis = src[0] - sphere->center;

	// map on to 2d plane
	// no z-axis
	fp_t dis_radius = sqrt(dis[0] * dis[0] + dis[2] * dis[2]);

	dst[0]	= atan(dis[0] / std::abs(dis[2])) / M_PI;
	dst[1]	= atan(dis[1] / dis_radius) / M_PI * 2;
	dst[2]	= 0;

	// x-axis adjustment
	if (dis[2] < 0) {
		if (dis[0] > 0)	dst[0]	= 1 - dst[0];
		else			dst[0]	= -1 + dst[0];
	}
}


// texture - direction
void Texture_Direction_Sphere::setSphere(Hitable_Sphere *sphere) {
	this->sphere = sphere;
}


void Texture_Direction_Sphere::setPixel(const Vec3f &point, const Vec3f &pixel) {

}


void Texture_Direction_Sphere::_getPixel_(Vec3f &dst, Vec3f *src) const {
	if (sphere == nullptr) {
		dst = Vec3f();
		return;
	}

	// first get the normal, it is used as z-axis
	// cross product of up vector and normal used as x-axis
	Vec3f axis_z = src[0] - sphere->center;
	Vec3f axis_x = Vec3f(0, 1, 0).cross(axis_z);
	Vec3f axis_y = axis_z.cross(axis_x);

	axis_x = axis_x.normalize();
	axis_y = axis_y.normalize();
	axis_z = axis_z.normalize();

	// assume that input is already normalized
	dst = 
	axis_x * src[1][0] + 
	axis_y * src[1][1] + 
	axis_z * src[1][2];
}


// Static Function Implementation
// ...
