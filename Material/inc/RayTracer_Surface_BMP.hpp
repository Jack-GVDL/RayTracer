// Created by Jack Tse on 2020/07/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/20   initial update


#ifndef RAYTRACER_SURFACE_BMP_HPP
#define RAYTRACER_SURFACE_BMP_HPP


#include "../../External/External.hpp"
#include "RayTracer_Surface.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Surface_BMP: public Surface {
	// Data
	public:
		uint8_t		*data	= nullptr;
		File_BMP	*file	= nullptr;
	
	// Operation
	public:
		// operation
		void			setBMP				(File_BMP *bmp);

		// interface
		virtual bool	convertToTexture	(Texture *texture) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SURFACE_BMP_HPP
