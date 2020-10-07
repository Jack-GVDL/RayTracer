// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/07   initial update


#ifndef RAYTRACER_SCATTER_RANDOM_CUH
#define RAYTRACER_SCATTER_RANDOM_CUH


#include "RayTracer_Scatter.cuh"


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
		__device__	Scatter_Random	();
		__device__	~Scatter_Random	();

		// operation
		__device__	void	setRadius		(fp_t radius);
		__device__	void	setParallel		(int8_t is_parallel);
		__device__	void	setRaySize		(uint8_t count);

		// interface
		__device__ virtual void	scatter	(RecordRay *src, MemoryControl_Scatter *memory_control) const;
};



// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_RANDOM_CUH
