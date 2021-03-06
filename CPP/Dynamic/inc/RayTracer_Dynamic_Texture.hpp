// Created by Jack Tse on 2020/07/30
//
// Log
// 2020/07/30	initial update
// 2020/08/09	change structure: Dynamic_ContainerType


#ifndef RAYTRACER_DYNAMIC_TEXTURE_HPP
#define RAYTRACER_DYNAMIC_TEXTURE_HPP


#include <vector>
#include "../../Tracer/Tracer.hpp"
#include "../inc/RayTracer_DynamicContainer.hpp"


// Define
// ...


// Typedef
// ...


// Enum
enum TypeTexture {
	TEXTURE_CONSTANT	= 0,
	TEXTURE_CHECKERBOARD,
	TEXTURE_IMAGE,
	TEXTURE_MAX
};


// Data Structure
// ...


// Macro Function
// ...


// Operation Handling
void	RayTracer_Dynamic_Texture_init	(std::vector<Dynamic_ContainerType*> *type_list);
void	RayTracer_Dynamic_Texture_info	();
void	RayTracer_Dynamic_Texture_del	();


// Inline Function Implementation
// ...


#endif	// RAYTRACER_DYNAMIC_TEXTURE_HPP