#include "../inc/RayTracer_Texture_Constant.cuh"
#include "../inc/RayTracer_Material.cuh"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
__device__ Material::Material() {
    transmissive    = nullptr;
    index           = RAY_INDEX_AIR;
}


__device__ Material::~Material() {
}


__device__ error_t Material::allocateScatter(int32_t size) {
    // free old
    cudaFree(scatter_list);

    // allocate new
    cudaMalloc(&scatter_list, size * sizeof(Scatter*));
    scatter_index   = 0;
    scatter_size    = size;

    return ERROR_NO;
}


// TODO: missing uniquness check
__device__ error_t Material::addScatter(Scatter *scatter) {
    if (scatter_index == scatter_size) return ERROR_ANY;

    scatter_list[scatter_index] = scatter;
    scatter_index++;
    return ERROR_NO;
}


// TODO: not yet completed
__device__ error_t Material::rmScatter(Scatter *scatter) {
    return ERROR_ANY;
}

// Static Function Implementation
// ...
