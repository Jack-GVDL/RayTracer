#include "../inc/RayTracer_Dynamic_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ops
static void*		init_constant						();
static void*		init_checkerboard					();
static void*		init_image							();

static int			config_constant						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_checkerboard					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_image						(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_constant					(void *object, int type, void* *list, uint32_t size);
static int			interact_checkerboard				(void *object, int type, void* *list, uint32_t size);
static int			interact_image						(void *object, int type, void* *list, uint32_t size);

// table
static int			config_checkerboard_setBoardSize	(void *object, uint8_t *data, uint32_t size);


// Static Data
// config
static config_type_func_t	config_table_constant		[]	= {
	0
};

static config_type_func_t	config_table_checkerboard	[]	= {
	config_checkerboard_setBoardSize
};

static config_type_func_t	config_table_image			[]	= {
	0};

// interact
static interact_type_func_t	interact_table_constant		[]	= {
	0
};

static interact_type_func_t	interact_table_checkerboard	[]	= {
	0
};

static interact_type_func_t	interact_table_image		[]	= {
	0
};


// Operation Handling
void RayTracer_Dynamic_Texture_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// constant
	Dynamic_ContainerType	*type_constant		= new Dynamic_ContainerType();
	type_constant->ops_init			= init_constant;
	type_constant->ops_config		= config_constant;
	type_constant->ops_interact		= interact_constant;
	type_list->push_back(type_constant);

	// checkerboard
	Dynamic_ContainerType	*type_checkerboard	= new Dynamic_ContainerType();
	type_checkerboard->ops_init		= init_checkerboard;
	type_checkerboard->ops_config	= config_checkerboard;
	type_checkerboard->ops_interact	= interact_checkerboard;
	type_list->push_back(type_checkerboard);

	// image
	Dynamic_ContainerType	*type_image			= new Dynamic_ContainerType();
	type_image->ops_init			= init_image;
	type_image->ops_config			= config_image;
	type_image->ops_interact		= interact_image;
	type_list->push_back(type_image);
}


void RayTracer_Dynamic_Texture_info() {
	printf("Texture Type \n");
	printf("0.  %s \n", "Constant");
	printf("1.  %s \n", "Checkerboard");
	printf("2.  %s \n", "Image");
}


void RayTracer_Dynamic_Texture_del() {

}


// Static Function Implementation
// init
static void* init_constant() {
	Texture_Constant *texture = new Texture_Constant();
	return texture;
}


static void* init_checkerboard() {
	Texture_CheckerBoard *texture = new Texture_CheckerBoard();
	return texture;
}


static void* init_image() {
	Texture_Image *texture = new Texture_Image();
	return texture;
}


// config
static int config_constant(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_constant, object, type, data, size);
}


static int config_checkerboard(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_checkerboard, object, type, data, size);
}


static int config_image(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_image, object, type, data, size);
}


// interact
static int interact_constant(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_constant, object, type, list, size);
}


static int interact_checkerboard(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_checkerboard, object, type, list, size);
}


static int interact_image(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_image, object, type, list, size);
}


// table
static int config_checkerboard_setBoardSize(void *object, uint8_t *data, uint32_t size) {
	Texture_CheckerBoard	*texture	= (Texture_CheckerBoard*)object;
	double					*vec		= (double*)data;
	texture->setBoardSize(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}
