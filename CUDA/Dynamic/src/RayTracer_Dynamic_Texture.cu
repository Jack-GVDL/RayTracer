#include "../inc/RayTracer_DynamicSkeleton.cuh"
#include "../inc/RayTracer_Dynamic_Texture.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// table
// __global__ static void			config_convolutor_setKernelSize		(int8_t *ret, void *object, uint8_t *data, uint32_t size);
// __global__ static void			config_convolutor_setKernelArray	(int8_t *ret, void *object, uint8_t *data, uint32_t size);
// __global__ static void			config_checkerboard_setBoardSize	(int8_t *ret, void *object, uint8_t *data, uint32_t size);
// __global__ static void			config_additor_setAdditor			(int8_t *ret, void *object, uint8_t *data, uint32_t size);
// __global__ static void			config_multiplier_setMultiplier		(int8_t *ret, void *object, uint8_t *data, uint32_t size);

// __global__ static void			interact_convolutor_setTexture		(int8_t *ret, void *object, void* *list, uint32_t size);
// __global__ static void			interact_mapSphere_setSphere		(int8_t *ret, void *object, void* *list, uint32_t size);
// __global__ static void			interact_dirSphere_setSphere		(int8_t *ret, void *object, void* *list, uint32_t size);
// __global__ static void			interact_mapTrimesh_setTrimesh		(int8_t *ret, void *object, void* *list, uint32_t size);
// __global__ static void			interact_dirTrimesh_setTrimesh		(int8_t *ret, void *object, void* *list, uint32_t size);

// skeleton
Dynamic_CUDA_constructTypeSkeleton(input,			Texture,	Texture_Input);
Dynamic_CUDA_constructTypeSkeleton(constant,		Texture,	Texture_Constant);
// Dynamic_CUDA_constructTypeSkeleton(convolutor,		Texture,	Texture_Convolutor);
// Dynamic_CUDA_constructTypeSkeleton(checkerboard,	Texture,	Texture_CheckerBoard);
// Dynamic_CUDA_constructTypeSkeleton(image,			Texture,	Texture_Image);
// Dynamic_CUDA_constructTypeSkeleton(additor,			Texture,	Texture_Math_Additor);
// Dynamic_CUDA_constructTypeSkeleton(multiplier,		Texture,	Texture_Math_Multiplier);
// Dynamic_CUDA_constructTypeSkeleton(mapSphere,		Texture,	Texture_Mapper_Sphere);
// Dynamic_CUDA_constructTypeSkeleton(dirSphere,		Texture,	Texture_Direction_Sphere);
// Dynamic_CUDA_constructTypeSkeleton(mapTrimesh,		Texture,	Texture_Mapper_Trimesh);
// Dynamic_CUDA_constructTypeSkeleton(dirTrimesh,		Texture,	Texture_Direction_Trimesh);

// Dynamic_CUDA_constructTypeConfigLinker(convolutor_setKernelSize, 	config_convolutor_setKernelSize);
// Dynamic_CUDA_constructTypeConfigLinker(convolutor_setKernelArray, 	config_convolutor_setKernelArray);
// Dynamic_CUDA_constructTypeConfigLinker(checkerboard_setBoardSize, 	config_checkerboard_setBoardSize);
// Dynamic_CUDA_constructTypeConfigLinker(additor_setAdditor, 			config_additor_setAdditor);
// Dynamic_CUDA_constructTypeConfigLinker(multiplier_setMultiplier, 	config_multiplier_setMultiplier);

// Dynamic_CUDA_constructTypeInteractLinker(convolutor_setTexture, interact_convolutor_setTexture);
// Dynamic_CUDA_constructTypeInteractLinker(mapSphere_setSphere, 	interact_mapSphere_setSphere);
// Dynamic_CUDA_constructTypeInteractLinker(dirSphere_setSphere, 	interact_dirSphere_setSphere);
// Dynamic_CUDA_constructTypeInteractLinker(mapTrimesh_setTrimesh, interact_mapTrimesh_setTrimesh);
// Dynamic_CUDA_constructTypeInteractLinker(dirTrimesh_setTrimesh, interact_dirTrimesh_setTrimesh);


// Static Data
// ...


