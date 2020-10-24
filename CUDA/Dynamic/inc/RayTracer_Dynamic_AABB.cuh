// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/15   initial update


#ifndef RAYTRACER_DYNAIC_AABB_CUH
#define RAYTRACER_DYNAIC_AABB_CUH


#include "../../Tracer/Tracer.cuh"
#include "../inc/RayTracer_DynamicContainer.cuh"


// Define
// ...


// Typedef
// ...


// Enum
enum TypeAABB {
	AABB_DEFAULT	= 0,
	AABB_MAX
};


// Data Structure
// ...


// Macro Function
// ...


// Operation Handling
__host__ void	RayTracer_Dynamic_AABB_init		(std::vector<Dynamic_ContainerType*> *type_list);
__host__ void	RayTracer_Dynamic_AABB_info		();
__host__ void	RayTracer_Dynamic_AABB_del		();

__host__ error_t Dynamic_AABB_load(Hitable_AABB *aabb, SceneObject_Hitable* *hitable_list, int32_t size);


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAIC_AABB_CUH
