// Created by Jack Tse on 2020/06/30
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/30   initial update
// 2020/07/20   change to new structure


#ifndef RAYTRACER_SCATTER_EMITTER_HPP
#define RAYTRACER_SCATTER_EMITTER_HPP


#include "RayTracer_Scatter.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter_Emitter: public Scatter {
	// Datga
	public:
		Vec3f	color;
		
	// Operation
	public:
		// interface
		virtual ScatterState	scatter_shootRay	(RecordScatter *dst, RecordScatter *src, ScatterState state) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_EMITTER_HPP
