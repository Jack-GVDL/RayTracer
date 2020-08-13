#include "../inc/RayTracer_Dynamic_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ops
static void*		init_convolutor						();
static void*		init_constant						();
static void*		init_checkerboard					();
static void*		init_image							();

static int			config_convolutor					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_constant						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_checkerboard					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_image						(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_convolutor					(void *object, int type, void* *list, uint32_t size);
static int			interact_constant					(void *object, int type, void* *list, uint32_t size);
static int			interact_checkerboard				(void *object, int type, void* *list, uint32_t size);
static int			interact_image						(void *object, int type, void* *list, uint32_t size);

// table
static int			config_convolutor_setKernelSize		(void *object, uint8_t *data, uint32_t size);
static int			config_convolutor_setKernelArray	(void *object, uint8_t *data, uint32_t size);
static int			config_checkerboard_setBoardSize	(void *object, uint8_t *data, uint32_t size);

static int			interact_convolutor_setTexture		(void *object, void* *list, uint32_t size);


// Static Data
// Static Data
static std::vector<config_type_func_t>		table_config_chain;
static std::vector<config_type_func_t>		table_config_convolutor;
static std::vector<config_type_func_t>		table_config_constant;
static std::vector<config_type_func_t>		table_config_checkerboard;
static std::vector<config_type_func_t>		table_config_image;

static std::vector<interact_type_func_t>	table_interact_chain;
static std::vector<interact_type_func_t>	table_interact_convolutor;
static std::vector<interact_type_func_t>	table_interact_constant;
static std::vector<interact_type_func_t>	table_interact_checkerboard;
static std::vector<interact_type_func_t>	table_interact_image;


// Operation Handling
void RayTracer_Dynamic_Texture_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_convolutor.push_back(config_convolutor_setKernelSize);
	table_config_convolutor.push_back(config_convolutor_setKernelArray);
	table_config_checkerboard.push_back(config_checkerboard_setBoardSize);
	table_interact_convolutor.push_back(interact_convolutor_setTexture);
	
	// convolutor
	Dynamic_ContainerType	*type_convolutor	= new Dynamic_ContainerType();
	type_convolutor->ops_init		= init_convolutor;
	type_convolutor->ops_config	= config_convolutor;
	type_convolutor->ops_interact	= interact_convolutor;
	type_list->push_back(type_convolutor);

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
static void* init_convolutor() {
	Texture_Convolutor *texture = new Texture_Convolutor();
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
static int config_convolutor(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_convolutor, object, type, data, size);
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
static int interact_convolutor(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_convolutor, object, type, list, size);
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
static int config_convolutor_setKernelSize(void *object, uint8_t *data, uint32_t size) {
	Texture_Convolutor		*texture		= (Texture_Convolutor*)object;
	int						kernel_width	= *((int*)data);
	texture->setKernel(texture->kernel, kernel_width);
	return 0;
}


static int config_convolutor_setKernelArray(void *object, uint8_t *data, uint32_t size) {
	Texture_Convolutor		*texture	= (Texture_Convolutor*)object;
	
	// delete original kernel
	delete[] texture->kernel;

	// create new kernel
	int		kernel_size	= texture->kernel_width * texture->kernel_width;
	double	*kernel		= new double[kernel_size];
	memcpy(kernel, data, sizeof(double) * kernel_size);

	texture->setKernel(kernel, texture->kernel_width);
	return 0;
}


static int config_checkerboard_setBoardSize(void *object, uint8_t *data, uint32_t size) {
	Texture_CheckerBoard	*texture	= (Texture_CheckerBoard*)object;
	double					*vec		= (double*)data;
	texture->setBoardSize(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}


static int interact_convolutor_setTexture(void *object, void* *list, uint32_t size) {
	Texture_Convolutor		*texture	= (Texture_Convolutor*)object;
	Texture					*target		= (Texture*)(list[0]);
	texture->setTexture(target);
	return 0;
}
