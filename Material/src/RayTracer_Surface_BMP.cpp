#include "../inc/RayTracer_Surface_BMP.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
void Surface_BMP::setBMP(File_BMP *file) {
	this->file = file;
}


bool Surface_BMP::convertToTexture(Texture *texture) const {
	// check if file and texture exist or not
	if (texture == nullptr)		return false;
	if (file == nullptr)		return false;

	// allocate memory space for image
	// TODO: currently only can use RGBA
	// ...

	return true;
}


// Static Function Implementation
// ...
