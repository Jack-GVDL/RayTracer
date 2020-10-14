// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/14   initial update


#ifndef RAYTRACER_MATERIAL_CUH
#define RAYTRACER_MATERIAL_CUH


#include "RayTracer_Texture.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter;


class Material {
	// Data
	public:
		Texture					*transmissive;
		fp_t					index;
		
		// backup
		// Texture					*index;

		// backup
		// Scatter*				*scatter_list;
		// int32_t					scatter_size;
		// int32_t					scatter_index;

		Vector					scatter_list;

	// Operation
	public:
		// init
		__device__	Material	();
		__device__	~Material	();

		// operation
		// backup
		// __device__ error_t	allocateScatter		(int32_t size);
		__device__ error_t	addScatter			(Scatter *scatter);
		__device__ error_t	rmScatter			(Scatter *scatter);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_MATERIAL_CUH
