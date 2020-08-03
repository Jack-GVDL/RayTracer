#include "../inc/RayTracer_Dynamic_Hitable.hpp"


// Define
// ...


// Typedef
typedef int(*config_func_table_t)(void *object, uint8_t *data, uint32_t size);


// Static Function Prototype
static void*		init_sphere							();
static void*		init_trimesh						();

static int			config_sphere						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_trimesh						(void *object, int type, uint8_t *data, uint32_t size);

static inline int	config_table						(config_func_table_t *table, void *object, int type, uint8_t *data, uint32_t size);


// Static Data
static config_func_table_t	config_table_sphere			[] = {0};
static config_func_table_t	config_table_trimesh		[] = {0};


// Operation Handling
void RayTracer_Dynamic_Hitable_init(std::vector<init_func_t>* init_list, std::vector<config_func_t>* config_list) {
	init_list->push_back(init_sphere);
	init_list->push_back(init_trimesh);

	config_list->push_back(config_sphere);
	config_list->push_back(config_trimesh);
}


void RayTracer_Dynamic_Hitable_del() {

}


// Static Function Implementation
// init
static void* init_sphere() {
	SceneObject_Sphere *hitable = new SceneObject_Sphere();
	return hitable;
}


static void* init_trimesh() {
	SceneObject_Trimesh *hitable = new SceneObject_Trimesh();
	return hitable;
}


// config
static int config_sphere(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_sphere, object, type, data, size);
}


static int config_trimesh(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_trimesh, object, type, data, size);
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
// ...
