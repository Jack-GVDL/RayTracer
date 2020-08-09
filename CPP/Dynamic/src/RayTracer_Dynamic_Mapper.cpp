#include "../inc/RayTracer_Dynamic_Mapper.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// init
static void*		init_additor						();
static void*		init_multiplier						();

static int			config_additor						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_multiplier					(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_additor					(void *object, int type, void* *list, uint32_t size);
static int			interact_multiplier					(void *object, int type, void* *list, uint32_t size);

// table
static int			config_additor_setAdditor			(void *object, uint8_t *data, uint32_t size);
static int			config_multiplier_setMultiplier		(void *object, uint8_t *data, uint32_t size);


// Static Data
static config_type_func_t	config_table_additor		[]	= {
	config_additor_setAdditor
};

static config_type_func_t	config_table_multiplier		[]	= {
	config_multiplier_setMultiplier
};

static interact_type_func_t	interact_table_additor		[]	= {
	0
};

static interact_type_func_t	interact_table_multiplier	[]	= {
	0
};


// Operation Handling
void RayTracer_Dynamic_Mapper_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// additor
	Dynamic_ContainerType	*type_additor		= new Dynamic_ContainerType();
	type_additor->ops_init		= init_additor;
	type_additor->ops_config	= config_additor;
	type_additor->ops_interact	= interact_additor;
	type_list->push_back(type_additor);

	// multiplier
	Dynamic_ContainerType	*type_multiplier	= new Dynamic_ContainerType();
	type_multiplier->ops_init		= init_multiplier;
	type_multiplier->ops_config	= config_multiplier;
	type_multiplier->ops_interact	= interact_multiplier;
	type_list->push_back(type_multiplier);
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
	Mapper_Additor	*mapper	= new Mapper_Additor();
	return mapper;
}


static void* init_multiplier() {
	Mapper_Multiplier	*mapper = new Mapper_Multiplier();
	return mapper;
}


// config
static int config_additor(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_additor, object, type, data, size);
}


static int config_multiplier(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_multiplier, object, type, data, size);
}


// interact
static int interact_additor(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_additor, object, type, list, size);
}


static int interact_multiplier(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_multiplier, object, type, list, size);
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
