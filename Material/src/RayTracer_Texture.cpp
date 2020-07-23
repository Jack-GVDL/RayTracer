#include "../inc/RayTracer_Texture.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
Vec3f Texture_Constant::getPixel(const Vec3f &point) const {
	return color;
}


void Texture_Constant::setPixel(const Vec3f &point, const Vec3f &pixel) {
	// UNUSED(pixel)
	color = point;
}


// Static Function Implementation
// ...
