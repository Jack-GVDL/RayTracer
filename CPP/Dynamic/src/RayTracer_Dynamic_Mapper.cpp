#include "../inc/RayTracer_Dynamic_Mapper.hpp"


// Define
// ...


// Typedef
typedef int(*config_func_table_t)(void *object, uint8_t *data, uint32_t size);


// Static Function Prototype
// init
static void*		init_additor						();
static void*		init_multiplier						();

// config
static int			config_additor						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_multiplier					(void *object, int type, uint8_t *data, uint32_t size);

// inline
static inline int	config_table						(config_func_table_t *table, void *object, int type, uint8_t *data, uint32_t size);

// table
static int			config_additor_setAdditor			(void *object, uint8_t *data, uint32_t size);
static int			config_multiplier_setMultiplier		(void *object, uint8_t *data, uint32_t size);


// Static Data
static config_func_table_t	config_table_additor	[] = {
	config_additor_setAdditor
};

static config_func_table_t	config_table_multiplier	[] = {
	config_multiplier_setMultiplier
};


// Operation Handling
void RayTracer_Dynamic_Mapper_init(std::vector<init_func_t>* init_list, std::vector<config_func_t> *config_list) {
	init_list->push_back(init_additor);
	init_list->push_back(init_multiplier);

	config_list->push_back(config_additor);
	config_list->push_back(config_multiplier);
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
	return config_table(config_table_additor, object, type, data, size);
}


static int config_multiplier(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_multiplier, object, type, data, size);
}


// inline
static inline int config_table(config_func_table_t *table, void *object, int type, uint8_t *data, uint32_t size) {
	// if (table == nullptr) return -1;  // trust operation
	// if (object == nullptr) return -1;  // trust operation

	// TODO: currently no size checking
	// it has to be done outside this function
	return table[type](object, data, size);
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
