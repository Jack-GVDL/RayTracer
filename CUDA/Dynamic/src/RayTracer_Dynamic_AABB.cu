#include <algorithm>
#include "../inc/RayTracer_Dynamic_AABB.cuh"
#include "../inc/RayTracer_DynamicSkeleton.cuh"


// Define
// ...


// Typedef
// ...


// Data Structure
// ...


// Static Function Prototype
// skeleton
Dynamic_CUDA_constructTypeSkeleton(aabb_default, Hitable_AABB, Hitable_AABB);

// cuda linker function
// TODO: remove
/*
__global__ static void aabb_load	(SceneObject_AABB *aabb, SceneObject_Hitable *hitable_list, int32_t size);
*/

// TODO: need to be standardized (although these function are static)
__global__ static void	aabb_getBounding	(Bounding *bounding_list, SceneObject_Hitable *hitable_list, int32_t size);
__global__ static void	aabb_createAABB		(AABB* *dst, AABB *aabb_left, AABB *aabb_right, SceneObject_Hitable *hitable_left, SceneObject_Hitable *hitable_right);
__global__ static void	aabb_setRoot		(Hitable_AABB *aabb, AABB *root);


// Static Data
// ...


// Operation Handling
__host__ void RayTracer_Dynamic_AABB_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	// ...

	// create type
	Dynamic_ContainerType *type;
	Dynamic_CUDA_addType(aabb_default,	aabb_default,	type_list);
}


__host__ void RayTracer_Dynamic_AABB_info() {
}


__host__ void RayTracer_Dynamic_AABB_del() {
}


__host__ error_t Dynamic_AABB_load(Hitable_AABB *aabb, SceneObject_Hitable* *hitable_list, int32_t size) {
	// TODO: remove
	/*
	// data to device
	SceneObject_Hitable *hitable_list_device;
	cudaMalloc(&hitable_list_device, size * sizeof(SceneObject_Hitable*));
	cudaMemcpy(hitable_list_device, hitable_list, size * sizeof(SceneObject_Hitable*));

	// device function
	aabb_load <<< 1, 1 >>> (aabb, hitable_list_device, size);

	// free space
	cudaFree(hitable_device);
	
	return ERROR_NO;
	*/

	// TODO: not yet completed
	// get bounding

	// build tree

	return ERROR_NO;
}


// Static Function Implementation
// cuda linker function
// TODO: remove
/*
__global__ static void aabb_load(SceneObject_AABB *aabb, SceneObject_Hitable *hitable_list, int32_t size) {
	Hitable_AABB *aabb = Hitable_AABB::create(hitable_list, size, 1);
	if (aabb == nullptr) return;

	aabb->addHitable(aabb)
}
*/


__global__ static void	aabb_getBounding(Bounding *bounding_list, SceneObject_Hitable *hitable_list, int32_t size) {
	// just copying (copy constructor)
	for (int32_t i = 0; i < size; ++i) {
		bounding_list[i] = hitable_list[i].bounding;
	}
}


__global__ static void	aabb_createAABB(AABB* *dst, AABB *aabb_left, AABB *aabb_right, SceneObject_Hitable *hitable_left, SceneObject_Hitable *hitable_right) {
	*dst = new AABB(aabb_left, aabb_right, hitable_left, hitable_right);
}


__global__ static void	aabb_setRoot(Hitable_AABB *aabb, AABB *root) {
	aabb->setAABB(root);
}
