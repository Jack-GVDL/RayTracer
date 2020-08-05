#include "../inc/RayTracer_Dynamic_Light.hpp"


// Define
// ...


// Typedef
typedef int(*config_func_table_t)(void *object, uint8_t *data, uint32_t size);


// Static Function Prototype
// init
static void*		init_directional					();
static void*		init_point							();

// config
static int			config_directional					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_point						(void *object, int type, uint8_t *data, uint32_t size);

// inline
static inline int	config_table						(config_func_table_t *table, void *object, int type, uint8_t *data, uint32_t size);

// table
static int			config_directional_setOrientation	(void *object, uint8_t *data, uint32_t size);
static int			config_point_setAttenuationCoeff	(void *object, uint8_t *data, uint32_t size);


// Static Data
static config_func_table_t	config_table_light_directional		[] = {
	config_directional_setOrientation};

static config_func_table_t	config_table_light_point			[] = {
	config_point_setAttenuationCoeff};


// Operation Handling
void RayTracer_Dynamic_Light_init(std::vector<init_func_t>* init_list, std::vector<config_func_t>* config_list) {
	init_list->push_back(init_directional);
	init_list->push_back(init_point);

	config_list->push_back(config_directional);
	config_list->push_back(config_point);
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
	return config_table(config_table_light_directional, object, type, data, size);
}


static int config_point(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_light_point, object, type, data, size);
}


// inline
static inline int config_table(config_func_table_t *table, void *object, int type, uint8_t *data, uint32_t size) {
	// if (table == nullptr) return -1;  // trust operation
	// if (object == nullptr) return -1;  // trust operation

	// TODO: currently no size checking
	// it has to be done outside this function
	return table[type](object, data, size);
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
