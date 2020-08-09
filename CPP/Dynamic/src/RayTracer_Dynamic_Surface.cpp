#include "../inc/RayTracer_Dynamic_Surface.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ops
static void*		init_constant						();
static void*		init_bmp							();

static int			config_constant						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_bmp							(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_constant					(void *object, int type, void* *list, uint32_t size);
static int			interact_bmp						(void *object, int type, void* *list, uint32_t size);

// table
static int			config_bmp_setPath					(void *object, uint8_t *data, uint32_t size);


// Static Data
// config
static config_type_func_t config_table_constant			[] = {
	0
};

static config_type_func_t config_table_bmp				[] = {
	config_bmp_setPath
};

// interact
static interact_type_func_t	interact_table_constant		[]	= {
	0
};

static interact_type_func_t	interact_table_bmp			[]	= {
	0
};


// Operation Handling
void RayTracer_Dynamic_Surface_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// constant
	Dynamic_ContainerType	*type_constant		= new Dynamic_ContainerType();
	type_constant->ops_init			= init_constant;
	type_constant->ops_config		= config_constant;
	type_constant->ops_interact		= interact_constant;
	type_list->push_back(type_constant);

	// bmp
	Dynamic_ContainerType	*type_bmp		= new Dynamic_ContainerType();
	type_bmp->ops_init				= init_bmp;
	type_bmp->ops_config			= config_bmp;
	type_bmp->ops_interact			= interact_bmp;
	type_list->push_back(type_bmp);
}


void RayTracer_Dynamic_Surface_info() {
	printf("Surface Type: \n");
	printf("0.  %s \n", "Constant");
	printf("1.  %s \n", "BMP");
}


void RayTracer_Dynamic_Surface_del() {

}


// Static Function Implementation
// init
static void* init_constant() {
	return nullptr;
}


static void* init_bmp() {
	Surface_BMP *surface = new Surface_BMP();
	return surface;
}


// config
static int config_constant(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_constant, object, type, data, size);
}


static int config_bmp(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_bmp, object, type, data, size);
}


// interact
static int interact_constant(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_constant, object, type, list, size);
}


static int interact_bmp(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_bmp, object, type, list, size);
}


// table
static int config_bmp_setPath(void *object, uint8_t *data, uint32_t size) {
	Surface_BMP	*surface	= (Surface_BMP*)object;
	const char	*path		= (const char*)data;

	// load bmp
	File_BMP *bmp = new File_BMP();
	if (!bmp->read(path)) {
		delete bmp;
		return -1;
	}

	surface->setBMP(bmp);
	return 0;
}

