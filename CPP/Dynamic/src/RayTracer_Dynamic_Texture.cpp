#include "../inc/RayTracer_Dynamic_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ops
static void*		init_input							();
static void*		init_constant						();
static void*		init_convolutor						();
static void*		init_checkerboard					();
static void*		init_image							();
static void*		init_additor						();
static void*		init_multiplier						();
static void*		init_sphere							();
static void*		init_sphereDir						();
static void*		init_trimesh						();
static void*		init_trimeshDir						();

static int			config_input						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_constant						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_convolutor					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_checkerboard					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_image						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_additor						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_multiplier					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_sphere						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_sphereDir					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_trimesh						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_trimeshDir					(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_input						(void *object, int type, void* *list, uint32_t size);
static int			interact_constant					(void *object, int type, void* *list, uint32_t size);
static int			interact_convolutor					(void *object, int type, void* *list, uint32_t size);
static int			interact_checkerboard				(void *object, int type, void* *list, uint32_t size);
static int			interact_image						(void *object, int type, void* *list, uint32_t size);
static int			interact_additor					(void *object, int type, void* *list, uint32_t size);
static int			interact_multiplier					(void *object, int type, void* *list, uint32_t size);
static int			interact_sphere						(void *object, int type, void* *list, uint32_t size);
static int			interact_sphereDir					(void *object, int type, void* *list, uint32_t size);
static int			interact_trimesh					(void *object, int type, void* *list, uint32_t size);
static int			interact_trimeshDir					(void *object, int type, void* *list, uint32_t size);

// table
static int			config_convolutor_setKernelSize		(void *object, uint8_t *data, uint32_t size);
static int			config_convolutor_setKernelArray	(void *object, uint8_t *data, uint32_t size);
static int			config_checkerboard_setBoardSize	(void *object, uint8_t *data, uint32_t size);
static int			config_additor_setAdditor			(void *object, uint8_t *data, uint32_t size);
static int			config_multiplier_setMultiplier		(void *object, uint8_t *data, uint32_t size);

static int			interact_convolutor_setTexture		(void *object, void* *list, uint32_t size);
static int			interact_sphere_setSphere			(void *object, void* *list, uint32_t size);
static int			interact_sphereDir_setSphere		(void *object, void* *list, uint32_t size);
static int			interact_trimesh_setTrimesh			(void *object, void* *list, uint32_t size);
static int			interact_trimeshDir_setTrimesh		(void *object, void* *list, uint32_t size);


// Static Data
static std::vector<config_type_func_t>		table_config_input;
static std::vector<config_type_func_t>		table_config_constant;
static std::vector<config_type_func_t>		table_config_convolutor;
static std::vector<config_type_func_t>		table_config_checkerboard;
static std::vector<config_type_func_t>		table_config_image;
static std::vector<config_type_func_t>		table_config_additor;
static std::vector<config_type_func_t>		table_config_multiplier;
static std::vector<config_type_func_t>		table_config_sphere;
static std::vector<config_type_func_t>		table_config_sphereDir;
static std::vector<config_type_func_t>		table_config_trimesh;
static std::vector<config_type_func_t>		table_config_trimeshDir;

static std::vector<interact_type_func_t>	table_interact_input;
static std::vector<interact_type_func_t>	table_interact_constant;
static std::vector<interact_type_func_t>	table_interact_convolutor;
static std::vector<interact_type_func_t>	table_interact_checkerboard;
static std::vector<interact_type_func_t>	table_interact_image;
static std::vector<interact_type_func_t>	table_interact_additor;
static std::vector<interact_type_func_t>	table_interact_multiplier;
static std::vector<interact_type_func_t>	table_interact_sphere;
static std::vector<interact_type_func_t>	table_interact_sphereDir;
static std::vector<interact_type_func_t>	table_interact_trimesh;
static std::vector<interact_type_func_t>	table_interact_trimeshDir;


// Operation Handling
void RayTracer_Dynamic_Texture_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_convolutor.push_back(		config_convolutor_setKernelSize		);
	table_config_convolutor.push_back(		config_convolutor_setKernelArray	);
	table_config_checkerboard.push_back(	config_checkerboard_setBoardSize	);
	table_config_additor.push_back(			config_additor_setAdditor			);
	table_config_multiplier.push_back(		config_multiplier_setMultiplier		);

	table_interact_convolutor.push_back(	interact_convolutor_setTexture		);
	table_interact_sphere.push_back(		interact_sphere_setSphere			);
	table_interact_sphereDir.push_back(		interact_sphereDir_setSphere		);
	table_interact_trimesh.push_back(		interact_trimesh_setTrimesh			);
	table_interact_trimeshDir.push_back(	interact_trimeshDir_setTrimesh		);

	// create type
	Dynamic_ContainerType *type;

	type = new Dynamic_ContainerType();
	type->setName("input");
	type->setOps(init_input, config_input, interact_input);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("constant");
	type->setOps(init_constant, config_constant, interact_constant);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("convolutor");
	type->setOps(init_convolutor, config_convolutor, interact_convolutor);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("checkerboard");
	type->setOps(init_checkerboard, config_checkerboard, interact_checkerboard);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("image");
	type->setOps(init_image, config_image, interact_image);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("math_additor");
	type->setOps(init_additor, config_additor, interact_additor);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("math_multiplier");
	type->setOps(init_multiplier, config_multiplier, interact_multiplier);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("mapper_sphere");
	type->setOps(init_sphere, config_sphere, interact_sphere);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("dir_sphere");
	type->setOps(init_sphereDir, config_sphereDir, interact_sphereDir);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("mapper_trimesh");
	type->setOps(init_trimesh, config_trimesh, interact_trimesh);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("dir_trimesh");
	type->setOps(init_trimeshDir, config_trimeshDir, interact_trimeshDir);
	type_list->push_back(type);
}


