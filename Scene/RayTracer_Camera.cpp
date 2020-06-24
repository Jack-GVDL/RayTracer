#include "RayTracer_Camera.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
void Camera::setLookFrom(const Vec3f look_from) {
	this->look_from = look_from;
	update();
}


void Camera::setLookAt(const Vec3f look_at, const Vec3f up) {
	this->look_at	= look_at;
	this->up		= up;
	update();
}


void Camera::setFOV(double value) {
	this->fov = value;
	update();
}


void Camera::setAspectRatio(double value) {
	this->aspect = value;
	update();
}


void Camera::update() {
	// fov
	// TODO: need more explanation on FOV
	//
	// aspect ratio: ratio of is width to its height
	// aspect = width / height
	// height = width / aspect
	// width  = aspect / height
	double	theta		= fov * M_PI / 180;
	double	half_height	= tan(theta / 2);
	double	half_width	= aspect / half_height;

	// w: direction
	// u: x-axis
	// v: y-axis
	// corss product of two normalized vectors should also be a normalized vector
	w	= (look_at - look_from).normalize();
	u	= up.cross(w).normalize();
	v	= w.cross(u);

	u	*= half_width;
	v	*= half_height; 
}


Ray Camera::getRay(double x, double y) {
	return Ray(look_from, w + x * u + y * v);
}


// Static Function Implementation
// ...