// Operation Handling
__host__ void RayTracer_Dynamic_Texture_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	// Dynamic_CUDA_constructTypeConfigLinker(convolutor, 		convolutor_setKernelSize);
	// Dynamic_CUDA_constructTypeConfigLinker(convolutor, 		convolutor_setKernelArray);
	// Dynamic_CUDA_constructTypeConfigLinker(checkerboard, 	checkerboard_setBoardSize);
	// Dynamic_CUDA_constructTypeConfigLinker(additor, 		additor_setAdditor);
	// Dynamic_CUDA_constructTypeConfigLinker(multiplier, 		multiplier_setMultiplier);

	// Dynamic_CUDA_constructTypeInteractLinker(convolutor,	convolutor_setTexture);
	// Dynamic_CUDA_constructTypeInteractLinker(mapSphere, 	mapSphere_setSphere);
	// Dynamic_CUDA_constructTypeInteractLinker(dirSphere, 	dirSphere_setSphere);
	// Dynamic_CUDA_constructTypeInteractLinker(mapTrimesh, 	mapTrimesh_setTrimesh);
	// Dynamic_CUDA_constructTypeInteractLinker(dirTrimesh, 	dirTrimesh_setTrimesh);

	// create type
	Dynamic_ContainerType *type;

	Dynamic_CUDA_addType(input,			input,				type_list);
	Dynamic_CUDA_addType(constant,		constant,			type_list);
	// Dynamic_CUDA_addType(convolutor,	convolutor,			type_list);
	// Dynamic_CUDA_addType(checkerboard,	checkerboard,		type_list);
	// Dynamic_CUDA_addType(image,			image,				type_list);
	// Dynamic_CUDA_addType(additor,		math_additor,		type_list);
	// Dynamic_CUDA_addType(multiplier,	math_multiplier,	type_list);
	// Dynamic_CUDA_addType(mapSphere,		mapper_sphere,		type_list);
	// Dynamic_CUDA_addType(dirSphere,		dir_sphere,			type_list);
	// Dynamic_CUDA_addType(mapTrimesh,	mapper_trimesh,		type_list);
	// Dynamic_CUDA_addType(dirTrimesh,	dir_trimesh,		type_list);
}


__host__ void RayTracer_Dynamic_Texture_info() {
}


__host__ void RayTracer_Dynamic_Texture_del() {
}


// Static Function Implementation
// table
// config
/*
__global__ static void config_convolutor_setKernelSize(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Texture_Convolutor		*texture		= (Texture_Convolutor*)object;
	int						kernel_width	= *((int*)data);

	texture->setKernel(texture->kernel, kernel_width);
	*ret = 0;
}


__global__ static void config_convolutor_setKernelArray(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Texture_Convolutor		*texture	= (Texture_Convolutor*)object;
	
	// delete original kernel
	delete[] texture->kernel;

	// create new kernel
	int32_t		kernel_size		= texture->kernel_width * texture->kernel_width;
	double		*data_double	= (double*)data;
	fp_t		*kernel			= new fp_t[kernel_size];
	for (int i = 0; i < kernel_size; i++) kernel[i] = (fp_t)(data_double[i]);

	texture->setKernel(kernel, texture->kernel_width);
	*ret = 0;
}


__global__ static void config_checkerboard_setBoardSize(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Texture_CheckerBoard	*texture	= (Texture_CheckerBoard*)object;
	double					*vec		= (double*)data;

	texture->setBoardSize(Vec3f(vec[0], vec[1], vec[2]));
	*ret = 0;
}


__global__ static void config_additor_setAdditor(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Texture_Math_Additor	*texture	= (Texture_Math_Additor*)object;
	double					*vec		= (double*)data;

	texture->setAdditor(Vec3f(vec[0], vec[1], vec[2]));
	*ret = 0;
}


__global__ static void config_multiplier_setMultiplier(int8_t *ret, void *object, uint8_t *data, uint32_t size) {
	Texture_Math_Multiplier	*texture	= (Texture_Math_Multiplier*)object;
	double					*vec		= (double*)data;

	texture->setMultiplier(Vec3f(vec[0], vec[1], vec[2]));
	*ret = 0;
}


// interact
__global__ static void interact_convolutor_setTexture(int8_t *ret, void *object, void* *list, uint32_t size) {
	Texture_Convolutor		*texture	= (Texture_Convolutor*)object;
	Texture					*target		= (Texture*)(list[0]);

	texture->setTexture(target);
	*ret = 0;
}


__global__ static void interact_mapSphere_setSphere(int8_t *ret, void *object, void* *list, uint32_t size) {
	Texture_Mapper_Sphere	*texture	= (Texture_Mapper_Sphere*)object;
	Hitable_Sphere			*sphere		= (Hitable_Sphere*)(list[0]);

	texture->setSphere(sphere);
	*ret = 0;
}


__global__ static void interact_dirSphere_setSphere(int8_t *ret, void *object, void* *list, uint32_t size) {
	Texture_Direction_Sphere	*texture	= (Texture_Direction_Sphere*)object;
	Hitable_Sphere				*sphere		= (Hitable_Sphere*)(list[0]);

	texture->setSphere(sphere);
	*ret = 0;
}


__global__ static void interact_mapTrimesh_setTrimesh(int8_t *ret, void *object, void* *list, uint32_t size) {
	Texture_Mapper_Trimesh	*texture	= (Texture_Mapper_Trimesh*)object;
	Hitable_Trimesh			*trimesh	= (Hitable_Trimesh*)(list[0]);

	texture->setTrimesh(trimesh);
	*ret = 0;

}


__global__ static void interact_dirTrimesh_setTrimesh(int8_t *ret, void *object, void* *list, uint32_t size) {
	Texture_Direction_Trimesh	*texture	= (Texture_Direction_Trimesh*)object;
	Hitable_Trimesh			*trimesh	= (Hitable_Trimesh*)(list[0]);

	texture->setTrimesh(trimesh);
	*ret = 0;

}
*/
