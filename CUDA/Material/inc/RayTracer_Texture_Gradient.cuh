// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/01   initial update


#ifndef RAYTRACER_GRADIENT_CUH
#define RAYTRACER_GRADIENT_CUH


#include "RayTracer_Texture.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Gradient: public Texture {
	// Enum
	public:
		enum GradientSource {
			EMPTY,
			DIRECTION,
			POSITION,
			CUSTOM,
			SOURCE_MAX
		};

	// Data
	public:
		Vec3f			additor		= Vec3f(1);
		Vec3f			multiplier	= Vec3f(1);
		GradientSource	source		= POSITION;

	// Operation
	public:
		// init
		__device__	Texture_Gradient();
		__device__	~Texture_Gradient();

		// interface
		__device__ virtual void		setPixel	(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void		_getPixel_	(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// ...
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_GRADIENT_CUH
