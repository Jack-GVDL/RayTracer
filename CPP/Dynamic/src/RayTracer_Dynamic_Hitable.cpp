#include "../inc/RayTracer_Dynamic_Hitable.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ops
static void*		init_sphere							();
static void*		init_trimesh						();

static int			config_sphere						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_trimesh						(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_sphere						(void *object, int type, void* *list, uint32_t size);
static int			interact_trimesh					(void *object, int type, void* *list, uint32_t size);

// table
static int			config_sphere_setCenter				(void *object, uint8_t *data, uint32_t size);
static int			config_sphere_setRadius				(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_0			(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_1			(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_2			(void *object, uint8_t *data, uint32_t size);


// Static Data
// config
static config_type_func_t	config_table_sphere			[]	= {
	config_sphere_setCenter,
	config_sphere_setRadius
};

static config_type_func_t	config_table_trimesh		[]	= {
	config_trimesh_setPoint_0,
	config_trimesh_setPoint_1,
	config_trimesh_setPoint_2
};

// interact
static interact_type_func_t	interact_table_sphere		[]	= {
	0
};

static interact_type_func_t	interact_table_trimesh		[]	= {
	0
};


// Operation Handling
void RayTracer_Dynamic_Hitable_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// sphere
	Dynamic_ContainerType	*type_sphere	= new Dynamic_ContainerType();
	type_sphere->ops_init		= init_sphere;
	type_sphere->ops_config		= config_sphere;
	type_sphere->ops_interact	= interact_sphere;
	type_list->push_back(type_sphere);

	// trimesh
	Dynamic_ContainerType	*type_trimesh	= new Dynamic_ContainerType();
	type_trimesh->ops_init		= init_trimesh;
	type_trimesh->ops_config	= config_trimesh;
	type_trimesh->ops_interact	= interact_trimesh;
	type_list->push_back(type_trimesh);
}


void RayTracer_Dynamic_Hitable_info() {
	printf("Hitable Type: \n");
	printf("0.  %s \n", "Sphere");
	printf("1.  %s \n", "Trimesh");
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
	return DynamicUtil::configType(config_table_sphere, object, type, data, size);
}


static int config_trimesh(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(config_table_trimesh, object, type, data, size);
}


// interact
static int interact_sphere(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_sphere, object, type, list, size);
}


static int interact_trimesh(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(interact_table_trimesh, object, type, list, size);
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
