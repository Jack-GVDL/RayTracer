// Author: Jack Tse
// Email: jacktsetcy@gmail.com
//
// Log
// 2020/09/12   initial update


#ifndef RAYTRACER_SCATTER_LIGHT_CUH
#define RAYTRACER_SCATTER_LIGHT_CUH


#include "RayTracer_Scatter.cuh"
#include "RayTracer_Scatter_AnyHit.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter_Light: public Scatter {
	// Enum
	public:
		enum ScatterTexture {
			DIFFUSE = 0,
			SPECULAR,
			EMISSIVE,
			AMBIENT,
			SHININESS,
			NORMAL,
			MAX
		};

	// Data
	public:
		// ...

	// Operation
	public:
		// init
		__device__	Scatter_Light	();
		__device__	~Scatter_Light	();

	protected:
		// interface
		__device__ virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_LIGHT_CUH
