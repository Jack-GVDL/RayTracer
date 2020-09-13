// Created by Jack Tse on 2020/06/09
// Follow TrackingStandard 0.1
//
// Log
// 2020/09/11   initial update


#ifndef RAYTRACER_RAY_CUH
#define RAYTRACER_RAY_CUH


#include "RayTracer_Vec3f.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Ray {
	// Data
	public:
		Vec3f pos;
		Vec3f dir;

	// Operation
	public:
		// init
		__host__ __device__ Ray() {}

		__host__ __device__ Ray(const Vec3f &pos, const Vec3f &dir): 
		pos(pos), dir(dir)
		{}

		__host__ __device__ Ray(const Ray &r): 
		pos(r.pos), dir(r.dir)
		{}

		// operation
		__host__ __device__  Vec3f 	getPosition		()			const { return pos; }
		__host__ __device__  Vec3f	getDirection	()			const { return dir; }
		__host__ __device__  Vec3f	pointAt			(fp_t t)	const { return pos + t * dir; }
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_RAY_CUH
