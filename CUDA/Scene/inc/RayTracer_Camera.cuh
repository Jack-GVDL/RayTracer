// Author: Jack Tse
// Email: jacktsetcy@gmail.com
//
// Log
// 2020/09/12   initial update


#ifndef RAYTRACER_CAMERA_CUH
#define RAYTRACER_CAMERA_CUH


#include "../../Utility/Utility.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Camera {
	// Data
	protected:
		Vec3f	look_from;
		Vec3f	look_at, up;
		Vec3f	w, u, v;
		fp_t	fov, aspect;

		// backup
		// double	width, height;

	// Operation
	public:
		// init
		__device__	Camera	();
		__device__	Camera	(const Vec3f look_from, const Vec3f look_at, const Vec3f up, fp_t fov, fp_t aspect);

		// getter and setter
		__device__ void 	setLookFrom		(const Vec3f look_from);
		__device__ void		setLookAt		(const Vec3f look_at);
		__device__ void		setUpDirection	(const Vec3f up_dir);
		__device__ void 	setFOV			(fp_t value);
		__device__ void		setAspectRatio	(fp_t value);
		__device__ void		setAll			(const Vec3f look_from, const Vec3f look_at, const Vec3f up, fp_t fov, fp_t aspect);

		// operation
		__device__ Ray		getRay			(fp_t x, fp_t y) const;

	protected:
		// helper
		__device__ void		update			();
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_CAMERA_CUH
