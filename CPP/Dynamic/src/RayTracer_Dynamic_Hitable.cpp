#include "../inc/RayTracer_DynamicSkeleton.hpp"
#include "../inc/RayTracer_Dynamic_Hitable.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// skeleton
Dynamic_constructTypeSkeleton(sphere,	SceneObject_Hitable,	Hitable_Sphere);
Dynamic_constructTypeSkeleton(trimesh,	SceneObject_Hitable,	Hitable_Trimesh);
Dynamic_constructTypeSkeleton(aabb,		SceneObject_Hitable,	Hitable_AABB);

// table
static int			config_sphere_setCenter				(void *object, uint8_t *data, uint32_t size);
static int			config_sphere_setRadius				(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_0			(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_1			(void *object, uint8_t *data, uint32_t size);
static int			config_trimesh_setPoint_2			(void *object, uint8_t *data, uint32_t size);

static int			interact_aabb_addHitable			(void *object, void* *list, uint32_t size);
static int			interact_aabb_rmHitable				(void *object, void* *list, uint32_t size);


// Static Data
// ...


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

	Dynamic_addType(sphere,		sphere,		type_list);
	Dynamic_addType(trimesh,	trimesh,	type_list);
	Dynamic_addType(aabb,		aabb,		type_list);
}


void RayTracer_Dynamic_Hitable_info() {
}


void RayTracer_Dynamic_Hitable_del() {
}


// Static Function Implementation
// ...


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
