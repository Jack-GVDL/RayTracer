// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/01   initial update


#ifndef RAYTRACER_SURFACE_CUH
#define RAYTRACER_SURFACE_CUH


#include "RayTracer_Texture.cuh"
#include "RayTracer_Texture_Image.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Surface {
	// Data
	public:
		uint8_t		*data	= nullptr;

		int32_t 	width, height;		// image width and height (in pixel)
		int32_t 	byte_data;			// byte size of data
		int32_t 	bit_pixel;			// bit size per pixel
		int32_t 	bit_channel;		// bit size per channel
		int32_t 	size_channel;		// number of channel per pixel

	// Operation
	public:
		// operation
		__host__ bool			convertToTexture	(Texture_Image *texture);

		// interface
		__host__ virtual bool	load				() = 0;
		__host__ virtual bool	dump				() = 0;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SURFACE_CUh
