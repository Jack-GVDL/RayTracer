#include "../inc/RayTracer_Surface.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
bool Surface::convertToTexture(Texture_Image *texture) {
	// check if data and texture exist or not
	if (data == nullptr)	return false;
	if (texture == nullptr)	return false;
	
	// TODO: currently can only handle RGB_888
	if (bit_pixel != 24)	return false;

	// copy data to texture
	texture->width	= width;
	texture->height	= height;
	
	// TODO: no conversion is needed now as Texture use RGB_888
	texture->color = new Vec3f[width * height];

	// texture use RGB_888
	fp_t			color_r, color_g, color_b;
	const int32_t	offset_pixel	= (bit_pixel + 7) / 8;
	const int32_t	offset_r		= 0;
	const int32_t	offset_g		= 1;
	const int32_t	offset_b		= 2;

	for (int i = 0; i < width * height; i++) {
		// get RGB and convert it double
		// where the range is [0, 1] (0, 1 is inclusive)
		// TODO: currently assume the range of a single channel is [0, 255]
		color_r = (fp_t)(data[i * offset_pixel + offset_r]) / 255.0;
		color_g = (fp_t)(data[i * offset_pixel + offset_g]) / 255.0;
		color_b = (fp_t)(data[i * offset_pixel + offset_b]) / 255.0;

		texture->color[i] = Vec3f(color_r, color_g, color_b);
	}

	return true;
}


// Static Function Implementation
// ...
