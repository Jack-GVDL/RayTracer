#include "../inc/RayTracer_Dynamic_RIAS.cuh"
#include "../inc/RayTracer_DynamicSkeleton.cuh"


// Define
// ...


// Typedef
// ...


// Data Structure
// ...


// Static Function Prototype
// skeleton
Dynamic_CPP_constructTypeSkeleton(aabb,		RIAS,	RIAS_AABB);
// Dynamic_CPP_constructTypeSkeleton(octree,	RIAS,	RIAS_Octree);


// Static Data
// ...


// Operation Handling
__host__ void RayTracer_Dynamic_RIAS_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	// ...

	// create type
	Dynamic_ContainerType *type;
	Dynamic_CPP_addType(aabb,	aabb,	type_list);
}


__host__ void RayTracer_Dynamic_RIAS_info() {
}


__host__ void RayTracer_Dynamic_RIAS_del() {
}


__host__ error_t Dynamic_RIAS_load(RIAS *rias, SceneObject_Hitable* *hitable_list, int32_t size) {
	rias->load(hitable_list, size);
	return ERROR_NO;
}


// Static Function Implementation
// ...
