// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/24	initial update
// 2020/10/04   add Dynamic_Hitable_XXX function


#ifndef RAYTRACER_DYNAMIC_HITABLE_CUH
#define RAYTRACER_DYNAMIC_HITABLE_CUH


#include <vector>
#include "../../Tracer/Tracer.cuh"
#include "../inc/RayTracer_DynamicContainer.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
// ...


// Macro Function
// ...


// Operation Handling
__host__ void		RayTracer_Dynamic_Hitable_init	(std::vector<Dynamic_ContainerType*> *type_list);
__host__ void		RayTracer_Dynamic_Hitable_info	();
__host__ void		RayTracer_Dynamic_Hitable_del	();

__host__ error_t	Dynamic_Hitable_setMaterial		(SceneObject_Hitable *hitable, Material *material);


// Inline Function Implementation
// ...


#endif	// RAYTRACER_DYNAMIC_HITABLE_CUH
