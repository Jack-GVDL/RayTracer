#include "../inc/RayTracer_Dynamic_Hitable.hpp"


// Define
// ...


// Typedef
typedef int(*config_func_table_t)(void *object, uint8_t *data, uint32_t size);


// Static Function Prototype
// init
static void*		init_sphere							();
static void*		init_trimesh						();

// config
static int			config_sphere						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_trimesh						(void *object, int type, uint8_t *data, uint32_t size);

// inline
static inline int	config_table						(config_func_table_t *table, void *object, int type, uint8_t *data, uint32_t size);

// table
static int			config_sphere_setCenter				(void *object, uint8_t *data, uint32_t size);
static int			config_sphere_setRadius				(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_0			(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_1			(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_2			(void *object, uint8_t *data, uint32_t size);


// Static Data
static config_func_table_t	config_table_sphere			[] = {
	config_sphere_setCenter,
	config_sphere_setRadius};

static config_func_table_t	config_table_trimesh		[] = {
	config_trimesh_setPoint_0,
	config_trimesh_setPoint_1,
	config_trimesh_setPoint_2
};


// Operation Handling
void RayTracer_Dynamic_Hitable_init(std::vector<init_func_t>* init_list, std::vector<config_func_t>* config_list) {
	init_list->push_back(init_sphere);
	init_list->push_back(init_trimesh);

	config_list->push_back(config_sphere);
	config_list->push_back(config_trimesh);
}


void RayTracer_Dynamic_Hitable_del() {

}


// Static Function Implementation
// init
static void* init_sphere() {
	SceneObject_Sphere *hitable = new SceneObject_Sphere();
	return hitable;
}


static void* init_trimesh() {
	SceneObject_Trimesh *hitable = new SceneObject_Trimesh();
	return hitable;
}


// config
static int config_sphere(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_sphere, object, type, data, size);
}


static int config_trimesh(void *object, int type, uint8_t *data, uint32_t size) {
	return config_table(config_table_trimesh, object, type, data, size);
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
static int config_sphere_setCenter(void *object, uint8_t *data, uint32_t size) {
	SceneObject_Sphere	*hitable	= (SceneObject_Sphere*)object;
	double				*center		= (double*)data;

	hitable->setCenter(Vec3f(center[0], center[1], center[2]));
	return 0;
}


static int config_sphere_setRadius(void *object, uint8_t *data, uint32_t size) {
	SceneObject_Sphere	*hitable	= (SceneObject_Sphere*)object;
	double				radius		= *((double*)data);

	hitable->setRadius(radius);
	return 0;
}


static int config_trimesh_setPoint_0(void *object, uint8_t *data, uint32_t size) {
	SceneObject_Trimesh	*hitable	= (SceneObject_Trimesh*)object;
	double				*point		= (double*)data;
	Vec3f				vec_point	= Vec3f(point[0], point[1], point[2]);

	hitable->setPoint(vec_point, hitable->point[1], hitable->point[2]);
	return 0;
}


static int config_trimesh_setPoint_1(void *object, uint8_t *data, uint32_t size) {
	SceneObject_Trimesh *hitable = (SceneObject_Trimesh*)object;
	double				*point		= (double*)data;
	Vec3f				vec_point	= Vec3f(point[0], point[1], point[2]);

	hitable->setPoint(hitable->point[0], vec_point, hitable->point[2]);
	return 0;
}


static int config_trimesh_setPoint_2(void *object, uint8_t *data, uint32_t size) {
	SceneObject_Trimesh *hitable = (SceneObject_Trimesh*)object;
	double				*point		= (double*)data;
	Vec3f				vec_point	= Vec3f(point[0], point[1], point[2]);

	hitable->setPoint(hitable->point[0], hitable->point[1], vec_point);
	return 0;
}
