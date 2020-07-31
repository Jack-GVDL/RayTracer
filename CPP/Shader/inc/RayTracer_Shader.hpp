// Created by Jack Tse on 2020/07/22
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/22   initial update


#ifndef RAYTRACER_SHADER_HPP
#define RAYTRACER_SHADER_HPP


#include "../../Material/Material.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter;


class Shader {
	// Data
	public:
		std::vector<Scatter*>	scatter_list;

	// Operation
	public:
		// operation
		bool	addScatter	(Scatter *scatter);
		bool	rmScatter	(Scatter *scatter);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SHADER_HPP
