#include "../inc/RayTracer_DynamicSkeleton.cuh"
#include "../inc/RayTracer_Dynamic_Light.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// table
__global__ static void			config_directional_setOrientation	(int8_t *ret, void *object, uint8_t *data, uint32_t size);
__global__ static void			config_point_setAttenuation			(int8_t *ret, void *object, uint8_t *data, uint32_t size);

// skeleton
Dynamic_CUDA_constructTypeSkeleton(directional,	SceneObject_Light,	Light_Directional);
Dynamic_CUDA_constructTypeSkeleton(point,		SceneObject_Light,	Light_Point);

Dynamic_CUDA_constructTypeConfigLinker(directional_setOrientation,	config_directional_setOrientation);
Dynamic_CUDA_constructTypeConfigLinker(point_setAttenuation,		config_point_setAttenuation);


// Static Data
// ...


// Operation Handling
__host__ void RayTracer_Dynamic_Light_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	Dynamic_CUDA_addTypeConfigLinker(directional,	directional_setOrientation);
	Dynamic_CUDA_addTypeConfigLinker(point,			point_setAttenuation);

	// table_config_directional.push_back(	config_directional_setOrientation	);
	// table_config_point.push_back(		config_point_setAttenuation			);

	// create type
	Dynamic_ContainerType *type;

	Dynamic_CUDA_addType(directional,	directional,	type_list);
	Dynamic_CUDA_addType(point,			point,			type_list);
}


__host__ void RayTracer_Dynamic_Light_info() {
}


__host__ void RayTracer_Dynamic_Light_del() {
}


// Static Function Implementation
// ...


// table
__global__ static void config_directional_setOrientation(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Light_Directional	*light			= (Light_Directional*)object;
	double				*orientation	= (double*)data;
	
	light->setOrientation(Vec3f(orientation[0], orientation[1], orientation[2]));
	*ret = 0;
}


__global__ static void config_point_setAttenuation(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Light_Point			*light	= (Light_Point*)object;
	double				*coeff	= (double*)data;

	light->setAttenuation(Vec3f(coeff[0], coeff[1], coeff[2]));
	*ret = 0;
}
