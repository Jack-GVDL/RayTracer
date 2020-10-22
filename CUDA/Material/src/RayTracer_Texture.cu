#include "../inc/RayTracer_Texture.cuh"

// TODO: test
#include <stdio.h>


// Define
// TODO: may use stack buffer in future
#define MAX_LIST_SIZE_POINT		16
#define MAX_LIST_SIZE_RECORD	12


// Data Structure
// TODO: should it be this name ?
struct RecordTexture{
	const Texture	*texture;
	int8_t			index_texture;
	int8_t			index_point;
};


// Static Data
// ...


// Static Function Prototype
__device__ static void	get_pixel	(Vec3f &dst, const Texture *texture, const Vec3f &src);


// Operation Handling
__device__ Texture::Texture() {
}


__device__ Texture::~Texture() {
	delete[] input_list;
}


__device__ error_t Texture::addInput(Texture *texture, int32_t index) {
	if (index < 0 || index >= input_size) return ERROR_ANY;
	input_list[index] = texture;
	return ERROR_NO;
}


__device__ error_t Texture::rmInput(int32_t index) {
	if (index < 0 || index >= input_size) return ERROR_ANY;
	input_list[index] = nullptr;
	return ERROR_NO;
}


__device__ void Texture::getPixel(Vec3f &dst, const Vec3f &src) const {
	get_pixel(dst, this, src);
}


// Static Function Implementation
__device__ static void get_pixel(Vec3f &dst, const Texture *texture, const Vec3f &src) {
	// recursive
	// cannot function on device (GPU)
	// it is the problem on allocation of point_list[MAX_LENGTH_VEC_BUFFER]
	/*
	// backtracking
	Vec3f point_list[MAX_LENGTH_VEC_BUFFER];

	for (int32_t i = 0; i < texture->input_size; ++i) {

		// backup
		// if (texture->input_list == nullptr) {
		// 	point_list[i] = Vec3f(0);
		// 	continue;
		// }

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
	*/

	// iterative
	Vec3f			list_point[MAX_LIST_SIZE_POINT];
	RecordTexture	stack_texture[MAX_LIST_SIZE_RECORD];
	int8_t			index_texture = 1;  // 1 for the top texture

	RecordTexture	*record;
	Vec3f			ret;

	// set list point
	// make it return Vec3f(0) if no overwriting on list_point[0]
	list_point[0] = Vec3f(0);

	// base texture
	// stack_texture[0].texture		= nullptr;
	stack_texture[0].index_texture	= 0;
	stack_texture[0].index_point	= 0;
	
	// push the top texture
	stack_texture[1].texture		= texture;
	stack_texture[1].index_texture	= 0;
	stack_texture[1].index_point	= 1;

	while (index_texture != 0) {

		record = stack_texture + index_texture;

		// push texture
		if (record->index_texture < record->texture->input_size) {
			++index_texture;

			stack_texture[index_texture].texture		= record->texture->input_list[record->index_texture];
			stack_texture[index_texture].index_texture	= 0;
			stack_texture[index_texture].index_point	= record->index_point + record->texture->input_size;
			continue;
		}

		// current level
		list_point[record->index_point + record->texture->input_size] = src;
		record->texture->_getPixel_(ret, list_point + record->index_point);

		// pop texture
		--index_texture;

		// for the new top texture
		// first set the return Vec3f
		// then increment the index_texture by 1 (next texture in the input list)
		record = stack_texture + index_texture;

		list_point[record->index_point + record->index_texture] = ret;
		++(record->index_texture);
	}

	dst = list_point[0];
}
