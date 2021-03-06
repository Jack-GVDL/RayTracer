// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update


#ifndef RAYTRACER_SCATTER_REFRACTION_HPP
#define RAYTRACER_SCATTER_REFRACTION_HPP


#include "RayTracer_Scatter.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter_Refraction: public Scatter {
	// Operation
	public:
		// interface
		virtual ScatterState	scatter_shootRay	(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const override;

		// TODO: find a better way to solve this problem
		virtual ScatterState	scatter_buildTree	(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_REFRACTION_HPP
