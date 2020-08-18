#include "../inc/RayTracer_Texture.hpp"


// Define
// TODO: may use stack buffer in future
#define MAX_LENGTH_VEC_BUFFER	16


// Static Data
// ...


// Static Function Prototype
static void	get_pixel	(Vec3f &dst, const Texture *texture, const Vec3f &src);


// Operation Handling
// TODO: backup
// TODO: need uniqueness checking
// bool Texture::addMapper(Mapper *mapper) {
// 	mapper_list.push_back(mapper);
// 	return true;
// }
//
//
// TODO: not yet completed
// bool Texture::rmMapper(Mapper *mapper) {
// 	return false;
// }


bool Texture::addInput(Texture *texture, int index) {
	if (index < 0 || index >= input_size) return false;
	input_list[index]	= texture;
	return true;
}


bool Texture::rmInput(int index) {
	if (index < 0 || index >= input_size) return false;
	input_list[index]	= nullptr;
	return true;
}


// TODO: backup
// backup
// void Texture::getPixel(Vec3f &dst, const Vec3f &src) const {
// 	Vec3f temp = src;
// 	for (auto *mapper : mapper_list) mapper->map(temp);

// 	_getPixel_(dst, temp);
// }


void Texture::getPixel(Vec3f &dst, const Vec3f &src) const {
	get_pixel(dst, this, src);
}


// Static Function Implementation
static void get_pixel(Vec3f &dst, const Texture *texture, const Vec3f &src) {
	// backtracking
	std::vector<Vec3f> point_list;
	for (int i = 0; i < texture->input_size; i++) {
		if (texture->input_list[i] == nullptr) continue;

		Vec3f temp;
		get_pixel(temp, texture->input_list[i], src);
		point_list.push_back(temp);

	}

	// add src
	point_list.push_back(src);

	// local
	texture->_getPixel_(dst, &point_list);
}
