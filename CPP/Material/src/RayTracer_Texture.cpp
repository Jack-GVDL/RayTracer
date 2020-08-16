#include "../inc/RayTracer_Texture.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// static void	get_pixel	(Vec3f &dst, const Vec3f &src);


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


// TODO: need uniqueness checking
bool Texture::addInput(Texture *texture) {
	input_list.push_back(texture);
	return true;
}


// TODO: not yet completed
bool Texture::rmInput(Texture *texture) {
	return false;
}


// TODO: old version
// backup
void Texture::getPixel(Vec3f &dst, const Vec3f &src) const {
	Vec3f temp = src;
	for (auto *mapper : mapper_list) mapper->map(temp);

	_getPixel_(dst, temp);
}


// TODO: new version
// void Texture::getPixel(Vec3f &dst, const Vec3f &src) const {
// }


// Static Function Implementation
// static void get_pixel(Vec3f &dst, const Vec3f &src) {

// }


// Static Function Implementation
// ...
