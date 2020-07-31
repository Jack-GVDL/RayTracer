#include "../inc/RayTracer_Texture_Gradient.hpp"


// Define
typedef Vec3f(*source_func_t)(const Ray *ray);


// Static Data
static Vec3f get_source_empty		(const Ray *ray);
static Vec3f get_source_direction	(const Ray *ray);
static Vec3f get_source_position	(const Ray *ray);
static Vec3f get_source_normal		(const Ray *ray);
static Vec3f get_source_custom		(const Ray *ray);


// Static Function Prototype
static source_func_t source_func_list[Texture_Gradient::SOURCE_MAX] = {
	get_source_empty,
	get_source_direction,
	get_source_position,
	get_source_custom
};


// Operation Handling
Vec3f Texture_Gradient::_getPixel_(const Ray *ray) const {
	// get source
	Vec3f vec_source = source_func_list[source](ray);

	// value addition and multiplication
	const double intensity_0 = (vec_source[0] + additor[0]) * multiplier[0];
	const double intensity_1 = (vec_source[1] + additor[1]) * multiplier[1];
	const double intensity_2 = (vec_source[2] + additor[2]) * multiplier[2];

	// need clamping
	return Vec3f(
		UtilMath::clamp<double>(intensity_0, 0.0, 1.0),
		UtilMath::clamp<double>(intensity_1, 0.0, 1.0),
		UtilMath::clamp<double>(intensity_2, 0.0, 1.0));
}


// do nothing
void Texture_Gradient::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


// Static Function Implementation
static Vec3f get_source_empty(const Ray *ray) {
	return Vec3f();
}


static Vec3f get_source_direction(const Ray *ray) {
	return ray->getDirection();
}


static Vec3f get_source_position(const Ray *ray) {
	return ray->getPosition();
}


// TODO: not yet completed
static Vec3f get_source_custom(const Ray *ray) {
	return Vec3f();
}
