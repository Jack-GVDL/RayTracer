#include "../inc/RayTracer_Texture_Input.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
// do nothing
void Texture_Input::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


void Texture_Input::_getPixel_(Vec3f &dst, Vec3f *src) const {
	dst = src[input_size];
}


// Static Function Implementation
// ...
