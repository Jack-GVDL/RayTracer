#include "../inc/RayTracer_Dynamic_Scatter.cuh"
#include "../inc/RayTracer_DynamicSkeleton.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// table
__global__ static void			config_random_setRadius				(int8_t *ret, void *object, uint8_t *data, uint32_t size);
__global__ static void			config_random_setParallel			(int8_t *ret, void *object, uint8_t *data, uint32_t size);
__global__ static void			config_random_setRaySize			(int8_t *ret, void *object, uint8_t *data, uint32_t size);

// skeleton
Dynamic_CUDA_constructTypeSkeleton(light,		Scatter,	Scatter_Light);
Dynamic_CUDA_constructTypeSkeleton(anyHit,		Scatter,	Scatter_AnyHit);
Dynamic_CUDA_constructTypeSkeleton(reflection,	Scatter,	Scatter_Reflection);
Dynamic_CUDA_constructTypeSkeleton(refraction,	Scatter,	Scatter_Refraction);
Dynamic_CUDA_constructTypeSkeleton(gradient,	Scatter,	Scatter_Gradient);
Dynamic_CUDA_constructTypeSkeleton(emitter,		Scatter,	Scatter_Emitter);
Dynamic_CUDA_constructTypeSkeleton(random,		Scatter,	Scatter_Random);

Dynamic_CUDA_constructTypeConfigLinker(random_setRadius,	config_random_setRadius);
Dynamic_CUDA_constructTypeConfigLinker(random_setParallel,	config_random_setParallel);
Dynamic_CUDA_constructTypeConfigLinker(random_setRaySize,	config_random_setRaySize);


// Static Data
// ...


// Operation Handling
__host__ void RayTracer_Dynamic_Scatter_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	Dynamic_CUDA_addTypeConfigLinker(random,		random_setRadius);
	Dynamic_CUDA_addTypeConfigLinker(random,		random_setParallel);
	Dynamic_CUDA_addTypeConfigLinker(random,		random_setRaySize);

	// create type
	Dynamic_ContainerType *type;

	Dynamic_CUDA_addType(light,		light,		type_list);
	Dynamic_CUDA_addType(reflection,	reflection,	type_list);
	Dynamic_CUDA_addType(refraction,	refraction,	type_list);
	Dynamic_CUDA_addType(gradient,	gradient,	type_list);
	Dynamic_CUDA_addType(emitter,	emitter,	type_list);
	Dynamic_CUDA_addType(random,		random,		type_list);
	Dynamic_CUDA_addType(anyHit,		any_hit,	type_list);
}


__host__ void RayTracer_Dynamic_Scatter_info() {
}


__host__ void RayTracer_Dynamic_Scatter_del() {
}


// Static Function Implementation
// table
__global__ static void config_random_setRadius(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Scatter_Random	*scatter	= (Scatter_Random*)object;
	double			radius		= ((double*)data)[0];

	scatter->setRadius((fp_t)radius);
	*ret = 0;
}


__global__ static void config_random_setParallel(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Scatter_Random	*scatter	= (Scatter_Random*)object;
	int				is_parallel	= ((int*)data)[0];

	scatter->setParallel(is_parallel ? 1 : 0);
	*ret = 0;
}


__global__ static void config_random_setRaySize(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Scatter_Random	*scatter	= (Scatter_Random*)object;
	int				count		= ((int*)data)[0];

	scatter->setRaySize((uint8_t)UtilMath::clamp<int>(0, count, 255));
	*ret = 0;
}
