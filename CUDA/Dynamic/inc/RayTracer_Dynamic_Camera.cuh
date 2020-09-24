// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/24   initial update


#ifndef RAYTRACER_DYNAMIC_CAMERA_CUH
#define RAYTRACER_DYNAMIC_CAMERA_CUH


#include <vector>
#include "../../Tracer/Tracer.cuh"
#include "../inc/RayTracer_DynamicContainer.cuh"


// Define
// ...


// Typedef
// ...


// Enum
enum TypeCamera {
	CAMERA_DEFAULT  = 0,
	CAMERA_MAX
};


// Data Structure
// ...


// Macro Function
// ...


// Operation Handling
__host__ void	RayTracer_Dynamic_Camera_init	(std::vector<Dynamic_ContainerType*> *type_list);
__host__ void	RayTracer_Dynamic_Camera_info	();
__host__ void	RayTracer_Dynamic_Camera_del	();



// Inline Function Implementation
// ...


#endif	// RAYTRACER_DYNAMIC_CAMERA_CUH
