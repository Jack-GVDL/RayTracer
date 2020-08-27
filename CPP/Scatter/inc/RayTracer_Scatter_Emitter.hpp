// Created by Jack Tse on 2020/06/30
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/30   initial update
// 2020/07/20   change to new structure
// 2020/07/30   add texture_list


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
	// Enum
	public:
		enum ScatterTexture {
			MAX
		};

	// Data
	public:
		Vec3f	color;
		
	// Operation
	public:
		// init
		Scatter_Emitter()
		{}
		
		// interface
		virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_EMITTER_HPP
