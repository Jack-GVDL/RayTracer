// Created by Jack Tse on 2020/06/09
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/09   initial update


#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP


#include "RayTracer_Vec3f.hpp"


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
		Ray() {}

		Ray(const Vec3f &pos, const Vec3f &dir): 
		pos(pos), dir(dir)
		{}

		Ray(const Ray &r): 
		pos(r.pos), dir(r.dir)
		{}

		// operation
		Vec3f 	getPosition		()			const { return pos; }
		Vec3f	getDirection	()			const { return dir; }
		Vec3f	pointAt			(fp_t t)	const { return pos + t * dir; }
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_RAY_HPP
