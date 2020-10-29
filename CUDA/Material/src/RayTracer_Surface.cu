#include "../inc/RayTracer_Surface.cuh"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// TODO: rename
__global__ static void	setTextureImage_data	(Texture_Image *texture, Vec3f *data, int32_t w, int32_t h);


// Operation Handling
__host__ bool Surface::convertToTexture(Texture_Image *texture) {
	// check if data and texture exist or not
	if (data == nullptr)	return false;
	if (texture == nullptr)	return false;
	
	// TODO: currently can only handle RGB_888
	if (bit_pixel != 24)	return false;

	// malloc for temp space
	Vec3f *color_host;
	Vec3f *color_device;

	color_host = new Vec3f[width * height];
	cudaMalloc(&color_device, width * height * sizeof(Vec3f));

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

		color_host[i] = Vec3f(color_r, color_g, color_b);
	}

	// memcpy to device and call kernel
	cudaMemcpy(color_device, color_host, width * height * sizeof(Vec3f), cudaMemcpyHostToDevice);
	setTextureImage_data <<< 1, 1 >>> (texture, color_device, width, height);

	// free for temp space
	delete[] color_host;

	return true;
}


// Static Function Implementation
__global__ static void setTextureImage_data(Texture_Image *texture, Vec3f *data, int32_t w, int32_t h) {
	texture->color	= data;
	texture->width	= w;
	texture->height	= h;
}
