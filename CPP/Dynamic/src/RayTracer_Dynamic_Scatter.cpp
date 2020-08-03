#include "../inc/RayTracer_Dynamic_Scatter.hpp"


// Define
// ...


// Typedef
typedef int(*config_func_table_t)(void *object, uint8_t *data, uint32_t size);


// Static Function Prototype
static void*		init_light							();
static void*		init_reflection						();
static void*		init_refraction						();
static void*		init_gradient						();
static void*		init_emitter						();

static int			config_light						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_reflection					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_refraction					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_gradient						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_emitter						(void *object, int type, uint8_t *data, uint32_t size);

static inline int	config_table						(config_func_table_t *table, void *object, int type, uint8_t *data, uint32_t size);


// Static Data
static config_func_table_t	config_table_light			[] = {0};
static config_func_table_t	config_table_reflection		[] = {0};
static config_func_table_t	config_table_refraction		[] = {0};
static config_func_table_t	config_table_gradient		[] = {0};
static config_func_table_t	config_table_emitter		[] = {0};


// Operation Handling
void RayTracer_Dynamic_Scatter_init(std::vector<init_func_t>* init_list, std::vector<config_func_t>* config_list) {
	init_list->push_back(init_light);
	init_list->push_back(init_reflection);
	init_list->push_back(init_refraction);
	init_list->push_back(init_gradient);
	init_list->push_back(init_emitter);

	config_list->push_back(config_light);
	config_list->push_back(config_reflection);
	config_list->push_back(config_refraction);
	config_list->push_back(config_gradient);
	config_list->push_back(config_emitter);
}


void RayTracer_Dynamic_Scatter_del() {

}


// Static Function Implementation
// init
static void* init_light() {
	Scatter_Light *scatter = new Scatter_Light();
	return scatter;
}


static void* init_reflection() {
	Scatter_Reflection *scatter = new Scatter_Reflection();
	return scatter;
}


static void* init_refraction() {
	Scatter_Refraction *scatter = new Scatter_Refraction();
	return scatter;
}


static void* init_gradient() {
	Scatter_Gradient *scatter = new Scatter_Gradient();
	return scatter;
}


static void* init_emitter() {
	Scatter_Emitter *scatter = new Scatter_Emitter();
	return scatter;
}


// config
static int config_light(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_light, object, type, data, size);
}


static int config_reflection(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_reflection, object, type, data, size);
}


static int config_refraction(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_refraction, object, type, data, size);
}


static int config_gradient(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_gradient, object, type, data, size);
}


static int config_emitter(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_emitter, object, type, data, size);
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
// ...
