#include "../inc/RayTracer_Camera.hpp"


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
	double	height_half	= tan(theta / 2);
	double	width_half	= aspect / height_half;

	// backup
	// width	= width_half;
	// height	= height_half;

	// w: direction
	// u: x-axis
	// v: y-axis
	// corss product of two normalized vectors should also be a normalized vector
	w	= (look_at - look_from).normalize();
	u	= w.cross(up).normalize();
	v	= u.cross(w);

	u	*= width_half;
	v	*= height_half; 
}


Ray Camera::getRay(double x, double y) const {
	return Ray(look_from, (w + x * u + y * v).normalize());
}


// Static Function Implementation
// ...
