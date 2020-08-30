#include <stdio.h>
#include "../inc/RayTracer_Dynamic_Scatter.hpp"
#include "../inc/RayTracer_DynamicSkeleton.hpp"


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
static void*		init_random							();

static int			config_light						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_reflection					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_refraction					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_gradient						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_emitter						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_random						(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_light						(void *object, int type, void* *list, uint32_t size);
static int			interact_reflection					(void *object, int type, void* *list, uint32_t size);
static int			interact_refraction					(void *object, int type, void* *list, uint32_t size);
static int			interact_gradient					(void *object, int type, void* *list, uint32_t size);
static int			interact_emitter					(void *object, int type, void* *list, uint32_t size);
static int			interact_random						(void *object, int type, void* *list, uint32_t size);

// skeleton
Dynamic_constructTypeSkeleton(anyHit, Scatter, Scatter_AnyHit);

// table
static int			config_random_setRadius				(void *object, uint8_t *data, uint32_t size);
static int			config_random_setParallel			(void *object, uint8_t *data, uint32_t size);
static int			config_random_setRaySize			(void *object, uint8_t *data, uint32_t size);


// Static Data
static std::vector<config_type_func_t>		table_config_light;
static std::vector<config_type_func_t>		table_config_reflection;
static std::vector<config_type_func_t>		table_config_refraction;
static std::vector<config_type_func_t>		table_config_gradient;
static std::vector<config_type_func_t>		table_config_emitter;
static std::vector<config_type_func_t>		table_config_random;

static std::vector<interact_type_func_t>	table_interact_light;
static std::vector<interact_type_func_t>	table_interact_reflection;
static std::vector<interact_type_func_t>	table_interact_refraction;
static std::vector<interact_type_func_t>	table_interact_gradient;
static std::vector<interact_type_func_t>	table_interact_emitter;
static std::vector<interact_type_func_t>	table_interact_random;


// Operation Handling
void RayTracer_Dynamic_Scatter_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_random.push_back(	config_random_setRadius		);
	table_config_random.push_back(	config_random_setParallel	);
	table_config_random.push_back(	config_random_setRaySize	);

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
	type->setName("refraction");
	type->setOps(init_refraction, config_refraction, interact_refraction);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("gradient");
	type->setOps(init_gradient, config_gradient, interact_gradient);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("emitter");
	type->setOps(init_emitter, config_emitter, interact_emitter);
	type_list->push_back(type);

	type = new Dynamic_ContainerType();
	type->setName("random");
	type->setOps(init_random, config_random, interact_random);
	type_list->push_back(type);

	Dynamic_addType(anyHit, any_hit, type_list);
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


static void* init_random() {
	Scatter_Random *scatter = new Scatter_Random();
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


static int config_random(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_random, object, type, data, size);
}


// interact
static int interact_light(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_light, object, type, list, size);
}


static int interact_reflection(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_reflection, object, type, list, size);
}


static int interact_refraction(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_refraction, object, type, list, size);
}


static int interact_gradient(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_gradient, object, type, list, size);
}


static int interact_emitter(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_emitter, object, type, list, size);
}


static int interact_random(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_random, object, type, list, size);
}


// table
static int config_random_setRadius(void *object, uint8_t *data, uint32_t size) {
	Scatter_Random	*scatter	= (Scatter_Random*)object;
	double			radius		= ((double*)data)[0];
	scatter->setRadius((fp_t)radius);
	return 0;
}


static int config_random_setParallel(void *object, uint8_t *data, uint32_t size) {
	Scatter_Random	*scatter	= (Scatter_Random*)object;
	int				is_parallel	= ((int*)data)[0];
	scatter->setParallel(is_parallel ? 1 : 0);
	return 0;
}


static int config_random_setRaySize(void *object, uint8_t *data, uint32_t size) {
	Scatter_Random	*scatter	= (Scatter_Random*)object;
	int				count		= ((int*)data)[0];
	scatter->setRaySize((uint8_t)UtilMath::clamp<int>(0, count, 255));
	return 0;
}
