// Created by Jack Tse on 2020/06/29
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/29   initial update


#ifndef RAYTRACER_SCATTER_HIT_HPP
#define RAYTRACER_SCATTER_HIT_HPP


#include "RayTracer_Scatter.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter_Hit: public Scatter {
	// Data
	public:
		Vec3f	color	=	Vec3f(0, 0, 0);

	// Operation
	public:
		// interface
		virtual ScatterState	scatter_shootRay	(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_HIT_HPP
