// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update
// 2020/07/30   add texture_list


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
	// Enum
	public:
		enum ScatterTexture {
			MAX = 0
		};

	// Data
	public:
		// ...

	// Operation
	public:
		// init
		Scatter_Refraction();
		
	protected:
		// interface
		virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;

		// helper
		bool 					setRecord_outer		(RecordRay *dst, RecordRay *src, fp_t *index_from, fp_t *index_to) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_REFRACTION_HPP
