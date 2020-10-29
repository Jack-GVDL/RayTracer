#include "../inc/RayTracer_Dynamic_Base.cuh"
#include <stdio.h>


// Define
// ...


// Typedef
// ...


// Static Data
// ...


// Static Function Prototype
__global__ static void global_Base_init	(int32_t size_random);


// Operation Handling
__host__ void RayTracer_Dynamic_Base_init() {
	global_Base_init <<< 1, 1 >>> (100);
}


// Static Function Implementation
__global__ static void global_Base_init(int32_t size_random) {
	UtilMath::initUtilMath(size_random);
}
