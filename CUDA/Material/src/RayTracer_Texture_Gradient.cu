#include "../inc/RayTracer_Texture_Gradient.cuh"


// Define
typedef Vec3f(*source_func_t)(const Ray *ray);


// Static Data
__device__ static Vec3f get_source_empty		(const Ray *ray);
__device__ static Vec3f get_source_direction	(const Ray *ray);
__device__ static Vec3f get_source_position		(const Ray *ray);
__device__ static Vec3f get_source_normal		(const Ray *ray);
__device__ static Vec3f get_source_custom		(const Ray *ray);


// Static Function Prototype
__device__ static source_func_t source_func_list[Texture_Gradient::SOURCE_MAX] = {
	get_source_empty,
	get_source_direction,
	get_source_position,
	get_source_custom
};


// Operation Handling
__device__ Texture_Gradient::Texture_Gradient() {
	input_size	= 1;
	input_list	= new Texture*[input_size];
	for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
}


__device__ Texture_Gradient::~Texture_Gradient() {
}


__device__ void Texture_Gradient::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


__device__ void Texture_Gradient::_getPixel_(Vec3f &dst, Vec3f *src) const {
	// value addition and multiplication
	const fp_t	intensity_0 = (src[0][0] + additor[0]) * multiplier[0];
	const fp_t	intensity_1 = (src[0][1] + additor[1]) * multiplier[1];
	const fp_t	intensity_2 = (src[0][2] + additor[2]) * multiplier[2];

	// need clamping
	dst = Vec3f(
		UtilMath::clamp<fp_t>(intensity_0, 0.0, 1.0),
		UtilMath::clamp<fp_t>(intensity_1, 0.0, 1.0),
		UtilMath::clamp<fp_t>(intensity_2, 0.0, 1.0));
}


// Static Function Implementation
__device__ static Vec3f get_source_empty(const Ray *ray) {
	return Vec3f();
}


__device__ static Vec3f get_source_direction(const Ray *ray) {
	return ray->getDirection();
}


__device__ static Vec3f get_source_position(const Ray *ray) {
	return ray->getPosition();
}


// TODO: not yet completed
__device__ static Vec3f get_source_custom(const Ray *ray) {
	return Vec3f();
}
