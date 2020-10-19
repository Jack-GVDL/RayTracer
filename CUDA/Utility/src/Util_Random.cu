
#include "../inc/Util_Random.cuh"


// Define
// ...


// Typedef
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
__device__	Random::Random() {
	curand_init(0, 0, 0, &state);
}


__device__	Random::~Random() {

}

__device__ fp_t Random::randUniform() {
	return curand_uniform(&state);
}


// Static Function Implementation
// ...
