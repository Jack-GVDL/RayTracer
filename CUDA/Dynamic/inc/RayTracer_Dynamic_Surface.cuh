// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/24	initial update
// 2020/10/04   add Dynamic_Surface_XXX function


#ifndef RAYTRACER_DYNAMIC_SURFACE_CUH
#define RAYTRACER_DYNAMIC_SURFACE_CUH


#include <vector>
#include "../../Tracer/Tracer.cuh"
#include "../../Material/Material.cuh"
#include "../inc/RayTracer_DynamicContainer.cuh"


// Define
// ...


// Typedef
// ...


// Enum
enum TypeSurface {
	SURFACE_CONSTANT	= 0,
	SURFACE_IMAGE,
	SURFACE_MAX
};


// Data Structure
// ...


// Macro Function
// ...


// Operation Handling
__host__ void		RayTracer_Dynamic_Surface_init	(std::vector<Dynamic_ContainerType*> *type_list);
__host__ void		RayTracer_Dynamic_Surface_info	();
__host__ void		RayTracer_Dynamic_Surface_del	();

__host__ error_t	Dynamic_Surface_load			(Surface *surface);
__host__ error_t	Dynamic_Surface_dump			(Surface *surface);


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAMIC_SURFACE_CUH
