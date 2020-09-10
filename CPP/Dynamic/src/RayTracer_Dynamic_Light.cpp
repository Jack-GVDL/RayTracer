#include "../inc/RayTracer_Dynamic_Light.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ops
static void*		init_directional					();
static void*		init_point							();

static int			config_directional					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_point						(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_directional				(void *object, int type, void* *list, uint32_t size);
static int			interact_point						(void *object, int type, void* *list, uint32_t size);

// table
static int			config_directional_setOrientation	(void *object, uint8_t *data, uint32_t size);
static int			config_point_setAttenuation			(void *object, uint8_t *data, uint32_t size);


// Static Data
static std::vector<config_type_func_t>		table_config_light_directional;
static std::vector<config_type_func_t>		table_config_light_point;

static std::vector<interact_type_func_t>	table_interact_directional;
static std::vector<interact_type_func_t>	table_interact_point;


// Operation Handling
void RayTracer_Dynamic_Light_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_light_directional.push_back(	config_directional_setOrientation	);
	table_config_light_point.push_back(			config_point_setAttenuation	);

	// create type
	Dynamic_ContainerType *type;
	
	type = new Dynamic_ContainerType();
	type->setName("directional");
	type->setOps(init_directional, config_directional, interact_directional);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("point");
	type->setOps(init_point, config_point, interact_point);
	type_list->push_back(type);
}


void RayTracer_Dynamic_Light_info() {
}


void RayTracer_Dynamic_Light_del() {
}


// Static Function Implementation
// init
static void* init_directional() {
	SceneObject_Light_Directional *light = new SceneObject_Light_Directional();
	return light;
}


static void* init_point() {
	SceneObject_Light_Point *light = new SceneObject_Light_Point();
	return light;
}


// config
static int config_directional(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_light_directional, object, type, data, size);
}


static int config_point(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_light_point, object, type, data, size);
}


// interact
static int interact_directional(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_directional, object, type, list, size);
}


static int interact_point(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_point, object, type, list, size);
}


// table
static int config_directional_setOrientation(void *object, uint8_t *data, uint32_t size) {
	SceneObject_Light_Directional	*light			= (SceneObject_Light_Directional*)object;
	double							*orientation	= (double*)data;
	
	light->setOrientation(Vec3f(orientation[0], orientation[1], orientation[2]));
	return 0;
}


static int config_point_setAttenuation(void *object, uint8_t *data, uint32_t size) {
	SceneObject_Light_Point			*light			= (SceneObject_Light_Point*)object;
	double							*coeff			= (double*)data;

	light->setAttenuation(Vec3f(coeff[0], coeff[1], coeff[2]));
	return 0;
}
