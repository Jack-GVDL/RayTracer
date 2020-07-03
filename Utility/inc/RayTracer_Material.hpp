// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update
// 2020/07/03   add scatter_list


#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP


#include <vector>
#include "RayTracer_Ray.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter;

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

		std::vector<Scatter*>	scatter_list;

	// Operation
	public:
		// init
		Material():
		emissive		(Vec3f(0.0, 0.0, 0.0)),
		ambient			(Vec3f(0.0, 0.0, 0.0)),
		specular		(Vec3f(0.4, 0.4, 0.4)),
		diffuse			(Vec3f(0.8, 0.8, 0.8)),
		reflective		(Vec3f(0.0, 0.0, 0.0)),
		transmissive	(Vec3f(0.0, 0.0, 0.0)),
		shininess		(0.5),
		index			(1.0)
		{}

		// operation
		bool	addScatter	(Scatter *scatter);
		bool	rmScatter	(Scatter *scatter);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_MATERIAL_HPP
