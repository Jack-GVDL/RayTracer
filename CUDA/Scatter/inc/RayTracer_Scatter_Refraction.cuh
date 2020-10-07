// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/07/10   initial update


#ifndef RAYTRACER_SCATTER_REFRACTION_CUH
#define RAYTRACER_SCATTER_REFRACTION_CUH


#include "RayTracer_Scatter.cuh"


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
        __device__  Scatter_Refraction  ();
        __device__  ~Scatter_Refraction ();
		
	protected:
		// interface
		__device__ virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;

		// helper
		__device__ bool 				setRecord_outer		(RecordRay *dst, RecordRay *src, fp_t *index_from, fp_t *index_to) const;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_REFRACTION_CUH
