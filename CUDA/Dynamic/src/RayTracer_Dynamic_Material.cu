#include "../inc/RayTracer_DynamicSkeleton.cuh"
#include "../inc/RayTracer_Dynamic_Material.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// skeleton
Dynamic_CUDA_constructTypeSkeleton(material_default,	Material,	Material);

// cuda linker function
__global__ static void	material_addScatter			(Material *material, Scatter *scatter);
__global__ static void	material_rmScatter			(Material *material, Scatter *scatter);
__global__ static void	material_setTransmissive	(Material *material, fp_t v_0, fp_t v_1, fp_t v_2);
__global__ static void	material_setIndex 			(Material *material, fp_t value);


// Operation Handling
__host__ void RayTracer_Dynamic_Material_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	// ...

	// create type
	Dynamic_ContainerType *type;
	
	Dynamic_CUDA_addType(material_default,	material_default,	type_list);
}


__host__ void RayTracer_Dynamic_Material_info() {
}


__host__ void RayTracer_Dynamic_Material_del() {
}


__host__ error_t Dynamic_Material_addScatter(Material *material, Scatter *scatter) {
	material_addScatter <<< 1, 1 >>> (material, scatter);
	return ERROR_NO;
}


__host__ error_t Dynamic_Material_rmScatter(Material *material, Scatter *scatter) {
	material_rmScatter <<< 1, 1 >>> (material, scatter);
	return ERROR_NO;
}


__host__ error_t Dynamic_Material_setTransmissive(Material *material, const Vec3f &transmissive) {
	material_setTransmissive <<< 1, 1 >>> (material, transmissive[0], transmissive[1], transmissive[2]);
	return ERROR_NO;
}


__host__ error_t Dynamic_Material_setIndex(Material *material, fp_t value) {
	material_setIndex <<< 1, 1 >>> (material, value);
	return ERROR_NO;
}


// Static Function Implementation
// cuda linker function
__global__ static void material_addScatter(Material *material, Scatter *scatter) {
	material->addScatter(scatter);
}


__global__ static void material_rmScatter(Material *material, Scatter *scatter) {
	material->rmScatter(scatter);
}


__global__ static void material_setTransmissive(Material *material, fp_t v_0, fp_t v_1, fp_t v_2) {
	material->transmissive->setPixel(
		Vec3f(), Vec3f(v_0, v_1, v_2));
}


__global__ static void material_setIndex(Material *material, fp_t value) {
	material->index = value;
}
