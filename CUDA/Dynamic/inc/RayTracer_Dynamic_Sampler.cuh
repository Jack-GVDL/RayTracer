// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/11/06   initial update


#ifndef RAYTRACER_DYNAMIC_SAMPLER_CUH
#define RAYTRACER_DYNAMIC_SAMPLER_CUH


#include "../../Tracer/Tracer.cuh"
#include "RayTracer_DynamicContainer.cuh"


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
__host__ void	RayTracer_Dynamic_Sampler_init	(std::vector<Dynamic_ContainerType*> *type_list);
__host__ void	RayTracer_Dynamic_Sampler_info	();
__host__ void	RayTracer_Dynamic_Sampler_del	();

__host__ error_t    Dynamic_Sampler_setSizeImage	(Sampler *sampler, int32_t w, int32_t h);


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAMIC_SAMPLER_CUH
