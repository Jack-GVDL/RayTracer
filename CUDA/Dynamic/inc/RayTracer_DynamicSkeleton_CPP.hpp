// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/28   initial update


#ifndef RAYTRACER_DYNAMICSKELETON_CPP_HPP
#define RAYTRACER_DYNAMICSKELETON_CPP_HPP


// Define
// variable
#define Dynamic_CPP_Variable_tableConfig(name)		CPP_table_config_##name
#define Dynamic_CPP_Variable_tableInteract(name)	CPP_table_interact_##name

// function
#define Dynamic_CPP_Function_init(name)				CPP_init_##name
#define Dynamic_CPP_Function_config(name)			CPP_config_##name
#define Dynamic_CPP_Function_interact(name)			CPP_interact_##name


// Macro Function
// type
#define Dynamic_CPP_constructTypeSkeleton(name, type_top, type_self)										\
																											\
																											\
static std::vector<config_type_func_t>		Dynamic_CPP_Variable_tableConfig(name);							\
static std::vector<interact_type_func_t>	Dynamic_CPP_Variable_tableInteract(name);						\
																											\
																											\
static void* Dynamic_CPP_Function_init(name)() {															\
	type_top *object = new type_self ();																	\
	return object;																							\
}																											\
																											\
																											\
static int Dynamic_CPP_Function_config(name)(void *object, int type, uint8_t *data, uint32_t size) {		\
	return DynamicUtil::configType(&Dynamic_CPP_Variable_tableConfig(name), object, type, data, size);		\
}																											\
																											\
																											\
static int Dynamic_CPP_Function_interact(name)(void *object, int type, void* *list, uint32_t size) {		\
	return DynamicUtil::interactType(&Dynamic_CPP_Variable_tableInteract(name), object, type, list, size);	\
}																											\


#define Dynamic_CPP_addType(name, tag, type_list)														\
type = new Dynamic_ContainerType();																		\
type->setName(#tag);																					\
type->setOps( 	Dynamic_CPP_Function_init(name), 														\
				Dynamic_CPP_Function_config(name), 														\
				Dynamic_CPP_Function_interact(name));													\
type_list->push_back(type);


#define Dynamic_CPP_addTypeConfig(name, func)															\
Dynamic_CPP_Variable_tableConfig(name).push_back(func);


#define Dynamic_CPP_addTypeInteract(name, func)															\
Dynamic_CPP_Variable_tableInteract(name).push_back(func)


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


#endif  // RAYTRACER_DYNAMICSKELETON_CPP_HPP