void RayTracer_Dynamic_Texture_info() {
}


void RayTracer_Dynamic_Texture_del() {
}


// Static Function Implementation
// init
static void* init_input() {
	Texture_Input *texture = new Texture_Input();
	return texture;
}


static void* init_constant() {
	Texture_Constant *texture = new Texture_Constant();
	return texture;
}


static void* init_convolutor() {
	Texture_Convolutor *texture = new Texture_Convolutor();
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


static void* init_additor() {
	Texture_Math_Additor *texture = new Texture_Math_Additor();
	return texture;
}


static void* init_multiplier() {
	Texture_Math_Multiplier *texture = new Texture_Math_Multiplier();
	return texture;
}


static void* init_sphere() {
	Texture_Mapper_Sphere *texture = new Texture_Mapper_Sphere();
	return texture;
}


static void* init_sphereDir() {
	Texture_Direction_Sphere *texture = new Texture_Direction_Sphere();
	return texture;
}


static void* init_trimesh() {
	Texture_Mapper_Trimesh *texture = new Texture_Mapper_Trimesh();
	return texture;
}


static void* init_trimeshDir() {
	Texture_Direction_Trimesh *texture = new Texture_Direction_Trimesh();
	return texture;
}


// config
static int config_input(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_input, object, type, data, size);
}


static int config_constant(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_constant, object, type, data, size);
}


static int config_convolutor(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_convolutor, object, type, data, size);
}


static int config_checkerboard(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_checkerboard, object, type, data, size);
}


static int config_image(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_image, object, type, data, size);
}


static int config_additor(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_additor, object, type, data, size);
}


static int config_multiplier(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_multiplier, object, type, data, size);
}


static int config_sphere(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_sphere, object, type, data, size);
}


static int config_sphereDir(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_sphereDir, object, type, data, size);
}


static int config_trimesh(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_trimesh, object, type, data, size);
}


static int config_trimeshDir(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_trimeshDir, object, type, data, size);
}


// interact
static int interact_input(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_input, object, type, list, size);
}


static int interact_constant(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_constant, object, type, list, size);
}


static int interact_convolutor(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_convolutor, object, type, list, size);
}


static int interact_checkerboard(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_checkerboard, object, type, list, size);
}


static int interact_image(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_image, object, type, list, size);
}


static int interact_additor(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_additor, object, type, list, size);
}


static int interact_multiplier(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_multiplier, object, type, list, size);
}


static int interact_sphere(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_sphere, object, type, list, size);
}


static int interact_sphereDir(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_sphereDir, object, type, list, size);
}


static int interact_trimesh(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_trimesh, object, type, list, size);
}


static int interact_trimeshDir(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_trimeshDir, object, type, list, size);
}


// table
// config
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
	int32_t		kernel_size		= texture->kernel_width * texture->kernel_width;
	double		*data_double	= (double*)data;
	fp_t		*kernel			= new fp_t[kernel_size];
	for (int i = 0; i < kernel_size; i++) kernel[i] = (fp_t)(data_double[i]);

	texture->setKernel(kernel, texture->kernel_width);
	return 0;
}


static int config_checkerboard_setBoardSize(void *object, uint8_t *data, uint32_t size) {
	Texture_CheckerBoard	*texture	= (Texture_CheckerBoard*)object;
	double					*vec		= (double*)data;
	texture->setBoardSize(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}


static int config_additor_setAdditor(void *object, uint8_t *data, uint32_t size) {
	Texture_Math_Additor	*texture	= (Texture_Math_Additor*)object;
	double					*vec		= (double*)data;
	texture->setAdditor(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}


static int config_multiplier_setMultiplier(void *object, uint8_t *data, uint32_t size) {
	Texture_Math_Multiplier	*texture	= (Texture_Math_Multiplier*)object;
	double					*vec		= (double*)data;
	texture->setMultiplier(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}


// interact
static int interact_convolutor_setTexture(void *object, void* *list, uint32_t size) {
	Texture_Convolutor		*texture	= (Texture_Convolutor*)object;
	Texture					*target		= (Texture*)(list[0]);
	texture->setTexture(target);
	return 0;
}


static int interact_sphere_setSphere(void *object, void* *list, uint32_t size) {
	Texture_Mapper_Sphere	*texture	= (Texture_Mapper_Sphere*)object;
	Hitable_Sphere			*sphere		= (Hitable_Sphere*)(list[0]);
	texture->setSphere(sphere);
	return 0;
}


static int interact_sphereDir_setSphere(void *object, void* *list, uint32_t size) {
	Texture_Direction_Sphere	*texture	= (Texture_Direction_Sphere*)object;
	Hitable_Sphere				*sphere		= (Hitable_Sphere*)(list[0]);
	texture->setSphere(sphere);
	return 0;
}


static int interact_trimesh_setTrimesh(void *object, void* *list, uint32_t size) {
	Texture_Mapper_Trimesh	*texture	= (Texture_Mapper_Trimesh*)object;
	Hitable_Trimesh			*trimesh	= (Hitable_Trimesh*)(list[0]);
	texture->setTrimesh(trimesh);
	return 0;

}


static int interact_trimeshDir_setTrimesh(void *object, void* *list, uint32_t size) {
	Texture_Direction_Trimesh	*texture	= (Texture_Direction_Trimesh*)object;
	Hitable_Trimesh			*trimesh	= (Hitable_Trimesh*)(list[0]);
	texture->setTrimesh(trimesh);
	return 0;

}
