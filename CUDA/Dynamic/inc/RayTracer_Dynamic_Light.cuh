// Author: Jack Tse
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/24	initial update
// 2020/10/04   add Dynamic_Light_XXX function


#ifndef RAYTRACER_DYNAMIC_LIGHT_CUH
#define RAYTRACER_DYNAMIC_LIGHT_CUH


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
__host__ void		RayTracer_Dynamic_Light_init	(std::vector<Dynamic_ContainerType*> *type_list);
__host__ void		RayTracer_Dynamic_Light_info	();
__host__ void		RayTracer_Dynamic_Light_del		();

__host__ error_t	Dynamic_Light_setOrigin			(SceneObject_Light *light, const Vec3f &origin);
__host__ error_t	Dynamic_Light_setColor			(SceneObject_Light *light, const Vec3f &color);


// Inline Function Implementation
// ...


#endif	// RAYTRACER_DYNAMIC_LIGHT_CUH