// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/14   initial update


#ifndef RAYTRACER_TEXTURE_CUH
#define RAYTRACER_TEXTURE_CUH


#include "../../Utility/Utility.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture {
	// Data
	public:
		// better to call it mapper_chain
		// as order matter
		// std::vector<Mapper*>	mapper_list;
		Texture*				*input_list		= nullptr;
		int32_t					input_size		= 0;

	// Operation
	public:
		// init
		__device__	Texture		();
		__device__	~Texture	();

		// operation
		__device__ error_t			addInput	(Texture *texture, int32_t index);
		__device__ error_t			rmInput		(int32_t index);

		__device__ void				getPixel	(Vec3f &dst, const Vec3f &src) const;

		// interface
		__device__ virtual void		setPixel	(const Vec3f &point, const Vec3f &pixel) = 0;
		__device__ virtual void		_getPixel_	(Vec3f &dst, Vec3f *src) const = 0;

	protected:
		// interface
		// ...
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_CUH
