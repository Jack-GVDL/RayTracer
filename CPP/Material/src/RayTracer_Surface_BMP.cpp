#include <string.h>
#include <stdint.h>
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


bool Surface_BMP::load() {
	if (file == nullptr) return false;

	// variable for ease of access
	const File_BMP_InfoHeader *info_header = &(file->info_header);

	// set pixel info
	bit_channel	= 8;  // TODO: not yet completed
	bit_pixel	= info_header->bit_count;

	// set image info
	width		= info_header->width;
	height		= info_header->height;

	// it should also be
	// byte_data = width * height;
	byte_data	= file->data.size();

	// check if able to flush data
	// TODO: currently only can handle RGB_888
	if (bit_pixel != 24) {
		data = nullptr;
		return false;
	}

	// allocate space for data
	// then set the content of data
	data = new uint8_t[((bit_pixel + 7) / 8) * (width * height)];

	// TODO: need to find a way to do custom conversion
	// TODO: currently only can handle RGB_888
	// it should be noticed that
	// for Surface
	// RGB (from low bit to high bit)
	//
	// for BMP
	// BGR (from low bit to high bit), actually need to see mask header
	for (int i = 0; i < width * height; i++) {
		data[i * 3 + 0] = file->data.data()[i * 3 + 2];
		data[i * 3 + 1] = file->data.data()[i * 3 + 1];
		data[i * 3 + 2] = file->data.data()[i * 3 + 0];
	}

	// memcpy(data, file->data.data(), byte_data);

	return true;
}


bool Surface_BMP::dump() {
	if (file == nullptr) return false;

	// delete data
	delete[] data;
	data = nullptr;

	return true;
}


// Static Function Implementation
// ...
