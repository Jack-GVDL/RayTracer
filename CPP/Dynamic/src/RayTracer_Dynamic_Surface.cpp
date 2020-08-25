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

static int			interact_bmp_convertToTexture		(void *object, void* *list, uint32_t size);

// Static Data
static std::vector<config_type_func_t>		table_config_constant;
static std::vector<config_type_func_t>		table_config_bmp;

static std::vector<interact_type_func_t>	table_interact_constant;
static std::vector<interact_type_func_t>	table_interact_bmp;


// Operation Handling
void RayTracer_Dynamic_Surface_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_bmp.push_back(		config_bmp_setPath				);

	table_interact_bmp.push_back(	interact_bmp_convertToTexture	);

	// create type
	Dynamic_ContainerType *type;

	type = new Dynamic_ContainerType();
	type->setName("constant");
	type->setOps(init_constant, config_constant, interact_constant);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("bmp");
	type->setOps(init_bmp, config_bmp, interact_bmp);
	type_list->push_back(type);
}


void RayTracer_Dynamic_Surface_info() {
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
	return DynamicUtil::configType(&table_config_constant, object, type, data, size);
}


static int config_bmp(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_bmp, object, type, data, size);
}


// interact
static int interact_constant(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_constant, object, type, list, size);
}


static int interact_bmp(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_bmp, object, type, list, size);
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


static int interact_bmp_convertToTexture(void *object, void* *list, uint32_t size) {
	Surface_BMP		*surface	= (Surface_BMP*)object;
	Texture_Image	*texture	= (Texture_Image*)(list[0]);

	if (!surface->convertToTexture(texture)) return -1;
	return 0;
}
