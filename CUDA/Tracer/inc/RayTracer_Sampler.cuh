// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/11/05   initial update


#ifndef RAYTRACER_SAMPLER_CUH
#define RAYTRACER_SAMPLER_CUH


#include "../../Utility/Utility.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
// TODO: need more dynamic way to do the samething
// may be use chain object
class Sampler {
	// Data
	public:
		// buffer
		// reason why we need buffer is that if super sampling is used
		// size of direction vector list and image list will increase 
		Vec3f	*buffer_dir;
		Vec3f	*buffer_image;

		int32_t	buffer_dir_size;
		int32_t	buffer_image_size;

		int32_t	w, h;

		// kernel block size
		int32_t block_w, block_h;

	// Operation
	public:
		// __init__
		__host__	Sampler		();
		__host__	~Sampler	();

		// operation
		virtual __host__ error_t	setSizeImage		(int32_t w, int32_t h);
		virtual __host__ error_t	convertPreMapper	(Vec3f *dir_list, int32_t size) = 0;
		virtual __host__ error_t	convertPostMapper	(Vec3f *image_list, int32_t size) = 0;

	protected:
		virtual __host__ void		update				() = 0;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SAMPLER_CUH
