#include "../inc/RayTracer_Texture.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// texture
// TODO: need uniqueness checking
bool Texture::addMapper(Mapper *mapper) {
	mapper_list.push_back(mapper);
	return true;
}


// TODO: not yet completed
bool Texture::rmMapper(Mapper *mapper) {
	return false;
}


Vec3f Texture::getPixel(const Vec3f &point) const {
	Ray ray = Ray(point, Vec3f(0));
	return getPixel(&ray);
}


Vec3f Texture::getPixel(const Ray *ray) const {
	Vec3f point = ray->getPosition();
	for (auto *mapper : mapper_list) mapper->map(point);

	Ray ray_temp = Ray(point, ray->getDirection());
	return _getPixel_(&ray_temp);
}


// texture_constant
Vec3f Texture_Constant::_getPixel_(const Ray *ray) const {
	return color;
}


void Texture_Constant::setPixel(const Vec3f &point, const Vec3f &pixel) {
	// UNUSED(pixel)
	color = pixel;
}


// Static Function Implementation
// ...
