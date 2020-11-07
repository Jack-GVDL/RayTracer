#include "../inc/RayTracer_Dynamic_Sampler.cuh"
#include "../inc/RayTracer_DynamicSkeleton.cuh"


// Define
// ...


// Typedef
// ...


// Data Structure
// ...


// Static Function Prototype
// skeleton
Dynamic_CPP_constructTypeSkeleton(grid,	Sampler,	Sampler_Grid);

// linker function
__host__ static int		config_grid_setSizeGrid		(void *object, uint8_t *data, uint32_t size);


// Static Data
// ...


// Operation Handling
__host__ void RayTracer_Dynamic_Sampler_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	Dynamic_CPP_addTypeConfig(grid, config_grid_setSizeGrid);

	// create type
	Dynamic_ContainerType *type;
	Dynamic_CPP_addType(grid,	grid,	type_list);
}


__host__ void RayTracer_Dynamic_Sampler_info() {
}


__host__ void RayTracer_Dynamic_Sampler_del() {
}


__host__ error_t Dynamic_Sampler_setSizeImage(Sampler *sampler, int32_t w, int32_t h) {
	sampler->setSizeImage(w, h);
	return ERROR_NO;
}


// Static Function Implementation
__host__ static int config_grid_setSizeGrid(void *object, uint8_t *data, uint32_t size) {
	Sampler_Grid	*sampler	= (Sampler_Grid*)object;
	int32_t			*dimension	= (int32_t*)data;

	sampler->setSizeGrid(dimension[0], dimension[1]);
	return ERROR_NO;
}
