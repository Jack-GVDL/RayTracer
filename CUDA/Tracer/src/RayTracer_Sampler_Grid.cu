#include "../inc/RayTracer_Sampler_Grid.cuh"


// Define
// ...


// Typedef
// ...


// Static Data
// ...


// Static Function Prototype
__global__ void	convert_pre_mapper	(Vec3f *dst, Vec3f *src, int32_t src_w, int32_t src_h,
									 int32_t block_w, int32_t block_h, int32_t grid_w, int32_t grid_h);
__global__ void	convert_post_mapper	(Vec3f *dst, Vec3f *src, int32_t dst_w, int32_t dst_h, 
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
__host__ error_t Sampler_Grid::convertPreMapper(Vec3f *dir_list, int32_t size) {
	convert_pre_mapper <<< 1, block_w * block_h >>> (buffer_dir, dir_list, w, h, block_w, block_h, grid_w, grid_h);
	return ERROR_NO;
}


// TODO: current assume that size is known and size is now unless
__host__ error_t Sampler_Grid::convertPostMapper(Vec3f *image_list, int32_t size) {
	convert_post_mapper <<< 1, block_w * block_h >>> (buffer_image, image_list, w, h, block_w, block_h, grid_w, grid_h);
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

	if (w % block_w != 0) {
		w_padded = w + block_w;
		++grid_w;
	}
	if (h % block_h != 0) {
		h_padded = h + block_h;
		++grid_h;
	}
	
	// allocate (device) space for buffer and set size
	cudaMalloc(&buffer_dir, w_padded * h_padded * sizeof(Vec3f));
	cudaMalloc(&buffer_image, w_padded * h_padded * sizeof(Vec3f));

	buffer_dir_size		= w_padded * h_padded * sizeof(Vec3f);
	buffer_image_size	= w_padded * h_padded * sizeof(Vec3f);
}


// Static Function Implementation
__global__ void convert_pre_mapper(
	Vec3f *dst, Vec3f *src, int32_t src_w, int32_t src_h,
	int32_t block_w, int32_t block_h, int32_t grid_w, int32_t grid_h) {

	// global index
	int	global_index	= blockIdx.x * blockDim.x + threadIdx.x;
	int	global_x		= global_index % block_w;
	int	global_y		= global_index / block_w;

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

			if (src_x > src_w || src_y > src_h)	dst[i + global_index] = Vec3f(0);
			else								dst[i + global_index] = src[src_y * src_w + src_x];
		}

		i += offset;
	}
}


__global__ void convert_post_mapper(
	Vec3f *dst, Vec3f *src, int32_t dst_w, int32_t dst_h, 
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
		const int32_t dst_x = src_x + global_x;
		const int32_t dst_y = src_y + global_y;

		if (dst_x < dst_w && dst_y < dst_y) {
			dst[dst_y * dst_w + dst_x] = src[i * offset + global_index];
		}

	}
}
