#include "../inc/RayTracer_Texture_Input.cuh"

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
__device__ Texture_Input::Texture_Input() {
	input_size	= 0;
	input_list	= nullptr;
	for (int32_t i = 0; i < input_size; ++i) input_list[i] = nullptr;
}


__device__ Texture_Input::~Texture_Input() {
}


__device__ void Texture_Input::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


__device__ void Texture_Input::_getPixel_(Vec3f &dst, Vec3f *src) const {
	dst = src[input_size];
}


// Static Function Implementation
// ...
