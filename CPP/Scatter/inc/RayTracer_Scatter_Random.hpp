// Created by Jack Tse on 2020/08/28
//
// Log
// 2020/08/28   initial update


#ifndef RAYTRACER_SCATTER_RANDOM_HPP
#define RAYTRACER_SCATTER_RANDOM_HPP


#include "RayTracer_Scatter.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter_Random: public Scatter {
	// Enum
	public:
		enum ScatterTexture {
			MAX
		};

	// Data
	public:
		fp_t	radius			= 1;
		int8_t	is_parallel		= 1;
		uint8_t	count			= 5;

	// Operation
	public:
		// init
		Scatter_Random	();
		~Scatter_Random	();

		// operation
		void					setRadius			(fp_t radius);
		void					setParallel			(int8_t is_parallel);
		void					setRaySize			(uint8_t count);

		// interface
		virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_RANDOM_HPP
