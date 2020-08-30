// Created by Jack Tse on 2020/08/28
//
// Log
// 2020/08/28   initial update


#ifndef RAYTRACER_SCATTER_ANYHIT_HPP
#define RAYTRACER_SCATTER_ANYHIT_HPP


#include "RayTracer_Scatter.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter_AnyHit: public Scatter {
	// Enum
	public:
		enum ScatterTexture {
			MAX
		};

	// Data
	public:
		// ...

	// Operation
	public:
		// init
		Scatter_AnyHit		();
		~Scatter_AnyHit		();

		// interface
		virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;	
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_ANYHIT_HPP
