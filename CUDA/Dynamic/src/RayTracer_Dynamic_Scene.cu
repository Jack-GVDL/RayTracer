#include "../inc/RayTracer_Dynamic_Scene.cuh"


// Define
// ...


// Typedef
// ...


// Static Data
extern __device__ Scene			*scene;


// Static Function Prototype
__global__ static void		global_addLight		(SceneObject_Light *light);
__global__ static void		global_addHitable	(SceneObject_Hitable *hitable);
__global__ static void		global_rmLight		(SceneObject_Light *light);
__global__ static void		global_rmHitable	(SceneObject_Hitable *hitable);


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
