// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/01   initial update


#ifndef RAYTRACER_SURFACE_BMP_CUH
#define RAYTRACER_SURFACE_BMP_CUH


#include "../../External/External.hpp"
#include "RayTracer_Surface.cuh"
#include "RayTracer_Texture_Image.cuh"


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
		File_BMP	*file	= nullptr;
	
	// Operation
	public:
		// operation
		__host__ void			setBMP	(File_BMP *bmp);

		// interface
		__host__ virtual bool	load	() override;
		__host__ virtual bool	dump	() override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SURFACE_BMP_CUH
