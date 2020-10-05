#include "../inc/RayTracer_DynamicSkeleton.cuh"
#include "../inc/RayTracer_Dynamic_Camera.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototpye
// skeleton
Dynamic_CUDA_constructTypeSkeleton(camera_default,	Camera,	Camera);

// table
// ...

// cuda linker function
// __global__ static void	camera_setAll			(Camera *camera);
__global__ static void	camera_setLookFrom		(Camera *camera, fp_t v_0, fp_t v_1, fp_t v_2);
__global__ static void	camera_setLookAt		(Camera *camera, fp_t v_0, fp_t v_1, fp_t v_2);
__global__ static void	camera_setUpDirection	(Camera *camera, fp_t v_0, fp_t v_1, fp_t v_2);
__global__ static void	camera_setFOV			(Camera *camera, fp_t value);
__global__ static void	camera_setAspectRatio	(Camera *camera, fp_t value);


// Static Data
// ...


// Operation Handling
__host__ void RayTracer_Dynamic_Camera_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	// ...

	// create type
	Dynamic_ContainerType *type;

	Dynamic_CUDA_addType(camera_default,	camera_default,	type_list);
}


__host__ void RayTracer_Dynamic_Camera_info() {
}


__host__ void RayTracer_Dynamic_Camera_del() {
}


// cuda linker function
// __host__ void Dynamic_Camera_setAll(Camera *camera) {
// }


__host__ error_t Dynamic_Camera_setLookFrom(Camera *camera, const Vec3f look_from) {
	camera_setLookFrom <<< 1, 1 >>> (camera, look_from[0], look_from[1], look_from[2]);
	return ERROR_NO;
}


__host__ error_t Dynamic_Camera_setLookAt(Camera *camera, const Vec3f look_at) {
	camera_setLookAt <<< 1, 1 >>> (camera, look_at[0], look_at[1], look_at[2]);
	return ERROR_NO;
}


__host__ error_t Dynamic_Camera_setUpDirection(Camera *camera, const Vec3f up) {
	camera_setUpDirection <<< 1, 1 >>> (camera, up[0], up[1], up[2]);
	return ERROR_NO;
}


__host__ error_t Dynamic_Camera_setFOV(Camera *camera, fp_t value) {
	camera_setFOV <<< 1, 1 >>> (camera, value);
	return ERROR_NO;
}


__host__ error_t Dynamic_Camera_setAspectRatio(Camera *camera, fp_t value) {
	camera_setAspectRatio <<< 1, 1 >>> (camera, value);
	return ERROR_NO;
}


// Static Function Implementation
// table
// ...

// cuda linker function
// __global__ static void camera_setAll(Camera *camera) {
// }


__global__ static void camera_setLookFrom(Camera *camera, fp_t v_0, fp_t v_1, fp_t v_2) {
	camera->setLookFrom(Vec3f(v_0, v_1, v_2));
}


__global__ static void camera_setLookAt(Camera *camera, fp_t v_0, fp_t v_1, fp_t v_2) {
	camera->setLookAt(Vec3f(v_0, v_1, v_2));
}


__global__ static void camera_setUpDirection(Camera *camera, fp_t v_0, fp_t v_1, fp_t v_2) {
	camera->setUpDirection(Vec3f(v_0, v_1, v_2));
}


__global__ static void camera_setFOV(Camera *camera, fp_t value) {
	camera->setFOV(value);
}


__global__ static void camera_setAspectRatio(Camera *camera, fp_t value) {
	camera->setAspectRatio(value);
}
