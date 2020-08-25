// Created by Jack Tse on 2020/07/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/20   initial update


#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP


#include <vector>
#include "RayTracer_Texture.hpp"
#include "RayTracer_Texture_Constant.hpp"


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
		Texture					*transmissive;
		// Texture					*index;
		double					index;

	// Operation
	public:
		// init
		Material():
		transmissive	(new Texture_Constant()),
		index			(RAY_INDEX_AIR)
		{}
		
		Material(Texture *transmissive, double index):
		transmissive	(transmissive),
		index			(index)
		{}
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_MATERIAL_HPP
