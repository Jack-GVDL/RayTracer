#include "../inc/RayTracer_Texture_Convolutor.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
__device__ Texture_Convolutor::Texture_Convolutor() {
	input_size	= 1;
	input_list	= new Texture*[input_size];
	for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
}


__device__ Texture_Convolutor::~Texture_Convolutor() {
}


__device__ void Texture_Convolutor::setTexture(Texture *texture) {
	this->texture = texture;
}


__device__ void Texture_Convolutor::setKernel(fp_t *kernel, int32_t width) {
	kernel_width = width;
	this->kernel = kernel;
}


__device__ void Texture_Convolutor::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


__device__ void Texture_Convolutor::_getPixel_(Vec3f &dst, Vec3f *src) const {
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
	const fp_t 		double_x 	= src[0][0];
	const fp_t 		double_y 	= src[0][1];
	
	const int32_t	int_x		= (int32_t)(double_x);
	const int32_t	int_y		= (int32_t)(double_y);

	// get pixel sum in kernel
	Vec3f			pixel_temp;
	Vec3f			pixel_sum	= Vec3f(0);

	const int32_t	width_half	= kernel_width / 2;
	int				index		= 0;
	
	for (int32_t y = -width_half; y < width_half + 1; y++) {
		for (int32_t x = -width_half; x < width_half + 1; x++) {

			texture->getPixel(pixel_temp, Vec3f(int_x + x, int_y + y, 0));
			pixel_sum += pixel_temp * kernel[index];
			index++;

		}
	}

	// set dst pixel
	dst = pixel_sum / (kernel_width * kernel_width);
}


// Static Function Implementation
// ...
