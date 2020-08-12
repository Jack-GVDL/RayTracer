#include "../inc/RayTracer_Texture_Chain.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
// TODO: missing uniquness check
bool Texture_Chain::addTexture(Texture *texture) {
	texture_list.push_back(texture);
	return true;
}


// TODO: not yet completed
bool Texture_Chain::rmTexture(Texture *texture) {
	return false;
}


Vec3f Texture_Chain::_getPixel_(const Ray *ray) const {
	Vec3f temp = ray->getPosition();
	for (auto *texture : texture_list) temp = texture->getPixel(temp);
	return temp;
}


void Texture_Chain::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


// Static Function Implementation
// ...
