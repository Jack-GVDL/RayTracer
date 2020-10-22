#include "../inc/RayTracer_Texture_Constant.cuh"

// TODO: test
#include <stdio.h>


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
__device__ Texture_Constant::Texture_Constant() {
	input_size	= 0;
	input_list	= nullptr;
	for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
}


__device__ Texture_Constant::~Texture_Constant() {
}


__device__ void Texture_Constant::setPixel(const Vec3f &point, const Vec3f &pixel) {
	color = pixel;
}


__device__ void Texture_Constant::_getPixel_(Vec3f &dst, Vec3f *src) const {
	dst = color;
}


// Static Function Implementation
// ...
