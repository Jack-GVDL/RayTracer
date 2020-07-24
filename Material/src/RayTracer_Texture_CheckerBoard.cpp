#include <cmath>
#include "../inc/RayTracer_Texture_CheckerBoard.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
void Texture_CheckerBoard::setBoardSize(const Vec3f &size) {
	size_board = size;
}


Vec3f Texture_CheckerBoard::getPixel(const Vec3f &point) const {
	double sines = sin(size_board[0] * point[0]) * 
				   sin(size_board[1] * point[1]) * 
				   sin(size_board[2] * point[2]);

	if (sines < 0) return Vec3f(0);
	return Vec3f(1);
}


// pixel cannot be set in this way
// so do nothing
void Texture_CheckerBoard::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


// Static Function Implementation
// ...
