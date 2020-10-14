// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/01   initial update


#ifndef RAYTRACER_TEXTURE_MATH_CUH
#define RAYTRACER_TEXTURE_MATH_CUH


#include "RayTracer_Texture.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Math_Additor: public Texture {
	// Data
	public:
		Vec3f	additor		= Vec3f(0);

	// Operation
	public:
		// init
		__device__	Texture_Math_Additor();
		__device__	~Texture_Math_Additor();

		// operation
		__device__ void				setAdditor      (const Vec3f &value);

		// interface
		__device__ virtual void		setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void		_getPixel_		(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// ...
};


class Texture_Math_Multiplier: public Texture {
	// Data
	public:
		Vec3f	multiplier	= Vec3f(1);

	// Operation
	public:
		// init
		__device__	Texture_Math_Multiplier();
		__device__	~Texture_Math_Multiplier();

		// operation
		__device__ void				setMultiplier	(const Vec3f &value);

		// interface
		__device__ virtual void		setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void		_getPixel_		(Vec3f &dst, Vec3f *src) const override;

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


#endif  // RAYTRACER_TEXTURE_MATH_CUH
