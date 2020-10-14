// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/07   initial update


#ifndef RAYTRACER_SCATTER_REFLECTION_CUH
#define RAYTRACER_SCATTER_REFLECTION_CUH


#include "RayTracer_Scatter.cuh"


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
        __device__  Scatter_Reflection  ();
        __device__  ~Scatter_Reflection ();

	protected:
		// interface
		__device__ virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_REFLECTION_CUH
