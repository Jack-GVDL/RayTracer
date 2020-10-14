#include "../inc/RayTracer_Camera.cuh"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
__device__ Camera::Camera() {
	this->look_from		= Vec3f(0.0, 0.0, 0.0);
	this->look_at		= Vec3f(0.0, 0.0, 1.0);
	this->up			= Vec3f(0.0, 1.0, 0.0);
	this->fov			= 90;
	this->aspect		= 1;

	update();
}


__device__ Camera::Camera(const Vec3f look_from, const Vec3f look_at, const Vec3f up, fp_t fov, fp_t aspect) {
	this->look_from	= look_from;
	this->look_at	= look_at;
	this->up		= up;
	this->fov		= fov;
	this->aspect	= aspect;

	update();
}


__device__ void Camera::setLookFrom(const Vec3f look_from) {
	this->look_from = look_from;
	update();
}


__device__ void Camera::setLookAt(const Vec3f look_at) {
	this->look_at	= look_at;
	update();
}


__device__ void Camera::setUpDirection(const Vec3f up) {
	this->up		= up;
	update();
}


__device__ void Camera::setFOV(fp_t value) {
	this->fov = value;
	update();
}


__device__ void Camera::setAspectRatio(fp_t value) {
	this->aspect = value;
	update();
}


__device__ void Camera::setAll(const Vec3f look_from, const Vec3f look_at, const Vec3f up, fp_t fov, fp_t aspect) {
	this->look_from	= look_from;
	this->look_at	= look_at;
	this->up		= up;
	this->fov		= fov;
	this->aspect	= aspect;

	update();
}


__device__ void Camera::update() {
	// fov
	// TODO: need more explanation on FOV
	//
	// aspect ratio: ratio of is width to its height
	// aspect = width / height
	// height = width / aspect
	// width  = aspect / height
	fp_t	theta		= fov * M_PI / 180;
	fp_t	height_half	= tan(theta / 2);
	fp_t	width_half	= aspect / height_half;

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


__device__ Ray Camera::getRay(fp_t x, fp_t y) const {
	return Ray(look_from, (w + x * u + y * v).normalize());
}


// Static Function Implementation
// ...
