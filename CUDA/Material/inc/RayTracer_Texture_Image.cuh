// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/01   initial update


#ifndef RAYTRACER_TEXTURE_IMAGE_CUH
#define RAYTRACER_TEXTURE_IMAGE_CUH


#include "RayTracer_Texture.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Image: public Texture {
	// Data
	public:
		Vec3f		*color	= nullptr;
		int32_t		width	= 0;
		int32_t		height	= 0;

	// Operation
	public:
		// init
		__device__	Texture_Image();
		__device__	~Texture_Image();

		// interface
		__device__ virtual void		setPixel	(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void		_getPixel_	(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// ...
};


// TODO: change to this name later
typedef Texture_Image Texture_PixelMap;


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_IMAGE_CUH
