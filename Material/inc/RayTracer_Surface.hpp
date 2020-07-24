// Created by Jack Tse on 2020/07/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/20   initial update
// 2020/07/24   change interface: add load, dump, remove convertToTexture


#ifndef RAYTRACER_SURFACE_HPP
#define RAYTRACER_SURFACE_HPP


#include "RayTracer_Texture.hpp"
#include "RayTracer_Texture_Image.hpp"


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
		uint8_t	*data	= nullptr;

		int 	width, height;		// image width and height (in pixel)
		int 	byte_data;			// byte size of data
		int 	bit_pixel;			// bit size per pixel
		int 	bit_channel;		// bit size per channel
		int 	size_channel;		// number of channel per pixel

	// Operation
	public:
		// operation
		bool			convertToTexture	(Texture_Image *texture);

		// interface
		virtual bool	load				() = 0;
		virtual bool	dump				() = 0;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SURFACE_HPP
