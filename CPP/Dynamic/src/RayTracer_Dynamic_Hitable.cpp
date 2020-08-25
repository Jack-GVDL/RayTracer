#include "../inc/RayTracer_Dynamic_Hitable.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ops
static void*		init_sphere							();
static void*		init_trimesh						();
static void*		init_aabb							();

static int			config_sphere						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_trimesh						(void *object, int type, uint8_t *data, uint32_t size);
static int			config_aabb							(void *object, int type, uint8_t *data, uint32_t size);

static int			interact_sphere						(void *object, int type, void* *list, uint32_t size);
static int			interact_trimesh					(void *object, int type, void* *list, uint32_t size);
static int			interact_aabb						(void *object, int type, void* *list, uint32_t size);

// table
static int			config_sphere_setCenter				(void *object, uint8_t *data, uint32_t size);
static int			config_sphere_setRadius				(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_0			(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_1			(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_2			(void *object, uint8_t *data, uint32_t size);

static int			interact_aabb_addHitable			(void *object, void* *list, uint32_t size);
static int			interact_aabb_rmHitable				(void *object, void* *list, uint32_t size);


// Static Data
static std::vector<config_type_func_t>		table_config_sphere;
static std::vector<config_type_func_t>		table_config_trimesh;
static std::vector<config_type_func_t>		table_config_aabb;

static std::vector<interact_type_func_t>	table_interact_sphere;
static std::vector<interact_type_func_t>	table_interact_trimesh;
static std::vector<interact_type_func_t>	table_interact_aabb;


// Operation Handling
void RayTracer_Dynamic_Hitable_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_sphere.push_back(	config_sphere_setCenter		);
	table_config_sphere.push_back(	config_sphere_setRadius		);
	table_config_trimesh.push_back(	config_trimesh_setPoint_0	);
	table_config_trimesh.push_back(	config_trimesh_setPoint_1	);
	table_config_trimesh.push_back(	config_trimesh_setPoint_2	);

	table_interact_aabb.push_back(	interact_aabb_addHitable	);
	table_interact_aabb.push_back(	interact_aabb_rmHitable		);

	// create type
	Dynamic_ContainerType *type;
	
	type = new Dynamic_ContainerType();
	type->setName("sphere");
	type->setOps(init_sphere, config_sphere, interact_sphere);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("trimesh");
	type->setOps(init_trimesh, config_trimesh, interact_trimesh);
	type_list->push_back(type);
	
	type = new Dynamic_ContainerType();
	type->setName("aabb");
	type->setOps(init_aabb, config_aabb, interact_aabb);
	type_list->push_back(type);
}


void RayTracer_Dynamic_Hitable_info() {
}


void RayTracer_Dynamic_Hitable_del() {
}


// Static Function Implementation
// init
static void* init_sphere() {
	Hitable_Sphere *hitable = new Hitable_Sphere();
	return hitable;
}


static void* init_trimesh() {
	Hitable_Trimesh *hitable = new Hitable_Trimesh();
	return hitable;
}


static void* init_aabb() {
	Hitable_AABB *hitable = new Hitable_AABB();
	return hitable;
}


// config
static int config_sphere(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_sphere, object, type, data, size);
}


static int config_trimesh(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_trimesh, object, type, data, size);
}


static int config_aabb(void *object, int type, uint8_t *data, uint32_t size) {
	return DynamicUtil::configType(&table_config_aabb, object, type, data, size);
}


// interact
static int interact_sphere(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_sphere, object, type, list, size);
}


static int interact_trimesh(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_trimesh, object, type, list, size);
}


static int interact_aabb(void *object, int type, void* *list, uint32_t size) {
	return DynamicUtil::interactType(&table_interact_aabb, object, type, list, size);
}


// table
static int config_sphere_setCenter(void *object, uint8_t *data, uint32_t size) {
	Hitable_Sphere	*hitable	= (Hitable_Sphere*)object;
	double				*center		= (double*)data;

	hitable->setCenter(Vec3f(center[0], center[1], center[2]));
	return 0;
}


static int config_sphere_setRadius(void *object, uint8_t *data, uint32_t size) {
	Hitable_Sphere	*hitable	= (Hitable_Sphere*)object;
	double				radius		= *((double*)data);

	hitable->setRadius(radius);
	return 0;
}


static int config_trimesh_setPoint_0(void *object, uint8_t *data, uint32_t size) {
	Hitable_Trimesh	*hitable	= (Hitable_Trimesh*)object;
	double				*point		= (double*)data;
	Vec3f				vec_point	= Vec3f(point[0], point[1], point[2]);

	hitable->setPoint(vec_point, hitable->point[1], hitable->point[2]);
	return 0;
}


static int config_trimesh_setPoint_1(void *object, uint8_t *data, uint32_t size) {
	Hitable_Trimesh *hitable = (Hitable_Trimesh*)object;
	double				*point		= (double*)data;
	Vec3f				vec_point	= Vec3f(point[0], point[1], point[2]);

	hitable->setPoint(hitable->point[0], vec_point, hitable->point[2]);
	return 0;
}


static int config_trimesh_setPoint_2(void *object, uint8_t *data, uint32_t size) {
	Hitable_Trimesh *hitable = (Hitable_Trimesh*)object;
	double				*point		= (double*)data;
	Vec3f				vec_point	= Vec3f(point[0], point[1], point[2]);

	hitable->setPoint(hitable->point[0], hitable->point[1], vec_point);
	return 0;
}


static int interact_aabb_addHitable(void *object, void* *list, uint32_t size) {
	Hitable_AABB		*hitable	= (Hitable_AABB*)object;
	SceneObject_Hitable	*child		= (SceneObject_Hitable*)(list[0]);

	if (!hitable->addHitable(child)) return -1;
	return 0;
}


static int interact_aabb_rmHitable(void *object, void* *list, uint32_t size) {
	Hitable_AABB		*hitable	= (Hitable_AABB*)object;
	SceneObject_Hitable	*child		= (SceneObject_Hitable*)(list[0]);

	if (!hitable->rmHitable(child)) return -1;
	return 0;
}
