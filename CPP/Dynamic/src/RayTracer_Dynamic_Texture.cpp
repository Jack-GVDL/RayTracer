#include "../inc/RayTracer_DynamicSkeleton.hpp"
#include "../inc/RayTracer_Dynamic_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// skeleton
Dynamic_constructTypeSkeleton(input,		Texture,	Texture_Input);
Dynamic_constructTypeSkeleton(constant,		Texture,	Texture_Constant);
Dynamic_constructTypeSkeleton(convolutor,	Texture,	Texture_Convolutor);
Dynamic_constructTypeSkeleton(checkerboard,	Texture,	Texture_CheckerBoard);
Dynamic_constructTypeSkeleton(image,		Texture,	Texture_Image);
Dynamic_constructTypeSkeleton(additor,		Texture,	Texture_Math_Additor);
Dynamic_constructTypeSkeleton(multiplier,	Texture,	Texture_Math_Multiplier);
Dynamic_constructTypeSkeleton(mapSphere,	Texture,	Texture_Mapper_Sphere);
Dynamic_constructTypeSkeleton(dirSphere,	Texture,	Texture_Direction_Sphere);
Dynamic_constructTypeSkeleton(mapTrimesh,	Texture,	Texture_Mapper_Trimesh);
Dynamic_constructTypeSkeleton(dirTrimesh,	Texture,	Texture_Direction_Trimesh);

// table
static int			config_convolutor_setKernelSize		(void *object, uint8_t *data, uint32_t size);
static int			config_convolutor_setKernelArray	(void *object, uint8_t *data, uint32_t size);
static int			config_checkerboard_setBoardSize	(void *object, uint8_t *data, uint32_t size);
static int			config_additor_setAdditor			(void *object, uint8_t *data, uint32_t size);
static int			config_multiplier_setMultiplier		(void *object, uint8_t *data, uint32_t size);

static int			interact_convolutor_setTexture		(void *object, void* *list, uint32_t size);
static int			interact_mapSphere_setSphere		(void *object, void* *list, uint32_t size);
static int			interact_dirSphere_setSphere		(void *object, void* *list, uint32_t size);
static int			interact_mapTrimesh_setTrimesh		(void *object, void* *list, uint32_t size);
static int			interact_dirTrimesh_setTrimesh		(void *object, void* *list, uint32_t size);


// Static Data
// ...


// Operation Handling
void RayTracer_Dynamic_Texture_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_convolutor.push_back(		config_convolutor_setKernelSize		);
	table_config_convolutor.push_back(		config_convolutor_setKernelArray	);
	table_config_checkerboard.push_back(	config_checkerboard_setBoardSize	);
	table_config_additor.push_back(			config_additor_setAdditor			);
	table_config_multiplier.push_back(		config_multiplier_setMultiplier		);

	table_interact_convolutor.push_back(	interact_convolutor_setTexture		);
	table_interact_mapSphere.push_back(		interact_mapSphere_setSphere		);
	table_interact_dirSphere.push_back(		interact_dirSphere_setSphere		);
	table_interact_mapTrimesh.push_back(	interact_mapTrimesh_setTrimesh		);
	table_interact_dirTrimesh.push_back(	interact_mapTrimesh_setTrimesh		);

	// create type
	Dynamic_ContainerType *type;

	Dynamic_addType(input,			input,				type_list);
	Dynamic_addType(constant,		constant,			type_list);
	Dynamic_addType(convolutor,		convolutor,			type_list);
	Dynamic_addType(checkerboard,	checkerboard,		type_list);
	Dynamic_addType(image,			image,				type_list);
	Dynamic_addType(additor,		math_additor,		type_list);
	Dynamic_addType(multiplier,		math_multiplier,	type_list);
	Dynamic_addType(mapSphere,		mapper_sphere,		type_list);
	Dynamic_addType(dirSphere,		dir_sphere,			type_list);
	Dynamic_addType(mapTrimesh,		mapper_trimesh,		type_list);
	Dynamic_addType(dirTrimesh,		dir_trimesh,		type_list);
}


void RayTracer_Dynamic_Texture_info() {
}


void RayTracer_Dynamic_Texture_del() {
}


// Static Function Implementation
// table
// config
static int config_convolutor_setKernelSize(void *object, uint8_t *data, uint32_t size) {
	Texture_Convolutor		*texture		= (Texture_Convolutor*)object;
	int						kernel_width	= *((int*)data);
	texture->setKernel(texture->kernel, kernel_width);
	return 0;
}


static int config_convolutor_setKernelArray(void *object, uint8_t *data, uint32_t size) {
	Texture_Convolutor		*texture	= (Texture_Convolutor*)object;
	
	// delete original kernel
	delete[] texture->kernel;

	// create new kernel
	int32_t		kernel_size		= texture->kernel_width * texture->kernel_width;
	double		*data_double	= (double*)data;
	fp_t		*kernel			= new fp_t[kernel_size];
	for (int i = 0; i < kernel_size; i++) kernel[i] = (fp_t)(data_double[i]);

	texture->setKernel(kernel, texture->kernel_width);
	return 0;
}


static int config_checkerboard_setBoardSize(void *object, uint8_t *data, uint32_t size) {
	Texture_CheckerBoard	*texture	= (Texture_CheckerBoard*)object;
	double					*vec		= (double*)data;
	texture->setBoardSize(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}


static int config_additor_setAdditor(void *object, uint8_t *data, uint32_t size) {
	Texture_Math_Additor	*texture	= (Texture_Math_Additor*)object;
	double					*vec		= (double*)data;
	texture->setAdditor(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}


static int config_multiplier_setMultiplier(void *object, uint8_t *data, uint32_t size) {
	Texture_Math_Multiplier	*texture	= (Texture_Math_Multiplier*)object;
	double					*vec		= (double*)data;
	texture->setMultiplier(Vec3f(vec[0], vec[1], vec[2]));
	return 0;
}


// interact
static int interact_convolutor_setTexture(void *object, void* *list, uint32_t size) {
	Texture_Convolutor		*texture	= (Texture_Convolutor*)object;
	Texture					*target		= (Texture*)(list[0]);
	texture->setTexture(target);
	return 0;
}


static int interact_mapSphere_setSphere(void *object, void* *list, uint32_t size) {
	Texture_Mapper_Sphere	*texture	= (Texture_Mapper_Sphere*)object;
	Hitable_Sphere			*sphere		= (Hitable_Sphere*)(list[0]);
	texture->setSphere(sphere);
	return 0;
}


static int interact_dirSphere_setSphere(void *object, void* *list, uint32_t size) {
	Texture_Direction_Sphere	*texture	= (Texture_Direction_Sphere*)object;
	Hitable_Sphere				*sphere		= (Hitable_Sphere*)(list[0]);
	texture->setSphere(sphere);
	return 0;
}


static int interact_mapTrimesh_setTrimesh(void *object, void* *list, uint32_t size) {
	Texture_Mapper_Trimesh	*texture	= (Texture_Mapper_Trimesh*)object;
	Hitable_Trimesh			*trimesh	= (Hitable_Trimesh*)(list[0]);
	texture->setTrimesh(trimesh);
	return 0;

}


static int interact_dirTrimesh_setTrimesh(void *object, void* *list, uint32_t size) {
	Texture_Direction_Trimesh	*texture	= (Texture_Direction_Trimesh*)object;
	Hitable_Trimesh			*trimesh	= (Hitable_Trimesh*)(list[0]);
	texture->setTrimesh(trimesh);
	return 0;

}
