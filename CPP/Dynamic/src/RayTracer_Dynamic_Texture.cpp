#include "../inc/RayTracer_Dynamic_Texture.hpp"


// Define
// ...


// Typedef
typedef int(*config_func_table_t)(void *object, uint8_t *data, uint32_t size);


// Static Function Prototype
// init
static void*		init_constant						();
static void*		init_checkerboard					();
static void*		init_image							();

// config
static int			config_constant						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_checkerboard					(void *object, int type, uint8_t *data, uint32_t size);
static int			config_image						(void *object, int type, uint8_t *data, uint32_t size);

// inline
static inline int	config_table						(config_func_table_t *table, void *object, int type, uint8_t *data, uint32_t size);

// table
static int			config_checkerboard_setBoardSize	(void *object, uint8_t *data, uint32_t size);


// Static Data
static config_func_table_t	config_table_constant		[]	= {0};
static config_func_table_t	config_table_checkerboard	[]	= {config_checkerboard_setBoardSize,
															   0};
static config_func_table_t	config_table_image			[]	= {0};


// Operation Handling
void RayTracer_Dynamic_Texture_init(std::vector<init_func_t>* init_list, std::vector<config_func_t>* config_list) {
	init_list->push_back(init_constant);
	init_list->push_back(init_checkerboard);
	init_list->push_back(init_image);

	config_list->push_back(config_constant);
	config_list->push_back(config_checkerboard);
	config_list->push_back(config_image);
}


void RayTracer_Dynamic_Texture_del() {

}


// Static Function Implementation
// init
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
static int config_constant(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_constant, object, type, data, size);
}


static int config_checkerboard(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_checkerboard, object, type, data, size);
}


static int config_image(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_image, object, type, data, size);
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
static int config_checkerboard_setBoardSize(void *object, uint8_t *data, uint32_t size) {
	Texture_CheckerBoard	*texture	= (Texture_CheckerBoard*)object;
	double					*vec		= (double*)data;
	texture->setBoardSize(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}
