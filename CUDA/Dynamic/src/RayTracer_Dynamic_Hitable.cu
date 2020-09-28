#include "../inc/RayTracer_DynamicSkeleton.cuh"
#include "../inc/RayTracer_Dynamic_Hitable.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// table
__global__ static void			config_sphere_setCenter				(int8_t *ret, void *object, uint8_t *data, uint32_t size);
__global__ static void			config_sphere_setRadius				(int8_t *ret, void *object, uint8_t *data, uint32_t size);
__global__ static void			config_trimesh_setPoint_0			(int8_t *ret, void *object, uint8_t *data, uint32_t size);
__global__ static void			config_trimesh_setPoint_1			(int8_t *ret, void *object, uint8_t *data, uint32_t size);
__global__ static void			config_trimesh_setPoint_2			(int8_t *ret, void *object, uint8_t *data, uint32_t size);

// __global__ static void			interact_aabb_addHitable			(int *ret, void *object, void* *list, uint32_t size);
// __global__ static void			interact_aabb_rmHitable				(int *ret, void *object, void* *list, uint32_t size);

// skeleton
Dynamic_CUDA_constructTypeSkeleton(sphere,	SceneObject_Hitable,	Hitable_Sphere);
Dynamic_CUDA_constructTypeSkeleton(trimesh,	SceneObject_Hitable,	Hitable_Trimesh);
// Dynamic_CUDA_constructTypeSkeleton(aabb,		SceneObject_Hitable,	Hitable_AABB);

Dynamic_CUDA_constructTypeConfigLinker(sphere_setCenter,		config_sphere_setCenter);
Dynamic_CUDA_constructTypeConfigLinker(sphere_setRadius,		config_sphere_setRadius);
Dynamic_CUDA_constructTypeConfigLinker(trimesh_setPoint_0,	config_trimesh_setPoint_0);
Dynamic_CUDA_constructTypeConfigLinker(trimesh_setPoint_1,	config_trimesh_setPoint_1);
Dynamic_CUDA_constructTypeConfigLinker(trimesh_setPoint_2,	config_trimesh_setPoint_2);

// Dynamic_CUDA_constructTypeInteractLinker(aabb_addHitable,	interact_aabb_addHitable);
// Dynamic_CUDA_constructTypeInteractLinker(aabb_rmHitable,		interact_aabb_rmHitable);


// Static Data
// ...


// Operation Handling
__host__ void RayTracer_Dynamic_Hitable_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	Dynamic_CUDA_addTypeConfigLinker(sphere,		sphere_setCenter);
	Dynamic_CUDA_addTypeConfigLinker(sphere,		sphere_setRadius);
	Dynamic_CUDA_addTypeConfigLinker(trimesh,	trimesh_setPoint_0);
	Dynamic_CUDA_addTypeConfigLinker(trimesh,	trimesh_setPoint_1);
	Dynamic_CUDA_addTypeConfigLinker(trimesh,	trimesh_setPoint_2);

	// Dynamic_CUDA_addTypeInteractLinker(aabb,		aabb_addHitable);
	// Dynamic_CUDA_addTypeInteractLinker(aabb,		aabb_rmHitable);

	// create type
	Dynamic_ContainerType *type;

	Dynamic_CUDA_addType(sphere,		sphere,		type_list);
	Dynamic_CUDA_addType(trimesh,	trimesh,	type_list);
	// Dynamic_CUDA_addType(aabb,		aabb,		type_list);
}


__host__ void RayTracer_Dynamic_Hitable_info() {
}


__host__ void RayTracer_Dynamic_Hitable_del() {
}


// Static Function Implementation
// ...


// table
__global__ static void config_sphere_setCenter(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Hitable_Sphere		*hitable	= (Hitable_Sphere*)object;
	double				*center		= (double*)data;

	hitable->setCenter(Vec3f(center[0], center[1], center[2]));
	*ret = 0;
}


__global__ static void config_sphere_setRadius(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Hitable_Sphere		*hitable	= (Hitable_Sphere*)object;
	double				radius		= *((double*)data);

	hitable->setRadius(radius);
	*ret = 0;
}


__global__ static void config_trimesh_setPoint_0(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Hitable_Trimesh		*hitable	= (Hitable_Trimesh*)object;
	double				*point		= (double*)data;
	Vec3f				vec_point	= Vec3f(point[0], point[1], point[2]);

	hitable->setPoint(vec_point, hitable->point[1], hitable->point[2]);
	*ret = 0;
}


__global__ static void config_trimesh_setPoint_1(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Hitable_Trimesh		*hitable = (Hitable_Trimesh*)object;
	double				*point		= (double*)data;
	Vec3f				vec_point	= Vec3f(point[0], point[1], point[2]);

	hitable->setPoint(hitable->point[0], vec_point, hitable->point[2]);
	*ret = 0;
}


__global__ static void config_trimesh_setPoint_2(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Hitable_Trimesh		*hitable = (Hitable_Trimesh*)object;
	double				*point		= (double*)data;
	Vec3f				vec_point	= Vec3f(point[0], point[1], point[2]);

	hitable->setPoint(hitable->point[0], hitable->point[1], vec_point);
	*ret = 0;
}


// __global__ static void interact_aabb_addHitable(int8_t *ret, void *object, void* *list, uint32_t size) {
// 	Hitable_AABB		*hitable	= (Hitable_AABB*)object;
// 	SceneObject_Hitable	*child		= (SceneObject_Hitable*)(list[0]);

// 	if (!hitable->addHitable(child)) return -1;
// 	*ret = 0;
// }


// __global__ static void interact_aabb_rmHitable(int8_t *ret, void *object, void* *list, uint32_t size) {
// 	Hitable_AABB		*hitable	= (Hitable_AABB*)object;
// 	SceneObject_Hitable	*child		= (SceneObject_Hitable*)(list[0]);

// 	if (!hitable->rmHitable(child)) return -1;
// 	*ret = 0;
// }
