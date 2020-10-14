// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/07/20   initial update
// 2020/09/12   add Scatter



#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP


#include <vector>
#include "RayTracer_Texture.hpp"
#include "RayTracer_Texture_Constant.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter;


class Material {
	// Data
	public:
		Texture					*transmissive;
		// Texture					*index;
		fp_t					index;

		std::vector<Scatter*>	scatter_list;

	// Operation
	public:
		// init
		Material	();
		~Material	();

		// operation
		error_t addScatter	(Scatter *scatter);
		error_t	rmScatter	(Scatter *scatter);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_MATERIAL_HPP
