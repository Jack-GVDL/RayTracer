// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/19   initial update


#ifndef UTIL_RANDOM_CUH
#define UTIL_RANDOM_CUH


// TODO: rename to RayTracer_Base
#include "../inc/RayTracer_Base.cuh"
#include <curand.h>
#include <curand_kernel.h>


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Random {
// Data
public:
	curandState		state;

// Operation
public:
	__device__	Random	();
	__device__	~Random	();

	__device__ fp_t	randUniform	();
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // UTIL_RANDOM_CUH
