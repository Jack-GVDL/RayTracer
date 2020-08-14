#include "../inc/RayTracer_Texture.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// TODO: need uniqueness checking
bool Texture::addMapper(Mapper *mapper) {
	mapper_list.push_back(mapper);
	return true;
}


// TODO: not yet completed
bool Texture::rmMapper(Mapper *mapper) {
	return false;
}


void Texture::getPixel(Vec3f &dst, const Vec3f &src) const {
	Vec3f temp = src;
	for (auto *mapper : mapper_list) mapper->map(temp);

	_getPixel_(dst, temp);
}


// Static Function Implementation
// ...
