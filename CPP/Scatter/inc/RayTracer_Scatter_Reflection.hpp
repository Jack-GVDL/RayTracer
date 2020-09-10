// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update
// 2020/07/20   change structure
// 2020/07/30   add texture_list


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
	// Enum
	public:
		enum ScatterTexture {
			REFLECTIVE = 0,
			MAX
		};

	// Data
	public:
		// ...

	// Operation
	public:
		// init
		Scatter_Reflection();

	protected:
		// interface
		virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_REFLECTION_HPP
