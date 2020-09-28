#include "../inc/RayTracer_DynamicSkeleton.cuh"
#include "../inc/RayTracer_Dynamic_Camera.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototpye
// skeleton
Dynamic_CUDA_constructTypeSkeleton(camera_default,	Camera,	Camera);

// table
// ...

// Static Data
// ...


// Operation Handling
__host__ void RayTracer_CUDA_Dynamic_Camera_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	// ...

	// create type
	Dynamic_ContainerType *type;

	Dynamic_CUDA_addType(camera_default,	camera_default,	type_list);
}


__host__ void RayTracer_CUDA_Dynamic_Camera_info() {
}


__host__ void RayTracer_CUDA_Dynamic_Camera_del() {
}


// Static Function Implementation
// table
// ...
