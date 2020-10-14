#include "../inc/RayTracer_Texture_Math.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
// additor
__device__ Texture_Math_Additor::Texture_Math_Additor() {
	input_size	= 1;
	input_list	= new Texture*[input_size];
	for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
}


__device__ Texture_Math_Additor::~Texture_Math_Additor() {
}


__device__ void Texture_Math_Additor::setAdditor(const Vec3f &value) {
	this->additor = value;
}


__device__ void Texture_Math_Additor::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


__device__ void Texture_Math_Additor::_getPixel_(Vec3f &dst, Vec3f *src) const {
	dst = src[0] + additor;
}


// multiplier
__device__ Texture_Math_Multiplier::Texture_Math_Multiplier() {
	input_size	= 1;
	input_list	= new Texture*[input_size];
	for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
}


__device__ Texture_Math_Multiplier::~Texture_Math_Multiplier() {
}


__device__ void Texture_Math_Multiplier::setMultiplier(const Vec3f &value) {
	this->multiplier = value;
}


__device__ void Texture_Math_Multiplier::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


__device__ void Texture_Math_Multiplier::_getPixel_(Vec3f &dst, Vec3f *src) const {
	dst = src[0] * multiplier;
}


// Static Function Implementation
// ...
