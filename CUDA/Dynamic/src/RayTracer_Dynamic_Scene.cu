#include "../inc/RayTracer_Dynamic_Scene.cuh"

// TODO: test
#include <stdio.h>


// Define
// ...


// Typedef
// ...


// Static Data
extern __device__ Scene			*scene;


// Static Function Prototype
__global__ static void		global_addLight			(SceneObject_Light *light);
__global__ static void		global_addHitable		(SceneObject_Hitable *hitable);
__global__ static void		global_rmLight			(SceneObject_Light *light);
__global__ static void		global_rmHitable		(SceneObject_Hitable *hitable);
__global__ static void		global_getLightIndex	(int32_t *dst);
__global__ static void		global_getHitableIndex	(int32_t *dst);
__global__ static void		global_getLightSize		(int32_t *dst);


// Operation Handling
__host__ error_t Dynamic_Scene_addLight(SceneObject_Light *light) {
	global_addLight <<< 1, 1 >>> (light);
	return ERROR_NO;
}


__host__ error_t Dynamic_Scene_addHitable(SceneObject_Hitable *hitable) {
	global_addHitable <<< 1, 1 >>> (hitable);
	return ERROR_NO;
}


__host__ error_t Dynamic_Scene_rmLight(SceneObject_Light * light) {
	global_rmLight <<< 1, 1 >>> (light);
	return ERROR_NO;
}


__host__ error_t Dynamic_Scene_rmHitable(SceneObject_Hitable *hitable) {
	global_rmHitable <<< 1, 1 >>> (hitable);
	return ERROR_NO;
}


__host__ int32_t Dynamic_Scene_getLightIndex() {
	int32_t *dst_device;
	int32_t	dst_host = -1;
	cudaMalloc(&dst_device, sizeof(int32_t));

	global_getLightIndex <<< 1, 1 >>> (dst_device);

	cudaMemcpy(&dst_host, dst_device, sizeof(int32_t), cudaMemcpyDeviceToHost);
	cudaFree(dst_device);

	return dst_host;
}


__host__ int32_t Dynamic_Scene_getHitableIndex() {
	int32_t *dst_device;
	int32_t	dst_host = -1;
	cudaMalloc(&dst_device, sizeof(int32_t));

	global_getHitableIndex <<< 1, 1 >>> (dst_device);

	cudaMemcpy(&dst_host, dst_device, sizeof(int32_t), cudaMemcpyDeviceToHost);
	cudaFree(dst_device);

	return dst_host;
}


__host__ int32_t Dynamic_Scene_getLightSize() {
	int32_t *dst_device;
	int32_t	dst_host = -1;
	cudaMalloc(&dst_device, sizeof(int32_t));

	global_getLightSize <<< 1, 1 >>> (dst_device);

	cudaMemcpy(&dst_host, dst_device, sizeof(int32_t), cudaMemcpyDeviceToHost);
	cudaFree(dst_device);

	return dst_host;
}


// Static Function Implementation
__global__ static void global_addLight(SceneObject_Light *light) {
	scene->addLight(light);
}


__global__ static void global_addHitable(SceneObject_Hitable *hitable) {
	scene->addHitable(hitable);
}


__global__ static void global_rmLight(SceneObject_Light *light) {
	scene->rmLight(light);
}


__global__ static void global_rmHitable(SceneObject_Hitable *hitable) {
	scene->rmHitable(hitable);
}


__global__ static void global_getLightIndex(int32_t *dst)  {
	*dst = scene->light_index;
	dst[0] = 11;
}


__global__ static void global_getHitableIndex(int32_t *dst)  {
	*dst = scene->hitable_index;
	*dst = 12;
}


__global__ static void global_getLightSize(int32_t *dst)  {
	// *dst = scene->light_size;
	*dst = 10;
}
