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
static config_type_func_t	config_table_camera_0		[]	= {
	0
};

static interact_type_func_t	interact_table_camera_0		[]	= {
	0
};


// Operation Handling
void RayTracer_Dynamic_Camera_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// camera 0
	Dynamic_ContainerType *type_camera_0 = new Dynamic_ContainerType();
	type_camera_0->ops_init		= init_camera_0;
	type_camera_0->ops_config	= config_camera_0;
	type_camera_0->ops_interact	= interact_camera_0;
	type_list->push_back(type_camera_0);
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
	return DynamicUtil::configType(config_table_camera_0, object, type, data, size);
}


// interact
static int interact_camera_0(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_camera_0, object, type, list, size);
}


// table
// ...
