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
static int			config_point_setAttenuationCoeff	(void *object, uint8_t *data, uint32_t size);


// Static Data
static config_type_func_t	config_table_light_directional		[]	= {
	config_directional_setOrientation
};

static config_type_func_t	config_table_light_point			[]	= {
	config_point_setAttenuationCoeff
};

static interact_type_func_t	interact_table_directional			[]	= {
	0
};

static interact_type_func_t	interact_table_point				[]	= {
	0
};


// Operation Handling
void RayTracer_Dynamic_Light_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// directional
	Dynamic_ContainerType	*type_directional	= new Dynamic_ContainerType();
	type_directional->ops_init		=	init_directional;
	type_directional->ops_config	=	config_directional;
	type_directional->ops_interact	=	interact_directional;
	type_list->push_back(type_directional);
	
	// point
	Dynamic_ContainerType	*type_point			= new Dynamic_ContainerType();
	type_point->ops_init			=	init_point;
	type_point->ops_config			=	config_point;
	type_point->ops_interact		=	interact_point;
	type_list->push_back(type_point);
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
	return DynamicUtil::configType(config_table_light_directional, object, type, data, size);
}


static int config_point(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_light_point, object, type, data, size);
}


// interact
static int interact_directional(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_directional, object, type, list, size);
}


static int interact_point(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_point, object, type, list, size);
}


// table
static int config_directional_setOrientation(void *object, uint8_t *data, uint32_t size) {
	SceneObject_Light_Directional	*light			= (SceneObject_Light_Directional*)object;
	double							*orientation	= (double*)data;
	
	light->setOrientation(Vec3f(orientation[0], orientation[1], orientation[2]));
	return 0;
}


static int config_point_setAttenuationCoeff(void *object, uint8_t *data, uint32_t size) {
	SceneObject_Light_Point			*light			= (SceneObject_Light_Point*)object;
	double							*coeff			= (double*)data;

	light->setAttenuationCoeff(Vec3f(coeff[0], coeff[1], coeff[2]));
	return 0;
}
