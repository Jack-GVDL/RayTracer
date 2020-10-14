#include "../inc/RayTracer_DynamicSkeleton.hpp"
#include "../inc/RayTracer_Dynamic_Camera.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototpye
// skeleton
Dynamic_constructTypeSkeleton(camera_default,	Camera,	Camera);

// table
// ...

// Static Data
// ...


// Operation Handling
void RayTracer_Dynamic_Camera_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	// ...

	// create type
	Dynamic_ContainerType *type;

	Dynamic_addType(camera_default,	camera_default,	type_list);
}


void RayTracer_Dynamic_Camera_info() {
}


void RayTracer_Dynamic_Camera_del() {
}


// Static Function Implementation
// table
// ...
