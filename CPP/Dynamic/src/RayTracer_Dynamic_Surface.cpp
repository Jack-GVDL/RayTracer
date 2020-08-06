#include "../inc/RayTracer_Dynamic_Surface.hpp"


// Define
// ...


// Typedef
typedef int(*config_func_table_t)(void *object, uint8_t *data, uint32_t size);


// Static Function Prototype
// init
static void*		init_constant						();
static void*		init_bmp							();

// config
static int			config_constant						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_bmp							(void *object, int type, uint8_t *data, uint32_t size);

// inline
static inline int	config_table						(config_func_table_t *table, void *object, int type, uint8_t *data, uint32_t size);

// table
static int			config_bmp_setPath					(void *object, uint8_t *data, uint32_t size);


// Static Data
static config_func_table_t config_table_constant	[] = {
	0
};

static config_func_table_t config_table_bmp			[] = {
	config_bmp_setPath
};


// Operation Handling
void RayTracer_Dynamic_Surface_init(std::vector<init_func_t>* init_list, std::vector<config_func_t>* config_list) {
	init_list->push_back(init_constant);
	init_list->push_back(init_bmp);

	config_list->push_back(config_constant);
	config_list->push_back(config_bmp);
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
	return config_table(config_table_constant, object, type, data, size);
}


static int config_bmp(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_bmp, object, type, data, size);
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

