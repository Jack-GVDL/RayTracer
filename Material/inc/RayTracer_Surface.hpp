// Created by Jack Tse on 2020/07/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/20   initial update


#ifndef RAYTRACER_SURFACE_HPP
#define RAYTRACER_SURFACE_HPP


#include "RayTracer_Texture.hpp"


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
		int size_data;	// size of data (in byte: 8 bit)

	// Operation
	public:
		virtual bool	convertToTexture	(Texture *texture) const = 0;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SURFACE_HPP
