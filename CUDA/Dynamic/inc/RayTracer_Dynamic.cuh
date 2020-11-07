// Author: Jack Tse
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/24	initial update


#ifndef RAYTRACER_DYNAMIC_CUH
#define RAYTRACER_DYNAMIC_CUH


#include "../../Tracer/Tracer.cuh"
#include "../../RIAS/RIAS.cuh"
#include "../../External/External.hpp"


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
EXPORT_DLL(void)	RayTracer_init									();
EXPORT_DLL(void)	RayTracer_del									();
EXPORT_DLL(void)	RayTracer_info									();

EXPORT_DLL(void)	RayTracer_Test_testDoubleArray					(double *array, uint32_t size);
EXPORT_DLL(void)	RayTracer_Test_testUint8Array					(uint8_t *array, uint32_t size);
EXPORT_DLL(int)		RayTracer_Test_checkStatus						(int index, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Test_setPrintInfo						(int is_enabled);

// TODO: NOT backup
// EXPORT_DLL(int)		RayTracer_Tracer_tracePoint					(int index_camera, void *pixel, double x, double y, int depth, int format);
EXPORT_DLL(int)		RayTracer_Tracer_traceRect						(int index_camera, void *pixel, int w, int h, int depth, int is_reverse_x, int is_reverse_y, int format);
EXPORT_DLL(int)		RayTracer_Tracer_setSampler						(int index_sampler);

EXPORT_DLL(int)		RayTracer_Camera_Type_getIndex					(const char *name);
EXPORT_DLL(int)		RayTracer_Camera_create							(int type);
EXPORT_DLL(int)		RayTracer_Camera_destroy						(int index);
EXPORT_DLL(int)		RayTracer_Camera_config							(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Camera_interact						(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Camera_setLookFrom					(int index, double *look_from);
EXPORT_DLL(int)		RayTracer_Camera_setLookAt						(int index, double *look_at);
EXPORT_DLL(int)		RayTracer_Camera_setUpDirection					(int index, double *up_dir);
EXPORT_DLL(int)		RayTracer_Camera_setFOV							(int index, double value);
EXPORT_DLL(int)		RayTracer_Camera_setAspectRatio					(int index, double value);

EXPORT_DLL(int)		RayTracer_Surface_Type_getIndex					(const char *name);
EXPORT_DLL(int)		RayTracer_Surface_create						(int type);
EXPORT_DLL(int)		RayTracer_Surface_destroy						(int index);
EXPORT_DLL(int)		RayTracer_Surface_config						(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Surface_interact						(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Surface_load							(int index);
EXPORT_DLL(int)		RayTracer_Surface_dump							(int index);

EXPORT_DLL(int)		RayTracer_Texture_Type_getIndex					(const char *name);
EXPORT_DLL(int)		RayTracer_Texture_create						(int type);
EXPORT_DLL(int)		RayTracer_Texture_destroy						(int index);
EXPORT_DLL(int)		RayTracer_Texture_config						(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Texture_interact						(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Texture_addInput						(int index_output, int index_input, int offset);
EXPORT_DLL(int)		RayTracer_Texture_rmInput						(int index_output, int offset);
EXPORT_DLL(int)		RayTracer_Texture_setPixel						(int index, const double *pixel, const double *point);
EXPORT_DLL(int)		RayTracer_Texture_getPixel						(int index, double *pixel, const double *point);

EXPORT_DLL(int)		RayTracer_Material_Type_getIndex				(const char *name);
EXPORT_DLL(int)		RayTracer_Material_addScatter					(int index, int index_scatter);
EXPORT_DLL(int)		RayTracer_Material_rmScatter					(int index, int index_scatter);
EXPORT_DLL(int)		RayTracer_Material_setTransmissive				(int index, double *transmissive);
EXPORT_DLL(int)		RayTracer_Material_setIndex						(int index, double value);

EXPORT_DLL(int)		RayTracer_Scatter_Type_getIndex					(const char *name);
EXPORT_DLL(int)		RayTracer_Scatter_create						(int type);
EXPORT_DLL(int)		RayTracer_Scatter_destroy						(int index);
EXPORT_DLL(int)		RayTracer_Scatter_config						(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Scatter_interact						(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Scatter_addScatter					(int index, int index_scatter);
EXPORT_DLL(int)		RayTracer_Scatter_rmScatter						(int index, int index_scatter);
EXPORT_DLL(int)		RayTracer_Scatter_setTexture					(int index_scatter, int index_texture, int offset);

EXPORT_DLL(int)		RayTracer_Hitable_Type_getIndex					(const char *name);
EXPORT_DLL(int)		RayTracer_Hitable_create						(int type);
EXPORT_DLL(int)		RayTracer_Hitable_destroy						(int index);
EXPORT_DLL(int)		RayTracer_Hitable_config						(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Hitable_interact						(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Hitable_setMaterial					(int index_hitable, int index_material);

EXPORT_DLL(int)		RayTracer_RIAS_create							(int type);
EXPORT_DLL(int)		RayTracer_RIAS_destroy							(int index);
EXPORT_DLL(int)		RayTracer_RIAS_config							(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_RIAS_interact							(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_RIAS_load								(int index);

EXPORT_DLL(int)		RayTracer_Light_Type_getIndex					(const char *name);
EXPORT_DLL(int)		RayTracer_Light_create							(int type);
EXPORT_DLL(int)		RayTracer_Light_destroy							(int index);
EXPORT_DLL(int)		RayTracer_Light_config							(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Light_interact						(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Light_setOrigin						(int index, double *origin);
EXPORT_DLL(int)		RayTracer_Light_setColor						(int index, double *color);

EXPORT_DLL(int)		RayTracer_Scene_addLight						(int index_light);
EXPORT_DLL(int)		RayTracer_Scene_addHitable						(int index_hitable);
EXPORT_DLL(int)		RayTracer_Scene_addRIAS							(int index_aabb);
EXPORT_DLL(int)		RayTracer_Scene_rmLight							(int index_light);
EXPORT_DLL(int)		RayTracer_Scene_rmHitable						(int index_hitable);
EXPORT_DLL(int)		RayTracer_Scene_rmRIAS							(int index_aabb);

EXPORT_DLL(int)		RayTracer_Sampler_Type_getIndex					(const char *name);
EXPORT_DLL(int)		RayTracer_Sampler_create						(int type);
EXPORT_DLL(int)		RayTracer_Sampler_destroy						(int index);
EXPORT_DLL(int)		RayTracer_Sampler_config						(int index, int type, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Sampler_interact						(int index, int type, int *index_list, int *type_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Sampler_setSizeImage					(int index, int32_t w, int32_t h);


// TODO: future: standarded object interface in order to reduce number of interface
/*
EXPORT_DLL(int)		RayTracer_Dynamic_getType						(const char* *name_list, uint32_t size);
EXPORT_DLL(int)		RayTracer_Dynamic_create						(int type, uint32_t size);
EXPORT_DLL(int)		RayTracer_Dynamic_destroy						(int index);
EXPORT_DLL(int)		RayTracer_Dynamic_config						(int index, int type, int index_config, uint8_t *data, uint32_t size);
EXPORT_DLL(int)		RayTracer_Dynamic_interact						(int index, int type, int index_interact, int *object_list, int *type_list, uint32_t size);
*/


// Inline Function Implementation
// ...


#endif	// RAYTRACER_DYNAMIC_CUH
