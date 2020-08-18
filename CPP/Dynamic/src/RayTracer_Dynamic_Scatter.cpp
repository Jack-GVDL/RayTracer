#include <stdio.h>
#include "../inc/RayTracer_Dynamic_Scatter.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ops
static void*		init_light							();
static void*		init_reflection						();
static void*		init_refraction						();
static void*		init_gradient						();
static void*		init_emitter						();

static int			config_light						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_reflection					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_refraction					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_gradient						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_emitter						(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_light						(void *object, int type, void* *list, uint32_t size);
static int			interact_reflection					(void *object, int type, void* *list, uint32_t size);
static int			interact_refraction					(void *object, int type, void* *list, uint32_t size);
static int			interact_gradient					(void *object, int type, void* *list, uint32_t size);
static int			interact_emitter					(void *object, int type, void* *list, uint32_t size);

// table
// ...


// Static Data
static std::vector<config_type_func_t>		table_config_light;
static std::vector<config_type_func_t>		table_config_reflection;
static std::vector<config_type_func_t>		table_config_refraction;
static std::vector<config_type_func_t>		table_config_gradient;
static std::vector<config_type_func_t>		table_config_emitter;

static std::vector<interact_type_func_t>	interact_table_light;
static std::vector<interact_type_func_t>	interact_table_reflection;
static std::vector<interact_type_func_t>	interact_table_refraction;
static std::vector<interact_type_func_t>	interact_table_gradient;
static std::vector<interact_type_func_t>	interact_table_emitter;


// Operation Handling
void RayTracer_Dynamic_Scatter_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	// ...

	// create type
	Dynamic_ContainerType *type;
	
	type = new Dynamic_ContainerType();
	type->setName("light");
	type->setOps(init_light, config_light, interact_light);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("reflection");
	type->setOps(init_reflection, config_reflection, interact_reflection);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("reflection");
	type->setOps(init_reflection, config_reflection, interact_reflection);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("gradient");
	type->setOps(init_gradient, config_gradient, interact_gradient);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("emitter");
	type->setOps(init_emitter, config_emitter, interact_emitter);
	type_list->push_back(type);
}


void RayTracer_Dynamic_Scatter_info() {
}


void RayTracer_Dynamic_Scatter_del() {
}


// Static Function Implementation
// init
static void* init_light() {
	Scatter_Light *scatter = new Scatter_Light();
	return scatter;
}


static void* init_reflection() {
	Scatter_Reflection *scatter = new Scatter_Reflection();
	return scatter;
}


static void* init_refraction() {
	Scatter_Refraction *scatter = new Scatter_Refraction();
	return scatter;
}


static void* init_gradient() {
	Scatter_Gradient *scatter = new Scatter_Gradient();
	return scatter;
}


static void* init_emitter() {
	Scatter_Emitter *scatter = new Scatter_Emitter();
	return scatter;
}


// config
static int config_light(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_light, object, type, data, size);
}


static int config_reflection(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_reflection, object, type, data, size);
}


static int config_refraction(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_refraction, object, type, data, size);
}


static int config_gradient(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_gradient, object, type, data, size);
}


static int config_emitter(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_emitter, object, type, data, size);
}


// interact
static int interact_light(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&interact_table_light, object, type, list, size);
}


static int interact_reflection(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&interact_table_reflection, object, type, list, size);
}


static int interact_refraction(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&interact_table_refraction, object, type, list, size);
}


static int interact_gradient(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&interact_table_gradient, object, type, list, size);
}


static int interact_emitter(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&interact_table_emitter, object, type, list, size);
}


// table
// ...
