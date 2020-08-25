#include "../inc/RayTracer_Texture.hpp"


// Define
// TODO: may use stack buffer in future
#define MAX_LENGTH_VEC_BUFFER	8


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
	Vec3f point_list[MAX_LENGTH_VEC_BUFFER];
	for (int i = 0; i < texture->input_size; i++) {

		if (texture->input_list[i] == nullptr) {
			point_list[i] = Vec3f(0);
			continue;
		}

		Vec3f temp;
		get_pixel(temp, texture->input_list[i], src);
		point_list[i] = temp;

	}

	// add src
	point_list[texture->input_size] = src;

	// local
	texture->_getPixel_(dst, point_list);

	// TODO: backup
	// backtracking
	// std::vector<Vec3f> point_list;
	// for (int i = 0; i < texture->input_size; i++) {
	//
	// 	if (texture->input_list[i] == nullptr) {
	// 		point_list.push_back(Vec3f(0));
	// 		continue;
	// 	}
	//
	// 	Vec3f temp;
	// 	get_pixel(temp, texture->input_list[i], src);
	// 	point_list.push_back(temp);
	//
	// }
	//
	// // add src
	// point_list.push_back(src);
	//
	// // local
	// texture->_getPixel_(dst, point_list.data());
}
