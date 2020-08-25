#include "../inc/RayTracer_Texture_Constant.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
void Texture_Constant::setPixel(const Vec3f &point, const Vec3f &pixel) {
	// UNUSED(pixel)
	color = pixel;
}


void Texture_Constant::_getPixel_(Vec3f &dst, Vec3f *src) const {
	dst = color;
}


// TODO: backup
// void Texture_Constant::_getPixel_(Vec3f &dst, const Vec3f &src) const {
// 	dst = color;
// }


// Static Function Implementation
// ...
