// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/24	initial update
// 2020/10/04   add Dynamic_Material_XXX function


#ifndef RAYTRACER_DYNAMIC_MATERIAL_CUH
#define RAYTRACER_DYNAMIC_MATERIAL_CUH


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
__host__ void		RayTracer_Dynamic_Material_init		(std::vector<Dynamic_ContainerType*> *type_list);
__host__ void		RayTracer_Dynamic_Material_info		();
__host__ void		RayTracer_Dynamic_Material_del		();

__host__ error_t	Dynamic_Material_addScatter			(Material *material, Scatter *scatter);
__host__ error_t	Dynamic_Material_rmScatter			(Material *material, Scatter *scatter);
__host__ error_t	Dynamic_Material_setTransmissive	(Material *material, const Vec3f &transmissive);
__host__ error_t	Dynamic_Material_setIndex			(Material *material, fp_t value);


// Inline Function Implementation
// ...


#endif	// RAYTRACER_DYNAMIC_MATERIAL_CUH