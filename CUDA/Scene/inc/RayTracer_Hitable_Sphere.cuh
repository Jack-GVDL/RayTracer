// Author: Jack Tse
// Email: jacktsetcy@gmail.com
//
// Log
// 2020/09/12   initial update


#ifndef RAYTRACER_HITABLE_SPHERE_CUH
#define RAYTRACER_HITABLE_SPHERE_CUH


#include "RayTracer_SceneObject_Hitable.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Hitable_Sphere: public SceneObject_Hitable {
	// Data
	public:
		Vec3f		center	= Vec3f();
		fp_t		radius	= 0;

	// Operation
	public:
		// init
		__device__ Hitable_Sphere	();
		__device__ ~Hitable_Sphere	();

		// operation
		__device__ void				setCenter			(const Vec3f &center);
		__device__ void				setRadius			(fp_t radius);

		// interface
		__device__ virtual int8_t	hit					(RecordHit *record, fp_t t_min, fp_t t_max) const override;
	
	protected:
		// operation
		__device__ void				updateBoundingBox	();
};


class Texture_Mapper_Sphere: public Texture {
	// Data
	public:
		Hitable_Sphere		*sphere	= nullptr;

	// Operation
	public:
		// init
		__device__ Texture_Mapper_Sphere	();
		__device__ ~Texture_Mapper_Sphere	();

		// operation
		__device__ void			setSphere		(Hitable_Sphere *sphere);

		// interfce
		__device__ virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// ...
};


class Texture_Direction_Sphere: public Texture {
	// Data
	public:
		Hitable_Sphere		*sphere = nullptr;

	// Operation
	public:
		// init
		__device__	Texture_Direction_Sphere	();
		__device__	~Texture_Direction_Sphere	();

		// operation
		__device__ void			setSphere		(Hitable_Sphere *sphere);

		// interfce
		__device__ virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;

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


#endif  // RAYTRACER_HITABLE_SPHERE_CUH
