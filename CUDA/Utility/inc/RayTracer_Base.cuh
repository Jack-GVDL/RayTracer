// Created by Jack Tse on 2020/06/23
// Follow TrackingStandard 0.1
//
// Log
// 2020/09/11   initial update


#ifndef RAYTRACER_BASE_CUH
#define RAYTRACER_BASE_CUH


#include <stdint.h>


// Define
#define M_PI			3.14159265358979323846

#define RAY_EPSILON     0.0001
#define RAY_INDEX_AIR   1.0

#define ERROR_NO        0
#define ERROR_ANY       -1
#define ERROR_AT(i)     (ERROR_ANY - i)

#define FLOAT_MAX		FLT_MAX
#define FLOAT_MIN		FLT_MIN


// Typedef
// floating point: double or float
typedef float	fp_t;
typedef int8_t	error_t;


// Enum
// ...


// Data Structure
// ...


// Macro Function
// ...


// Inline Function Implementation
template <class T>
__host__ __device__ inline T min(T v1, T v2) {
	return v1 < v2 ? v1 : v2;
}


template <class T>
__host__ __device__ inline T max(T v1, T v2) {
	return v1 > v2 ? v1 : v2;
}


template <class T>
__host__ __device__ inline T abs(T v) {
	return v < 0 ? -v : v;
}


#endif  // RAYTRACER_BASE_CUH