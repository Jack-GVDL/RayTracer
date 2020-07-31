#include "../inc/RayTracer_Material.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// TODO: missing uniqueness checking
bool Material::addScatter(Scatter *scatter) {
	scatter_list.push_back(scatter);
	return true;
}


// TODO: not yet completed
bool Material::rmScatter(Scatter *scatter) {
	return false;
}


// Static Function Implementation
// ...
