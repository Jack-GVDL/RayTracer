// Created by Jack Tse on 2020/07/28
//
// Log
// 2020/07/28   initial update
// 2020/08/09   change structure


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

EXPORT_DLL(void)	RayTracer_Test_testDoubleArray				(double *array, uint32_t size);
EXPORT_DLL(void)	RayTracer_Test_testUint8Array				(uint8_t *array, uint32_t size);
EXPORT_DLL(int)		RayTracer_Test_checkStatus					(int index, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Test_setPrintInfo					(int is_enabled);

EXPORT_DLL(int)     RayTracer_Sample_buildScene					(int index);

EXPORT_DLL(int)		RayTracer_Tracer_tracePoint					(int index_camera, double *pixel, double x, double y, int depth);
EXPORT_DLL(int)		RayTracer_Tracer_traceRect					(int index_camera, double *pixel, double w, double h, double pixel_w, double pixel_h, int depth);

EXPORT_DLL(int)		RayTracer_Camera_create						(int type);
EXPORT_DLL(int)		RayTracer_Camera_destroy					(int index);
EXPORT_DLL(int)		RayTracer_Camera_config						(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Camera_interact					(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Camera_setLookFrom				(int index, double *look_from);
EXPORT_DLL(int)		RayTracer_Camera_setLookAt					(int index, double *look_at);
EXPORT_DLL(int)		RayTracer_Camera_setUpDirection				(int index, double *up_dir);
EXPORT_DLL(int)		RayTracer_Camera_setFOV						(int index, double value);
EXPORT_DLL(int)		RayTracer_Camera_setAspectRatio				(int index, double value);

EXPORT_DLL(int)		RayTracer_Mapper_create						(int type);
EXPORT_DLL(int)		RayTracer_Mapper_destroy					(int index);
EXPORT_DLL(int)		RayTracer_Mapper_config						(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Mapper_interact					(int index, int type, int *index_list, int *type_list, uint32_t size);

EXPORT_DLL(int) 	RayTracer_Surface_create					(int type);
EXPORT_DLL(int) 	RayTracer_Surface_destroy					(int index);
EXPORT_DLL(int) 	RayTracer_Surface_config					(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Surface_interact					(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Surface_load						(int index);
EXPORT_DLL(int)		RayTracer_Surface_dump						(int index);

EXPORT_DLL(int) 	RayTracer_Texture_create					(int type);
EXPORT_DLL(int) 	RayTracer_Texture_destroy					(int index);
EXPORT_DLL(int) 	RayTracer_Texture_config					(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Texture_interact					(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Texture_addMapper					(int index_texture, int index_mapper);
EXPORT_DLL(int)		RayTracer_Texture_rmMapper					(int index_texture, int index_mapper);
EXPORT_DLL(int)		RayTracer_Texture_setPixel					(int index, const double *pixel, const double *point);
EXPORT_DLL(int)		RayTracer_Texture_getPixel					(int index, double *pixel, const double *point);

EXPORT_DLL(int) 	RayTracer_Scatter_create		            (int type);
EXPORT_DLL(int) 	RayTracer_Scatter_destroy		            (int index);
EXPORT_DLL(int) 	RayTracer_Scatter_config		            (int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Scatter_interact					(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Scatter_setTexture	            (int index_scatter, int index_texture, int offset);
EXPORT_DLL(int)		RayTracer_Scatter_rmTexture		            (int index_scatter, int offset);

EXPORT_DLL(int)		RayTracer_SceneObject_Hitable_create		(int type);
EXPORT_DLL(int) 	RayTracer_SceneObject_Hitable_destroy		(int index);
EXPORT_DLL(int)		RayTracer_SceneObject_Hitable_config		(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_SceneObject_Hitable_interact		(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int) 	RayTracer_SceneObject_Hitable_addScatter	(int index_hitable, int index_scatter);
EXPORT_DLL(int)		RayTracer_SceneObject_Hitable_rmScatter		(int index_hitable, int index_scatter);

EXPORT_DLL(int)		RayTracer_SceneObject_Light_create			(int type);
EXPORT_DLL(int)		RayTracer_SceneObject_Light_destroy			(int index);
EXPORT_DLL(int)		RayTracer_SceneObject_Light_config			(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_SceneObject_Light_interact		(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)     RayTracer_SceneObject_Light_setOrigin       (int index, double *origin);
EXPORT_DLL(int)		RayTracer_SceneObject_Light_setColor		(int index, double *color);

EXPORT_DLL(int)		RayTracer_Scene_addLight					(int index_light);
EXPORT_DLL(int)		RayTracer_Scene_addHitable					(int index_hitable);
EXPORT_DLL(int)		RayTracer_Scene_rmLight						(int index_light);
EXPORT_DLL(int)		RayTracer_Scene_rmHitable					(int index_hitable);


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAMIC_HPP
