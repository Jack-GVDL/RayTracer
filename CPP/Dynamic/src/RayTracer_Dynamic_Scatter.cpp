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
// config
static config_type_func_t	config_table_light			[]	= {
	0
};

static config_type_func_t	config_table_reflection		[]	= {
	0
};

static config_type_func_t	config_table_refraction		[]	= {
	0
};

static config_type_func_t	config_table_gradient		[]	= {
	0
};

static config_type_func_t	config_table_emitter		[]	= {
	0
};

// interact
static interact_type_func_t interact_table_light		[]	= {
	0
};

static interact_type_func_t interact_table_reflection	[]	= {
	0
};

static interact_type_func_t interact_table_refraction	[]	= {
	0
};

static interact_type_func_t interact_table_gradient		[]	= {
	0
};

static interact_type_func_t interact_table_emitter		[]	= {
	0
};


// Operation Handling
void RayTracer_Dynamic_Scatter_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// light
	Dynamic_ContainerType	*type_light			= new Dynamic_ContainerType();
	type_light->ops_init			= init_light;
	type_light->ops_config			= config_light;
	type_light->ops_interact		= interact_light;
	type_list->push_back(type_light);

	// reflection
	Dynamic_ContainerType	*type_reflection	= new Dynamic_ContainerType();
	type_reflection->ops_init		= init_reflection;
	type_reflection->ops_config		= config_reflection;
	type_reflection->ops_interact	= interact_reflection;
	type_list->push_back(type_reflection);

	// refraction
	Dynamic_ContainerType	*type_refraction	= new Dynamic_ContainerType();
	type_refraction->ops_init		= init_refraction;
	type_refraction->ops_config		= config_refraction;
	type_refraction->ops_interact	= interact_refraction;
	type_list->push_back(type_refraction);

	// gradient
	Dynamic_ContainerType	*type_gradient		= new Dynamic_ContainerType();
	type_gradient->ops_init			= init_gradient;
	type_gradient->ops_config		= config_gradient;
	type_gradient->ops_interact		= interact_gradient;
	type_list->push_back(type_gradient);

	// emitter
	Dynamic_ContainerType	*type_emitter		= new Dynamic_ContainerType();
	type_emitter->ops_init			= init_emitter;
	type_emitter->ops_config		= config_emitter;
	type_emitter->ops_interact		= interact_emitter;
	type_list->push_back(type_emitter);
}


void RayTracer_Dynamic_Scatter_info() {
	printf("Scatter Type \n");
	printf("0.  %s \n", "Light");
	printf("1.  %s \n", "Reflection");
	printf("2.  %s \n", "Refraction");
	printf("3.  %s \n", "Gradient");
	printf("4.  %s \n", "Emitter");
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
	return DynamicUtil::configType(config_table_light, object, type, data, size);
}


static int config_reflection(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_reflection, object, type, data, size);
}


static int config_refraction(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_refraction, object, type, data, size);
}


static int config_gradient(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_gradient, object, type, data, size);
}


static int config_emitter(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_emitter, object, type, data, size);
}


// interact
static int interact_light(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_light, object, type, list, size);
}


static int interact_reflection(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_reflection, object, type, list, size);
}


static int interact_refraction(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_refraction, object, type, list, size);
}


static int interact_gradient(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_gradient, object, type, list, size);
}


static int interact_emitter(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_emitter, object, type, list, size);
}


// table
// ...
