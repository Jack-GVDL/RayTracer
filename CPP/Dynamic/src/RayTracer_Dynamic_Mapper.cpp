#include <vector>
#include "../inc/RayTracer_Dynamic_Mapper.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// init
static void*		init_additor						();
static void*		init_multiplier						();
static void*		init_sphere							();
static void*		init_trimesh						();

static int			config_additor						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_multiplier					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_sphere						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_trimesh						(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_additor					(void *object, int type, void* *list, uint32_t size);
static int			interact_multiplier					(void *object, int type, void* *list, uint32_t size);
static int			interact_sphere						(void *object, int type, void* *list, uint32_t size);
static int			interact_trimesh					(void *object, int type, void* *list, uint32_t size);

// table
static int			config_additor_setAdditor			(void *object, uint8_t *data, uint32_t size);
static int			config_multiplier_setMultiplier		(void *object, uint8_t *data, uint32_t size);

static int			config_sphere_setSphere				(void *object, void* *list, uint32_t size);
static int			config_trimesh_setTrimesh			(void *object, void* *list, uint32_t size);


// Static Data
static std::vector<config_type_func_t>		table_config_additor;
static std::vector<config_type_func_t>		table_config_multiplier;
static std::vector<config_type_func_t>		table_config_sphere;
static std::vector<config_type_func_t>		table_config_trimesh;

static std::vector<interact_type_func_t>	table_interact_additor;
static std::vector<interact_type_func_t>	table_interact_multiplier;
static std::vector<interact_type_func_t>	table_interact_sphere;
static std::vector<interact_type_func_t>	table_interact_trimesh;


// Operation Handling
void RayTracer_Dynamic_Mapper_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_additor.push_back(		config_additor_setAdditor		);
	table_config_multiplier.push_back(	config_multiplier_setMultiplier	);

	table_interact_sphere.push_back(	config_sphere_setSphere			);
	table_interact_trimesh.push_back(	config_trimesh_setTrimesh		);

	// additor
	Dynamic_ContainerType	*type_additor		= new Dynamic_ContainerType();
	type_additor->ops_init			= init_additor;
	type_additor->ops_config		= config_additor;
	type_additor->ops_interact		= interact_additor;
	type_list->push_back(type_additor);

	// multiplier
	Dynamic_ContainerType	*type_multiplier	= new Dynamic_ContainerType();
	type_multiplier->ops_init		= init_multiplier;
	type_multiplier->ops_config		= config_multiplier;
	type_multiplier->ops_interact	= interact_multiplier;
	type_list->push_back(type_multiplier);

	// sphere
	Dynamic_ContainerType	*type_sphere		= new Dynamic_ContainerType();
	type_sphere->ops_init			= init_sphere;
	type_sphere->ops_config			= config_sphere;
	type_sphere->ops_interact		= interact_sphere;
	type_list->push_back(type_sphere); 

	// trimesh
	Dynamic_ContainerType	*type_trimesh		= new Dynamic_ContainerType();
	type_trimesh->ops_init			= init_trimesh;
	type_trimesh->ops_config		= config_trimesh;
	type_trimesh->ops_interact		= interact_trimesh;
	type_list->push_back(type_trimesh);
}


void RayTracer_Dynamic_Mapper_info() {
	printf("Mapper Type \n");
	printf("0.  %s \n", "Additor");
	printf("1.  %s \n", "Multiplier");
}


void RayTracer_Dynamic_Mapper_del() {

}


// Static Function Implementation
// init
static void* init_additor() {
	Mapper_Additor		*mapper	= new Mapper_Additor();
	return mapper;
}


static void* init_multiplier() {
	Mapper_Multiplier	*mapper = new Mapper_Multiplier();
	return mapper;
}


static void* init_sphere() {
	Mapper_Sphere		*mapper = new Mapper_Sphere();
	return mapper;
}


static void* init_trimesh() {
	Mapper_Trimesh		*mapper = new Mapper_Trimesh();
	return mapper;
}


// config
static int config_additor(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_additor, object, type, data, size);
}


static int config_multiplier(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_multiplier, object, type, data, size);
}


static int config_sphere(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_sphere, object, type, data, size);
}


static int config_trimesh(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_trimesh, object, type, data, size);
}


// interact
static int interact_additor(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_additor, object, type, list, size);
}


static int interact_multiplier(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_multiplier, object, type, list, size);
}


static int interact_sphere(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_sphere, object, type, list, size);
}


static int interact_trimesh(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_trimesh, object, type, list, size);
}


// table
static int config_additor_setAdditor(void *object, uint8_t *data, uint32_t size) {
	Mapper_Additor	*mapper = (Mapper_Additor*)object;
	double			*vec	= (double*)data;

	mapper->setAdditor(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}


static int config_multiplier_setMultiplier(void *object, uint8_t *data, uint32_t size) {
	Mapper_Multiplier	*mapper	= (Mapper_Multiplier*)object;
	double				*vec	= (double*)data;

	mapper->setMultiplier(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}


static int config_sphere_setSphere(void *object, void* *list, uint32_t size) {
	Mapper_Sphere		*mapper		= (Mapper_Sphere*)object;
	Hitable_Sphere		*hitable	= (Hitable_Sphere*)(list[0]);

	mapper->setSphere(hitable);
	return 0;
}


static int config_trimesh_setTrimesh(void *object, void* *list, uint32_t size) {
	Mapper_Trimesh		*mapper		= (Mapper_Trimesh*)object;
	Hitable_Trimesh		*hitable	= (Hitable_Trimesh*)(list[0]);

	mapper->setTrimesh(hitable);
	return 0;
}
