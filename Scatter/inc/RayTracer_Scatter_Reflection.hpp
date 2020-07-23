// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update
// 2020/07/20   change structure


#ifndef RAYTRACER_SCATTER_REFLECTION_HPP
#define RAYTRACER_SCATTER_REFLECTION_HPP


#include "RayTracer_Scatter.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter_Reflection: public Scatter {
	// Data
	public:
		Texture		*reflective	= nullptr;

	// Operation
	public:
		// init
		Scatter_Reflection(Texture *reflective):
		reflective	(reflective)
		{}

		// interface
		virtual ScatterState	scatter_shootRay	(RecordScatter *dst, RecordScatter *src, ScatterState state) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_REFLECTION_HPP
