#include "../inc/RayTracer_DynamicSkeleton.hpp"
#include "../inc/RayTracer_Dynamic_Light.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// skeleton
Dynamic_constructTypeSkeleton(directional,	SceneObject_Light,	Light_Directional);
Dynamic_constructTypeSkeleton(point,		SceneObject_Light,	Light_Point);

// table
static int			config_directional_setOrientation	(void *object, uint8_t *data, uint32_t size);
static int			config_point_setAttenuation			(void *object, uint8_t *data, uint32_t size);


// Static Data
// ...


// Operation Handling
void RayTracer_Dynamic_Light_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_directional.push_back(	config_directional_setOrientation	);
	table_config_point.push_back(		config_point_setAttenuation			);

	// create type
	Dynamic_ContainerType *type;

	Dynamic_addType(directional,	directional,	type_list);
	Dynamic_addType(point,			point,			type_list);
}


void RayTracer_Dynamic_Light_info() {
}


void RayTracer_Dynamic_Light_del() {
}


// Static Function Implementation
// ...


// table
static int config_directional_setOrientation(void *object, uint8_t *data, uint32_t size) {
	Light_Directional	*light			= (Light_Directional*)object;
	double				*orientation	= (double*)data;
	
	light->setOrientation(Vec3f(orientation[0], orientation[1], orientation[2]));
	return 0;
}


static int config_point_setAttenuation(void *object, uint8_t *data, uint32_t size) {
	Light_Point			*light	= (Light_Point*)object;
	double				*coeff	= (double*)data;

	light->setAttenuation(Vec3f(coeff[0], coeff[1], coeff[2]));
	return 0;
}
