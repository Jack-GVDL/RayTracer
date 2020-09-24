#include "../inc/RayTracer_Dynamic_AABB.cuh"
#include "../inc/RayTracer_DynamicSkeleton.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// skeleton
Dynamic_constructTypeSkeleton(default, Hitable_AABB, Hitable_AABB);


// Static Data
// ...


// Operation Handling
__host__ void RayTracer_Dynamic_AABB_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	// ...

	// create type
	Dynamic_ContainerType *type;
	Dynamic_addType(default, default, type_list);
}


__host__ void RayTracer_Dynamic_AABB_info() {
}


__host__ void RayTracer_Dynamic_AABB_del() {
}




// Static Function Implementation
// ...
