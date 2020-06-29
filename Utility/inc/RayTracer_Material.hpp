// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update


#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP


#include "RayTracer_Ray.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Material {
	// Data
	public:
		Vec3f	emissive;
		Vec3f	ambient;
		Vec3f	specular;
		Vec3f	diffuse;
		Vec3f	reflective;
		Vec3f	transmissive;

		double	shininess;
		double	index;

	// Operation
	public:
		// init
		Material():
		emissive		(Vec3f(0.0, 0.0, 0.0)),
		ambient			(Vec3f(0.0, 0.0, 0.0)),
		specular		(Vec3f(0.4, 0.4, 0.0)),
		diffuse			(Vec3f(0.4, 0.2, 0.1)),
		reflective		(Vec3f(0.0, 0.0, 0.0)),
		transmissive	(Vec3f(0.0, 0.0, 0.0)),
		shininess		(0.5),
		index			(1.0)
		{}
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_MATERIAL_HPP
