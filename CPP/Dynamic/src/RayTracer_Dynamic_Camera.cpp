#include "../inc/RayTracer_Dynamic_Camera.hpp"


// Define
// ...


// Typedef
typedef int(*config_func_table_t)(void *object, uint8_t *data, uint32_t size);


// Static Function Prototpye
static void*		init_camera_0						();
static int			config_camera_0						(void *object, int type, uint8_t *data, uint32_t size);

static inline int	config_table						(config_func_table_t *table, void *object, int type, uint8_t *data, uint32_t size);


// Static Data
static config_func_table_t	config_table_camera_0		[] = {0};


// Operation Handling
void RayTracer_Dynamic_Camera_init(std::vector<init_func_t>* init_list, std::vector<config_func_t>* config_list) {
	init_list->push_back(init_camera_0);

	config_list->push_back(config_camera_0);
}


void RayTracer_Dynamic_Camera_info() {
	
}


void RayTracer_Dynamic_Camera_del() {

}


// Static Function Implementation
// init
static void* init_camera_0() {
	Camera *camera = new Camera();
	return camera;
}


// config
static int config_camera_0(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_camera_0, object, type, data, size);
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
