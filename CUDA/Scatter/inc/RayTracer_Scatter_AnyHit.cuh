// Author: Jack Tse
// Email: jacktsetcy@gmail.com
//
// Log
// 2020/09/12   initial update


#ifndef RAYTRACER_SCATTER_ANYHIT_CUH
#define RAYTRACER_SCATTER_ANYHIT_CUH


#include "RayTracer_Scatter.cuh"


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
		__device__	Scatter_AnyHit		();
		__device__	~Scatter_AnyHit		();

		// interface
		__device__ virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;	
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_ANYHIT_CUH
