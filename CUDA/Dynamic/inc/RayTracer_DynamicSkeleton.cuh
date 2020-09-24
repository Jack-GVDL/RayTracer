// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/15   initial update


#ifndef RAYTRACER_DYNAMICSKELETON_HPP
#define RAYTRACER_DYNAMICSKELETON_HPP


#include <vector>


// Define
// variable
#define Dynamic_Variable_tableConfig(name)		table_config_##name
#define Dynamic_Variable_tableInteract(name)	table_interact_##name

// function
#define Dynamic_Function_initCuda(name)			initCuda_##name
#define Dynamic_Function_configCuda(name)		configCuda_##name
#define Dynamic_Function_interactCuda(name)		interactCuda_##name

#define Dynamic_Function_init(name)				init_##name
#define Dynamic_Function_config(name)			config_##name
#define Dynamic_Function_interact(name)			interact_##name


// Macro Function
// type
#define Dynamic_constructTypeSkeleton(name, type_top, type_self)															\
																															\
																															\
static std::vector<config_type_func_t>		Dynamic_Variable_tableConfig(name);												\
static std::vector<interact_type_func_t>	Dynamic_Variable_tableInteract(name);											\
																															\
																															\
/* global function */																										\
__global__ void Dynamic_Function_initCuda(name)(void* *dst) {																\
	type_top *object = new type_self ();																					\
	*dst = object;																											\
}																															\
																															\
																															\
/* host function */																											\
__host__ static void* Dynamic_Function_init(name)() {																		\
	void *obj_device;																										\
	cudaMalloc(&obj_device, sizeof(void*));																					\
	Dynamic_Function_initCuda(name)<<< 1, 1 >>>(&obj_device);																\
	return obj_device;																										\
}																															\
																															\
																															\
__host__ static int Dynamic_Function_config(name)(void *object, int type, uint8_t *data, uint32_t size) {					\
	return DynamicUtil::configType(&Dynamic_Variable_tableConfig(name), object, type, data, size);							\
}																															\
																															\
																															\
__host__ static int Dynamic_Function_interact(name)(void *object, int type, void* *list, uint32_t size) {					\
	return DynamicUtil::interactType(&Dynamic_Variable_tableInteract(name), object, type, list, size);						\
}																															\


#define Dynamic_constructTypeConfigLinker(name, func)																		\
__host__ int Dynamic_Function_configCuda(name)(void *object, uint8_t *data, uint32_t size) {						\
	/* data */																												\
	uint8_t *data_device;																									\
	cudaMalloc(&data_device, size * sizeof(uint8_t));																		\
	cudaMemcpy(data_device, data, size * sizeof(uint8_t), cudaMemcpyHostToDevice);											\
																															\
	/* return value */																										\
	int8_t *ret_device;																										\
	cudaMalloc(&ret_device, sizeof(int8_t));																				\
																															\
	/* kernel function */																									\
	##func<<< 1, 1 >>>(ret_device, object, data_device, size);															\
																															\
	/* data */																												\
	cudaFree(data_device);																									\
																															\
	/* return value */																										\
	int8_t ret;																												\
	cudaMemcpy(&ret, ret_device, sizeof(int8_t), cudaMemcpyDeviceToHost);													\
	cudaFree(data_device);																									\
	return ret;																												\
}


#define Dynamic_constructInteractLinker(name_type, name_interact, func)														\
__host__ int Dynamic_Function_interactCuda(name)(void *object, void* *list, uint32_t size) {						\
	/* data */																												\
	void* *data_device;																										\
	cudaMalloc(&data_device, size * sizeof(void*));																			\
	cudaMemcpy(data_device, data, size * sizeof(void*), cudaMemcpyHostToDevice);											\
																															\
	/* return value */																										\
	int8_t *ret_device;																										\
	cudaMalloc(&ret_device, sizeof(int8_t));																				\
																															\
	/* kernel function */																									\
	##func<<< 1, 1 >>>(ret_device, object, data_device, size);															\
																															\
	/* data */																												\
	cudaFree(data_device);																									\
																															\
	/* return value */																										\
	int8_t ret;																												\
	cudaMemcpy(&ret, ret_device, sizeof(int8_t), cudaMemcpyDeviceToHost);													\
	cudaFree(data_device);																									\
	return ret;																												\
}


#define Dynamic_addType(name, tag, type_list)															\
type = new Dynamic_ContainerType();																		\
type->setName(#tag);																					\
type->setOps( 	Dynamic_Function_init(name), 															\
				Dynamic_Function_config(name), 															\
				Dynamic_Function_interact(name));														\
type_list->push_back(type);


#define Dynamic_addTypeConfig(name, func)																\
Dynamic_Variable_tableConfig(name).push_back(func);


#define Dynamic_addTypeInteract(name, func)																\
Dynamic_Variable_tableInteract(name).push_back(func)


#define Dynamic_addTypeConfigLinker(name, func)															\
Dynamic_addTypeConfig(name, Dynamic_Function_configCuda(func))


#define Dynamic_addTypeInteractLinker(name, func)														\
Dynamic_addTypeConfig(name, Dynamic_Function_interactCuda(func))


// type interface
// TODO: not yet completed


// Typedef
// ...


// Enum
// ...


// Data Structure
// ...


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAMICSKELETON_HPP
