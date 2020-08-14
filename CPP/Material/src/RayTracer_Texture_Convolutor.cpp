#include "../inc/RayTracer_Texture_Convolutor.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
void Texture_Convolutor::setTexture(Texture *texture) {
	this->texture = texture;
}


void Texture_Convolutor::setKernel(double *kernel, int width) {
	kernel_width = width;
	this->kernel = kernel;
}


void Texture_Convolutor::_getPixel_(Vec3f &dst, const Vec3f &src) const {
	// if texture or kernel not exist
	// then do nothing
	if (texture == nullptr) {
		dst	= Vec3f();
		return;
	}

	if (kernel == nullptr) {
		dst = Vec3f();
		return;
	}

	// get center point
	const double 	double_x 		= src[0];
	const double 	double_y 		= src[1];
	
	const int		int_x			= (int)(double_x);
	const int		int_y			= (int)(double_y);

	// get pixel sum in kernel
	Vec3f		pixel_temp;
	Vec3f		pixel_sum	= Vec3f(0);

	const int	width_half	= kernel_width / 2;
	int			index		= 0;
	
	for (int y = -width_half; y < width_half + 1; y++) {
		for (int x = -width_half; x < width_half + 1; x++) {

			texture->getPixel(pixel_temp, Vec3f(int_x + x, int_y + y, 0));
			pixel_sum += pixel_temp * kernel[index];
			index++;

		}
	}

	// set dst pixel
	dst = pixel_sum / (kernel_width * kernel_width);
}


void Texture_Convolutor::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


// Static Function Implementation
// ...
