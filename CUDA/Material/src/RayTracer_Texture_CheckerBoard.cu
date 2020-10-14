#include <cmath>
#include "../inc/RayTracer_Texture_CheckerBoard.cuh"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
__device__ Texture_CheckerBoard::Texture_CheckerBoard() {
	input_size	= 0;
	input_list	= nullptr;
	for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
}


__device__ Texture_CheckerBoard::~Texture_CheckerBoard() {
}


__device__ void Texture_CheckerBoard::setBoardSize(const Vec3f &size) {
	size_board = size;
}


__device__ void Texture_CheckerBoard::setBoardColor(const Vec3f &color_1, const Vec3f &color_2) {
	this->color_1	= color_1;
	this->color_2	= color_2;
}


// pixel cannot be set in this way
// so do nothing
__device__ void Texture_CheckerBoard::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


__device__ void Texture_CheckerBoard::_getPixel_(Vec3f &dst, Vec3f *src) const {
	// check if point should be black or white
	// one characteristic of sin / cos is periodic changes of y ranging [1, -1]
	fp_t sines 	= sin(size_board[0] * src[0][0]) * 
				  sin(size_board[1] * src[0][1]) * 
				  sin(size_board[2] * src[0][2]);

	if (sines < 0)	dst = color_1;
	else			dst = color_2;
}


// Static Function Implementation
// ...
