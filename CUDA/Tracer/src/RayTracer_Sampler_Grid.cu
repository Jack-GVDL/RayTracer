#include "../inc/RayTracer_Sampler_Grid.cuh"

// TODO: test
#include <stdio.h>


// Define
// ...


// Typedef
// ...


// Static Data
// ...


// Static Function Prototype
__global__ void	convert_pre_mapper	(fp_t *dst, fp_t *src, int32_t src_w, int32_t src_h,
									 int32_t block_w, int32_t block_h, int32_t grid_w, int32_t grid_h);
__global__ void	convert_post_mapper	(fp_t *dst, fp_t *src, int32_t dst_w, int32_t dst_h, 
									 int32_t block_w, int32_t block_h, int32_t grid_w, int32_t grid_h);


// Operation Handling
__host__ Sampler_Grid::Sampler_Grid():
grid_w(0),
grid_h(0)
{
}


__host__ Sampler_Grid::~Sampler_Grid()  {
}


__host__ error_t Sampler_Grid::setSizeGrid(int32_t w, int32_t h) {
	if (w <= 0 || h <= 0) return ERROR_ANY;

	this->block_w	= w;
	this->block_h	= h;

	update();
	return ERROR_NO;
}


// backup
/*
__host__ error_t Sampler_Grid::setSizeImage(int32_t w, int32_t h) {
	if (w <= 0 || h <= 0) return ERROR_ANY;
	
	// set image size
	Sampler::setSizeImage(w, h);

	update();
	return ERROR_NO;
}
*/


// TODO: current assume that size is known and size is now unless
__host__ error_t Sampler_Grid::convertPreMapper(fp_t *dir_list, int32_t size) {
	convert_pre_mapper <<< 1, block_w * block_h >>> (buffer_dir, dir_list, w, h, block_w, block_h, grid_w, grid_h);
	// cudaDeviceSynchronize();

	// TODO: test
	// printf("convertPreMapper \n");

	return ERROR_NO;
}


// TODO: current assume that size is known and size is now unless
__host__ error_t Sampler_Grid::convertPostMapper(fp_t *image_list, int32_t size) {
	convert_post_mapper <<< 1, block_w * block_h >>> (image_list, buffer_image, w, h, block_w, block_h, grid_w, grid_h);
	// cudaDeviceSynchronize();
	return ERROR_NO;
}


__host__ void Sampler_Grid::update() {
	// check if w, h, block_w, block_h is valid or not
	// update operation will run without error iff these variables are valid
	if (w == 0 || h == 0 || block_w == 0 || block_h == 0) return;

	// deallocate previous space
	cudaFree(buffer_dir);
	cudaFree(buffer_image);

	// to ensure that each kernel block is in same size
	// padding is used for buffer
	// therefore, size of buffer may be larger than direction vector list and image list
	//
	// CURRENT: actual buffer size depends on grid size
	// CURRENT: i.e. setSizeGrid is needed to be called before this function
	int32_t	w_padded = w;
	int32_t	h_padded = h;
	grid_w	= w / block_w;
	grid_h	= h / block_h;

	if (w % block_w != 0) ++grid_w;
	if (h % block_h != 0) ++grid_h;

	w_padded = grid_w * block_w;
	h_padded = grid_h * block_h;
	
	// allocate (device) space for buffer and set size
	buffer_dir_size		= w_padded * h_padded * 2 * sizeof(fp_t);
	buffer_image_size	= w_padded * h_padded * 3 * sizeof(fp_t);

	cudaMalloc(&buffer_dir,		buffer_dir_size);
	cudaMalloc(&buffer_image,	buffer_image_size);

	// set padded image size
	size_padded = w_padded * h_padded;
}


// Static Function Implementation
__global__ void convert_pre_mapper(
	fp_t *dst, fp_t *src, int32_t src_w, int32_t src_h,
	int32_t block_w, int32_t block_h, int32_t grid_w, int32_t grid_h) {

	// global index
	int	global_index	= blockIdx.x * blockDim.x + threadIdx.x;
	int	global_x		= global_index % block_w;
	int	global_y		= global_index / block_w;

	// TODO: test
	// printf("Pre mapper: %i %i, %i %i, %i %i \n", block_w, block_h, grid_w, grid_h, global_x, global_y);

	// TODO: currently offset is equal to block_w * block_h
	// but this limit the size of thread
	int32_t offset = block_w * block_h;
	int32_t i = 0;

	// for every grid
	for (int32_t y = 0; y < grid_h; ++y) {
		for (int32_t x = 0; x < grid_w; ++x) {

			// global xy
			const int32_t src_x = x * block_w + global_x; 
			const int32_t src_y = y * block_h + global_y;
			
			// TODO: test
			// if (global_index == 0) printf("%i %i %i %i \n", y, x, i, src_y * src_w + src_x);

			if (src_x > src_w || src_y > src_h)	{
				dst[(i + global_index) * 2 + 0] = 0.0;
				dst[(i + global_index) * 2 + 1] = 0.0;
			} else {
				dst[(i + global_index) * 2 + 0] = src[(src_y * src_w + src_x) * 2 + 0];
				dst[(i + global_index) * 2 + 1] = src[(src_y * src_w + src_x) * 2 + 1];
			}
			
			i += offset;
		}
	}
}


__global__ void convert_post_mapper(
	fp_t *dst, fp_t *src, int32_t dst_w, int32_t dst_h, 
	int32_t block_w, int32_t block_h, int32_t grid_w, int32_t grid_h) {

	// global index
	int	global_index	= blockIdx.x * blockDim.x + threadIdx.x;
	int	global_x		= global_index % block_w;
	int	global_y		= global_index / block_w;

	// TODO: currently offset is equal to block_w * block_h
	// but this limit the size of thread
	int32_t	offset = block_w * block_h;

	for (int32_t i = 0; i < grid_w * grid_h; ++i) {

		// grid xy
		const int32_t src_x = i % grid_w;
		const int32_t src_y = i / grid_w;

		// global xy
		const int32_t dst_x = src_x * block_w + global_x;
		const int32_t dst_y = src_y * block_h + global_y;

		if (dst_x < dst_w && dst_y < dst_h) {
			dst[(dst_y * dst_w + dst_x) * 3 + 0] = src[(i * offset + global_index) * 3 + 0];
			dst[(dst_y * dst_w + dst_x) * 3 + 1] = src[(i * offset + global_index) * 3 + 1];
			dst[(dst_y * dst_w + dst_x) * 3 + 2] = src[(i * offset + global_index) * 3 + 2];
		}

	}

	// TODO: test
	// printf("Enter \n");
}
