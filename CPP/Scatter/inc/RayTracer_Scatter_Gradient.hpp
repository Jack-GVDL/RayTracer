// Created by Jack Tse on 2020/06/29
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/29   initial update
// 2020/07/30   add texture_list


#ifndef RAYTRACER_SCATTER_GRADIENT_HPP
#define RAYTRACER_SCATTER_GRADIENT_HPP


#include "RayTracer_Scatter.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter_Gradient: public Scatter {
	// Enum
	public:
		enum GradientSource {
			EMPTY,
			DIRECTION,
			POSITION,
			NORMAL,
			CUSTOM,
			SOURCE_MAX
		};

		enum ScatterTexture {
			MAX
		};

	// Data
	public:
		Vec3f			additor		= Vec3f(1);
		Vec3f			multiplier	= Vec3f(1);
		GradientSource	source		= DIRECTION;
		
		Vec3f			(*ops_source)(const Ray *ray) = nullptr;

	// Operation
	public:
		// init
		Scatter_Gradient()
		{}
		
		// interface
		virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_GRADIENT_HPP
