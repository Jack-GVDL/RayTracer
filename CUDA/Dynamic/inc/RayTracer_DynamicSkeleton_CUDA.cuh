// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/15   initial update
// 2020/09/28	relocation from RayTracer_DynamicSkeleton to RayTracer_DynamicSkeleton_CUDA


#ifndef RAYTRACER_DYNAMICSKELETON_CUDA_HPP
#define RAYTRACER_DYNAMICSKELETON_CUDA_HPP


#include <vector>


// Define
// variable
#define Dynamic_CUDA_Variable_tableConfig(name)			CUDA_table_config_##name
#define Dynamic_CUDA_Variable_tableInteract(name)		CUDA_table_interact_##name

// function
#define Dynamic_CUDA_Function_Global_init(name)			CUDA_Global_init_##name
#define Dynamic_CUDA_Function_Global_config(name)		CUDA_Global_config_##name
#define Dynamic_CUDA_Function_Global_interact(name)		CUDA_Global_interact_##name

#define Dynamic_CUDA_Function_Host_init(name)			CUDA_Host_init_##name
#define Dynamic_CUDA_Function_Host_config(name)			CUDA_Host_config_##name
#define Dynamic_CUDA_Function_Host_interact(name)		CUDA_Host_interact_##name

#define Dynamic_CUDA_Function_Linker_config(name)		CUDA_Linker_config_##name
#define Dynamic_CUDA_Function_Linker_interact(name)		CUDA_Linker_interact_##name


// Macro Function
// type
#define Dynamic_CUDA_constructTypeSkeleton(name, type_top, type_self)														\
																															\
																															\
static std::vector<config_type_func_t>		Dynamic_CUDA_Variable_tableConfig(name);										\
static std::vector<interact_type_func_t>	Dynamic_CUDA_Variable_tableInteract(name);										\
																															\
																															\
/* global function */																										\
__global__ void Dynamic_CUDA_Function_Global_init(name)(void* *dst) {														\
	type_top *object = new type_self ();																					\
	*dst = object;																											\
}																															\
																															\
																															\
/* host function */																											\
__host__ static void* Dynamic_CUDA_Function_Host_init(name)() {																\
	void *obj_device;																										\
	cudaMalloc(&obj_device, sizeof(void*));																					\
	Dynamic_CUDA_Function_Global_init(name)<<< 1, 1 >>>(&obj_device);														\
	return obj_device;																										\
}																															\
																															\
																															\
__host__ static int Dynamic_CUDA_Function_Host_config(name)(void *object, int type, uint8_t *data, uint32_t size) {			\
	return DynamicUtil::configType(&Dynamic_CUDA_Variable_tableConfig(name), object, type, data, size);						\
}																															\
																															\
																															\
__host__ static int Dynamic_CUDA_Function_Host_interact(name)(void *object, int type, void* *list, uint32_t size) {			\
	return DynamicUtil::interactType(&Dynamic_CUDA_Variable_tableInteract(name), object, type, list, size);					\
}																															\


#define Dynamic_CUDA_constructTypeConfigLinker(name, func)																	\
__host__ int Dynamic_CUDA_Function_Linker_config(name)(void *object, uint8_t *data, uint32_t size) {								\
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
	##func<<< 1, 1 >>>(ret_device, object, data_device, size);																\
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


#define Dynamic_CUDA_constructInteractLinker(name_type, name_interact, func)												\
__host__ int Dynamic_CUDA_Function_Linker_interact(name)(void *object, void* *list, uint32_t size) {								\
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
	##func<<< 1, 1 >>>(ret_device, object, data_device, size);																\
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


#define Dynamic_CUDA_addType(name, tag, type_list)														\
type = new Dynamic_ContainerType();																		\
type->setName(#tag);																					\
type->setOps( 	Dynamic_CUDA_Function_Host_init(name), 													\
				Dynamic_CUDA_Function_Host_config(name), 												\
				Dynamic_CUDA_Function_Host_interact(name));												\
type_list->push_back(type);


#define Dynamic_CUDA_addTypeConfig(name, func)															\
Dynamic_CUDA_Variable_tableConfig(name).push_back(func);


#define Dynamic_CUDA_addTypeInteract(name, func)														\
Dynamic_CUDA_Variable_tableInteract(name).push_back(func)


#define Dynamic_CUDA_addTypeConfigLinker(name, func)													\
Dynamic_CUDA_addTypeConfig(name, Dynamic_CUDA_Function_Linker_config(func))


#define Dynamic_CUDA_addTypeInteractLinker(name, func)													\
Dynamic_CUDA_addTypeInteract(name, Dynamic_CUDA_Function_Linker_interact(func))


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


#endif  // RAYTRACER_DYNAMICSKELETON_CUDA_HPP
