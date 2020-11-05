#include "../inc/RayTracer_Sampler_Grid.cuh"


// Define
// ...


// Typedef
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
__host__ Sampler_Grid::Sampler_Grid():
grid_w(1),
grid_h(1)
{
}


__host__ Sampler_Grid::~Sampler_Grid()  {
}


__host__ error_t Sampler_Grid::setSizeGrid(int32_t w, int32_t h) {
	if (w <= 0 || h <= 0) return ERROR_ANY;

	// TODO: in this current condition, grid and block mean the same thing
	this->grid_w	= w;
	this->grid_h	= h;

	this->block_w	= w;
	this->block_h	= h;

	return ERROR_NO;
}


__host__ error_t Sampler_Grid::setSizeImage(int32_t w, int32_t h) {
	if (w <= 0 || h <= 0) return ERROR_ANY;
	
	// set image size
	Sampler::setSizeImage(w, h);

	// deallocate previous space
	// cudaFree(buffer_dir);
	// cudaFree(buffer_image);

	// to ensure that each kernel block is in same size
	// padding is used for buffer
	// therefore, size of buffer may be larger than direction vector list and image list
	//
	// CURRENT: actual buffer size depends on grid size
	// CURRENT: i.e. setSizeGrid is needed to be called before this function
	int32_t	w_padded = w;
	int32_t	h_padded = h;

	if (w % grid_w != 0) w_padded = w + grid_w;
	if (h % grid_h != 0) h_padded = h + grid_h;
	
	// allocate (device) space for buffer
	cudaMalloc(&buffer_dir, w_padded * h_padded * sizeof(Vec3f));
	cudaMalloc(&buffer_image, w_padded * h_padded * sizeof(Vec3f));

	return ERROR_NO;
}


// TODO: not yet completed
__host__ error_t Sampler_Grid::convertPreMapper(Vec3f *dir_list, int32_t size) {
	// from dir_list to buffer_dir
}


// TODO: not yet completed
__host__ error_t Sampler_Grid::convertPostMapper(Vec3f *image_list, int32_t size) {
	// from buffer_image to image_list
}


// Static Function Implementation
// ...
