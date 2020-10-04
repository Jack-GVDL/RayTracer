// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/24   initial update
// 2020/10/04   add Dynamic_Camera_XXX function


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
__host__ void		RayTracer_Dynamic_Camera_init	(std::vector<Dynamic_ContainerType*> *type_list);
__host__ void		RayTracer_Dynamic_Camera_info	();
__host__ void		RayTracer_Dynamic_Camera_del	();

// cuda linker function
// __host__ void	Dynamic_Camera_setAll			(Camera *camera);
__host__ error_t	Dynamic_Camera_setLookFrom		(Camera *camera, const Vec3f look_from);
__host__ error_t	Dynamic_Camera_setLookAt		(Camera *camera, const Vec3f look_at);
__host__ error_t	Dynamic_Camera_setUpDirection	(Camera *camera, const Vec3f up);
__host__ error_t	Dynamic_Camera_setFOV			(Camera *camera, fp_t value);
__host__ error_t	Dynamic_Camera_setAspectRatio	(Camera *camera, fp_t value);


// Inline Function Implementation
// ...


#endif	// RAYTRACER_DYNAMIC_CAMERA_CUH
