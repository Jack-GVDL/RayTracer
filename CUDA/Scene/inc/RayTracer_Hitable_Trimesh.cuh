// Author: Jack Tse
// Email: jacktsetcy@gmail.com
//
// Log
// 2020/09/12   initial update


#ifndef RAYTRACER_HITABLE_TRIMESH_CUH
#define RAYTRACER_HITABLE_TRIMESH_CUH


#include "../../Material/Material.cuh"
#include "RayTracer_SceneObject_Hitable.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Hitable_Trimesh: public SceneObject_Hitable {
	// Data
	public:
		Vec3f	point[3];

	// Operation
	public:
		// init
		__device__	Hitable_Trimesh		();
		__device__	~Hitable_Trimesh	();

		// operation
		__device__ void				setPoint			(const Vec3f &p0, const Vec3f &p1, const Vec3f &p2);

		// interface
		__device__ virtual int8_t	hit					(RecordHit *record, fp_t t_min, fp_t t_max) const override;

	protected:
		// operation
		__device__ void				updateBoundingBox	();
};


class Texture_Mapper_Trimesh: public Texture {
	// Data
	public:
		Hitable_Trimesh		*trimesh	= nullptr;

	// Operation
	public:
		// init
		__device__	Texture_Mapper_Trimesh	();
		__device__	~Texture_Mapper_Trimesh	();

		// operation
		__device__ void			setTrimesh		(Hitable_Trimesh *trimesh);

		// interfce
		__device__ virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// ...
};


class Texture_Direction_Trimesh: public Texture {
	// Data
	public:
		Hitable_Trimesh		*trimesh	= nullptr;

	// Operation
	public:
		// init
		__device__	Texture_Direction_Trimesh	();
		__device__	~Texture_Direction_Trimesh	();

		// operation
		__device__ void			setTrimesh		(Hitable_Trimesh *trimesh);

		// interfce
		__device__ virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// ...
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_HITABLE_TRIMESH_CUH
