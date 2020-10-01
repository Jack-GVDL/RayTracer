// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/01   initial update


#ifndef RAYTRACER_TEXTURE_CONVOLUTOR_CUH
#define RAYTRACER_TEXTURE_CONVOLUTOR_CUH


#include "RayTracer_Texture.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Convolutor: public Texture {
	// Data
	public:
		Texture		*texture		= nullptr;

		fp_t		*kernel			= nullptr;
		int32_t		kernel_width	= 0;

	// Operation
	public:
		// init
		__device__	Texture_Convolutor();
		__device__	~Texture_Convolutor();

		// operation
		__device__ void				setTexture	(Texture *texture);
		__device__ void				setKernel	(fp_t *kernel, int32_t width);  // width and height should be the same

		// interace
		__device__ virtual void		setPixel	(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void		_getPixel_	(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// ...
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_CONVOLUTOR_CUH
