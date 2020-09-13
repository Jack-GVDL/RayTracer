#include "../inc/RayTracer_Material.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
Material::Material() {
    transmissive    = new Texture_Constant();
    index           = RAY_INDEX_AIR;
}


Material::~Material() {
}


// TODO: missing uniquness check
error_t Material::addScatter(Scatter *scatter) {
    scatter_list.push_back(scatter);
    return ERROR_NO;
}


// TODO: not yet completed
error_t Material::rmScatter(Scatter *scatter) {
    return ERROR_ANY;
}

// Static Function Implementation
// ...
