// Created by Jack Tse on 2020/07/28
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/28   initial update


#ifndef RAYTRACER_DYNAMIC_HPP
#define RAYTRACER_DYNAMIC_HPP


#include <stdint.h>
#include "../../Tracer/Tracer.hpp"


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
EXPORT_DLL(void)	RayTracer_init								();
EXPORT_DLL(void)	RayTracer_del								();
EXPORT_DLL(void)	RayTracer_info								();

EXPORT_DLL(void)	RayTracer_trace								(double *pixel, double x, double y, int depth);

EXPORT_DLL(int) 	RayTracer_Surface_create					(int type);
EXPORT_DLL(int) 	RayTracer_Surface_destroy					(int index);
EXPORT_DLL(int) 	RayTracer_Surface_config					(int index, int type, uint8_t *data, uint32_t size);

EXPORT_DLL(int) 	RayTracer_Texture_create					(int type);
EXPORT_DLL(int) 	RayTracer_Texture_destroy					(int index);
EXPORT_DLL(int)		RayTracer_Texture_setPixel					(int index, double *point, double *pixel);
EXPORT_DLL(int)		RayTracer_Texture_getPixel					(int index, double *point);
EXPORT_DLL(int) 	RayTracer_Texture_config					(int index, int type, uint8_t *data, uint32_t size);

EXPORT_DLL(int) 	RayTracer_Scatter_create		            (int type);
EXPORT_DLL(int) 	RayTracer_Scatter_destroy		            (int index);
EXPORT_DLL(int)		RayTracer_Scatter_addTexture	            (int index_scatter, int index_texture, int offset);
EXPORT_DLL(int)		RayTracer_Scatter_rmTexture		            (int index_scatter, int index_texture);
EXPORT_DLL(int) 	RayTracer_Scatter_config		            (int index, int type, uint8_t *data, uint32_t size);

EXPORT_DLL(int)		RayTracer_SceneObject_Hitable_create		(int type);
EXPORT_DLL(int) 	RayTracer_SceneObject_Hitable_destroy		(int index);
EXPORT_DLL(int) 	RayTracer_SceneObject_Hitable_addScatter	(int index_hitable, int index_scatter);
EXPORT_DLL(int)		RayTracer_SceneObject_Hitable_rmScatter		(int index_hitable, int index_scatter);
EXPORT_DLL(int)		RayTracer_SceneObject_Hitable_config		(int index, int type, uint8_t *data, uint32_t size);


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAMIC_HPP
