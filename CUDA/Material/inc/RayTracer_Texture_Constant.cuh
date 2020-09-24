// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/14   initial update


#ifndef RAYTRACER_TEXTURE_CONSTANT_CUH
#define RAYTRACER_TEXTURE_CONSTANT_CUH


#include "RayTracer_Texture.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Constant: public Texture {
	// Data
	public:
		Vec3f   color   = Vec3f();

	// Operation
	public:
		// init
		__device__	Texture_Constant	();
		__device__	~Texture_Constant	();

		// interface
		__device__ virtual void	setPixel	(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void	_getPixel_	(Vec3f &dst, Vec3f *src) const override;

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


#endif  // RAYTRACER_TEXTURE_CONSTANT_CUH
