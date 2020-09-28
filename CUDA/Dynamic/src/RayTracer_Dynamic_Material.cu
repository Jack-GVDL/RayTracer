#include "../inc/RayTracer_DynamicSkeleton.cuh"
#include "../inc/RayTracer_Dynamic_Material.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// skeleton
Dynamic_CUDA_constructTypeSkeleton(default,	Material,	Material);


// Operation Handling
__host__ void RayTracer_Dynamic_Material_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	// ...

	// create type
	Dynamic_ContainerType *type;
	Dynamic_CUDA_addType(default,	default,	type_list);
}


__host__ void RayTracer_Dynamic_Material_info() {
}


__host__ void RayTracer_Dynamic_Material_del() {
}


// Static Function Implementation
// ...
