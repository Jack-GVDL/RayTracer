// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/15   initial update
// 2020/10/28   change name to RIAS (Ray Intersectin Acceleration Structure)


#ifndef RAYTRACER_DYNAIC_RIAS_CUH
#define RAYTRACER_DYNAIC_RIAS_CUH


#include "../../Tracer/Tracer.cuh"
#include "../../RIAS/RIAS.cuh"
#include "../inc/RayTracer_DynamicContainer.cuh"


// Define
// ...


// Typedef
// ...


// Enum
enum TypeRIAS {
	RIAS_AABB	= 0,
	// RIAS_OCTREE,
	RIAS_MAX
};


// Data Structure
// ...


// Macro Function
// ...


// Operation Handling
__host__ void	RayTracer_Dynamic_RIAS_init		(std::vector<Dynamic_ContainerType*> *type_list);
__host__ void	RayTracer_Dynamic_RIAS_info		();
__host__ void	RayTracer_Dynamic_RIAS_del		();

__host__ error_t	Dynamic_RIAS_load	(RIAS *rias, SceneObject_Hitable* *hitable_list, int32_t size);


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAIC_RIAS_CUH
