#include "../inc/RayTracer_Dynamic_Camera.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototpye
// ops
static void*		init_camera_0						();

static int			config_camera_0						(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_camera_0					(void *object, int type, void* *list, uint32_t size);

// table
// ...


// Static Data
static std::vector<config_type_func_t>		table_config_camera_0;

static std::vector<interact_type_func_t>	table_interact_camera_0;


// Operation Handling
void RayTracer_Dynamic_Camera_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	// ...

	// create type
	Dynamic_ContainerType *type;
	
	type = new Dynamic_ContainerType();
	type->setName("camera_0");
	type->setOps(init_camera_0, config_camera_0, interact_camera_0);
	type_list->push_back(type);
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
	return DynamicUtil::configType(&table_config_camera_0, object, type, data, size);
}


// interact
static int interact_camera_0(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_camera_0, object, type, list, size);
}


// table
// ...
