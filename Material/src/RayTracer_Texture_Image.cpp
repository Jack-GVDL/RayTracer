#include "../inc/RayTracer_Texture_Image.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
Vec3f Texture_Image::_getPixel_(const Ray *ray) const {
	// get point
	// TODO: mapping is not yet completed
	const int x = (int)(ray->getPosition()[0]);
	const int y = (int)(ray->getPosition()[1]);

	// check if out of bound
	if (x < 0 || x >= width ||
		y < 0 || y >= height) return Vec3f(0);

	// get image pixel
	// TODO: supersampling is not yet completed
	return color[x + y * width];
}


// do nothing
void Texture_Image::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


// Static Function Implementation
// ...
