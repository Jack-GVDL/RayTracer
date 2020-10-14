#include <stdio.h>
#include "../inc/RayTracer_Dynamic_Scatter.hpp"
#include "../inc/RayTracer_DynamicSkeleton.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// skeleton
Dynamic_constructTypeSkeleton(light,		Scatter,	Scatter_Light);
Dynamic_constructTypeSkeleton(anyHit,		Scatter,	Scatter_AnyHit);
Dynamic_constructTypeSkeleton(reflection,	Scatter,	Scatter_Reflection);
Dynamic_constructTypeSkeleton(refraction,	Scatter,	Scatter_Refraction);
Dynamic_constructTypeSkeleton(gradient,		Scatter,	Scatter_Gradient);
Dynamic_constructTypeSkeleton(emitter,		Scatter,	Scatter_Emitter);
Dynamic_constructTypeSkeleton(random,		Scatter,	Scatter_Random);

// table
static int			config_random_setRadius				(void *object, uint8_t *data, uint32_t size);
static int			config_random_setParallel			(void *object, uint8_t *data, uint32_t size);
static int			config_random_setRaySize			(void *object, uint8_t *data, uint32_t size);


// Static Data
// ...


// Operation Handling
void RayTracer_Dynamic_Scatter_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_random.push_back(	config_random_setRadius		);
	table_config_random.push_back(	config_random_setParallel	);
	table_config_random.push_back(	config_random_setRaySize	);

	// create type
	Dynamic_ContainerType *type;

	Dynamic_addType(light,		light,		type_list);
	Dynamic_addType(reflection,	reflection,	type_list);
	Dynamic_addType(refraction,	refraction,	type_list);
	Dynamic_addType(gradient,	gradient,	type_list);
	Dynamic_addType(emitter,	emitter,	type_list);
	Dynamic_addType(random,		random,		type_list);
	Dynamic_addType(anyHit,		any_hit,	type_list);
}


void RayTracer_Dynamic_Scatter_info() {
}


void RayTracer_Dynamic_Scatter_del() {
}


// Static Function Implementation
// table
static int config_random_setRadius(void *object, uint8_t *data, uint32_t size) {
	Scatter_Random	*scatter	= (Scatter_Random*)object;
	double			radius		= ((double*)data)[0];
	scatter->setRadius((fp_t)radius);
	return 0;
}


static int config_random_setParallel(void *object, uint8_t *data, uint32_t size) {
	Scatter_Random	*scatter	= (Scatter_Random*)object;
	int				is_parallel	= ((int*)data)[0];
	scatter->setParallel(is_parallel ? 1 : 0);
	return 0;
}


static int config_random_setRaySize(void *object, uint8_t *data, uint32_t size) {
	Scatter_Random	*scatter	= (Scatter_Random*)object;
	int				count		= ((int*)data)[0];
	scatter->setRaySize((uint8_t)UtilMath::clamp<int>(0, count, 255));
	return 0;
}
