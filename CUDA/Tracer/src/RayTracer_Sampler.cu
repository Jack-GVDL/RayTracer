#include "../inc/RayTracer_Sampler.cuh"


// Define
// ...


// Typedef
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
__host__ Sampler::Sampler():
buffer_dir			(nullptr),
buffer_image		(nullptr),
buffer_dir_size		(0),
buffer_image_size	(0),
w					(0),
h					(0),
block_w				(0),
block_h				(0)
{
}


__host__ Sampler::~Sampler() {
	cudaFree(buffer_dir);
	cudaFree(buffer_image);
}


__host__ error_t Sampler::setSizeImage(int32_t w, int32_t h) {
	if (w <= 0 || h <= 0) return ERROR_ANY;

	this->w = w;
	this->h = h;
	
	update();
	return ERROR_NO;
}


// Static Function Implementation
// ...
