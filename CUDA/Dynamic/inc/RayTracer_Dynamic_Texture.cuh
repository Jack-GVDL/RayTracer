// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/24	initial update
// 2020/10/04   add Dynamic_Texture_XXX function


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
__host__ void		RayTracer_Dynamic_Texture_init	(std::vector<Dynamic_ContainerType*> *type_list);
__host__ void		RayTracer_Dynamic_Texture_info	();
__host__ void		RayTracer_Dynamic_Texture_del	();

__host__ error_t	Dynamic_Texture_addInput		(Texture *texture, Texture *input, int32_t offset);
__host__ error_t	Dynamic_Texture_rmInput			(Texture *texture, int32_t offset);
__host__ error_t	Dynamic_Texture_setPixel		(Texture *texture, const Vec3f &point, const Vec3f &pixel);
__host__ error_t	Dynamic_Texture_getPixel		(Texture *texture, Vec3f &dst, const Vec3f &src);


// Inline Function Implementation
// ...


#endif	// RAYTRACER_DYNAMIC_TEXTURE_CUH
