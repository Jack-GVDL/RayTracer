#include "../inc/RayTracer_Dynamic_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ops
static void*		init_chain							();
static void*		init_meanSampler					();
static void*		init_constant						();
static void*		init_checkerboard					();
static void*		init_image							();

static int			config_chain						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_meanSampler					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_constant						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_checkerboard					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_image						(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_chain						(void *object, int type, void* *list, uint32_t size);
static int			interact_meanSampler				(void *object, int type, void* *list, uint32_t size);
static int			interact_constant					(void *object, int type, void* *list, uint32_t size);
static int			interact_checkerboard				(void *object, int type, void* *list, uint32_t size);
static int			interact_image						(void *object, int type, void* *list, uint32_t size);

// table
static int			config_checkerboard_setBoardSize	(void *object, uint8_t *data, uint32_t size);

static int			interact_chain_addTexture			(void *object, void* *list, uint32_t size);
static int			interact_chain_rmTexture			(void *object, void* *list, uint32_t size);
static int			interact_meanSampler_setTexture		(void *object, void* *list, uint32_t size);


// Static Data
// Static Data
static std::vector<config_type_func_t>		table_config_chain;
static std::vector<config_type_func_t>		table_config_meanSampler;
static std::vector<config_type_func_t>		table_config_constant;
static std::vector<config_type_func_t>		table_config_checkerboard;
static std::vector<config_type_func_t>		table_config_image;

static std::vector<interact_type_func_t>	table_interact_chain;
static std::vector<interact_type_func_t>	table_interact_meanSampler;
static std::vector<interact_type_func_t>	table_interact_constant;
static std::vector<interact_type_func_t>	table_interact_checkerboard;
static std::vector<interact_type_func_t>	table_interact_image;


// Operation Handling
void RayTracer_Dynamic_Texture_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_checkerboard.push_back(config_checkerboard_setBoardSize);
	table_interact_chain.push_back(interact_chain_addTexture);
	table_interact_chain.push_back(interact_chain_rmTexture);
	table_interact_meanSampler.push_back(interact_meanSampler_setTexture);

	// chain
	Dynamic_ContainerType	*type_chain			= new Dynamic_ContainerType();
	type_chain->ops_init			= init_chain;
	type_chain->ops_config			= config_chain;
	type_chain->ops_interact		= interact_chain;
	type_list->push_back(type_chain);

	// mean sampler
	Dynamic_ContainerType	*type_meanSampler	= new Dynamic_ContainerType();
	type_meanSampler->ops_init		= init_meanSampler;
	type_meanSampler->ops_config	= config_meanSampler;
	type_meanSampler->ops_interact	= interact_meanSampler;
	type_list->push_back(type_meanSampler);

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
}


void RayTracer_Dynamic_Texture_del() {

}


// Static Function Implementation
// init
static void* init_chain() {
	Texture_Chain *texture = new Texture_Chain();
	return texture;
}


static void* init_meanSampler() {
	Texture_MeanSampler *texture = new Texture_MeanSampler();
	return texture;
}


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
static int config_chain(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_chain, object, type, data, size);
}


static int config_meanSampler(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_meanSampler, object, type, data, size);
}


static int config_constant(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_constant, object, type, data, size);
}


static int config_checkerboard(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_checkerboard, object, type, data, size);
}


static int config_image(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_image, object, type, data, size);
}


// interact
static int interact_chain(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_chain, object, type, list, size);
}


static int interact_meanSampler(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_meanSampler, object, type, list, size);
}


static int interact_constant(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_constant, object, type, list, size);
}


static int interact_checkerboard(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_checkerboard, object, type, list, size);
}


static int interact_image(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_image, object, type, list, size);
}


// table
static int config_checkerboard_setBoardSize(void *object, uint8_t *data, uint32_t size) {
	Texture_CheckerBoard	*texture	= (Texture_CheckerBoard*)object;
	double					*vec		= (double*)data;
	texture->setBoardSize(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}


static int interact_chain_addTexture(void *object, void* *list, uint32_t size) {
	Texture_Chain			*texture	= (Texture_Chain*)object;
	Texture					*target		= (Texture*)(list[0]);
	return texture->addTexture(target);
}


static int interact_chain_rmTexture(void *object, void* *list, uint32_t size) {
	Texture_Chain			*texture	= (Texture_Chain*)object;
	Texture					*target		= (Texture*)(list[0]);
	return texture->rmTexture(target);
}


static int interact_meanSampler_setTexture(void *object, void* *list, uint32_t size) {
	Texture_MeanSampler		*texture	= (Texture_MeanSampler*)object;
	Texture					*target		= (Texture*)(list[0]);
	texture->setTexture(target);
	return 0;
}

