// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/01   initial update


#ifndef RAYTRACER_TEXTURE_INPUT_CUH
#define RAYTRACER_TEXTURE_INPUT_CUH


#include "RayTracer_Texture.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Input: public Texture {
	// Data
	public:
		// ...

	// Operation
	public:	
		// init
		__device__	Texture_Input();
		__device__	~Texture_Input();

		// operation
		// ...

		// interface
		__device__ virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_INPUT_CUH
