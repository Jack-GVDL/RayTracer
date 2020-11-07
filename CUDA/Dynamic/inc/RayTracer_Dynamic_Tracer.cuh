// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/24	initial update


#ifndef RAYTRACER_DYNAMIC_TRACER_CUH
#define RAYTRACER_DYNAMIC_TRACER_CUH


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
// TODO: may be rename to Dynamic_Tracer_init
// do the same thing for rest of the function
__host__ void		RayTracer_Dynamic_Tracer_init				();

__host__ error_t    Dynamic_Tracer_addScheduler					(int32_t size_memory);
// __host__ error_t	Dynamic_Tracer_resetScheduler				();

__host__ error_t    Dynamic_Tracer_setSampler                   (Sampler *sampler);

__host__ int		RayTracer_Dynamic_Tracer_tracePoint_RGB888	(int index_camera, void *data, int w, int h, int depth, int is_reverse_x, int is_reverse_y);
__host__ int		RayTracer_Dynamic_Tracer_tracePoint_RGB64F	(int index_camera, void *data, int w, int h, int depth, int is_reverse_x, int is_reverse_y);  // 64-bit floating point array, aka double


// Inline Function Implementation
// ...


#endif	// RAYTRACER_DYNAMIC_TRACER_CUH
