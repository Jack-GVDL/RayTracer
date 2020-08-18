#include "../inc/RayTracer_Texture_Image.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// do nothing
void Texture_Image::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


void Texture_Image::_getPixel_(Vec3f &dst, std::vector<Vec3f> *src) const {
	// get point
	const int x = (int)((*src)[0][0]);
	const int y = (int)((*src)[0][1]);

	// check if out of bound
	if (x < 0 || x >= width ||y < 0 || y >= height) {
		dst = Vec3f();
		return;
	}

	// get image pixel
	dst = color[x + y * width];
}


// TODO: backup
// void Texture_Image::_getPixel_(Vec3f &dst, const Vec3f &src) const {
// 	// get point
// 	const int x = (int)(src[0]);
// 	const int y = (int)(src[1]);

// 	// check if out of bound
// 	if (x < 0 || x >= width ||y < 0 || y >= height) {
// 		dst = Vec3f();
// 		return;
// 	}

// 	// get image pixel
// 	dst = color[x + y * width];
// }


// Static Function Implementation
// ...
