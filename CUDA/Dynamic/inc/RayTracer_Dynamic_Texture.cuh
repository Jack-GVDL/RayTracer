// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/24	initial update


#ifndef RAYTRACER_DYNAMIC_TEXTURE_CUH
#define RAYTRACER_DYNAMIC_TEXTURE_CUH


#include <vector>
#include "../../Tracer/Tracer.cuh"
#include "../inc/RayTracer_DynamicContainer.cuh"


// Define
// ...


// Typedef
// ...


// Enum
enum TypeTexture {
	TEXTURE_CONSTANT	= 0,
	TEXTURE_CHECKERBOARD,
	TEXTURE_IMAGE,
	TEXTURE_MAX
};


// Data Structure
// ...


// Macro Function
// ...


// Operation Handling
__host__ void	RayTracer_Dynamic_Texture_init	(std::vector<Dynamic_ContainerType*> *type_list);
__host__ void	RayTracer_Dynamic_Texture_info	();
__host__ void	RayTracer_Dynamic_Texture_del	();


// Inline Function Implementation
// ...


#endif	// RAYTRACER_DYNAMIC_TEXTURE_CUH
