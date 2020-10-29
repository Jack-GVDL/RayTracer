#include "../inc/RayTracer_UtilMath.cuh"
#include "../inc/Util_Random.cuh"


// Define
// using namespace UtilMath;


// Typedef
// ...


// Static Data
__device__ Random	*random;
__device__ fp_t		*table_random;
__device__ int32_t	size_table;
__device__ int32_t	offset = 0;


// Static Function Prototype
// ...


// Operation Handling
namespace UtilMath {

__device__ void initUtilMath(int32_t size_random) {
	random = new Random();

	cudaMalloc(&table_random, size_random * sizeof(fp_t));
	size_table = size_random;

	for (int32_t i = 0; i < size_table; ++i) table_random[i] = randFloat();
}


__device__ fp_t randFloat() {
	return random->randUniform();
}

__device__ fp_t randFloat(int32_t index) {
	++offset;
	return table_random[(index + offset) % size_table];
}

}


// Static Function Implementation
// ...
