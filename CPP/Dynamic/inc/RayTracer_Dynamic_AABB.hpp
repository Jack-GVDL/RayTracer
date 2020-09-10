// Created by Jack Tse on 2020/09/04
//
// Log
// 2020/09/04   initial update


#ifndef RAYTRACER_DYNAIC_AABB_HPP
#define RAYTRACER_DYNAIC_AABB_HPP


#include <vector>
#include "../../Tracer/Tracer.hpp"
#include "../inc/RayTracer_DynamicContainer.hpp"


// Define
// ...


// Typedef
// ...


// Enum
enum TypeAABB {
	AABB_DEFAULT	= 0,
	AABB_MAX
};


// Data Structure
// ...


// Macro Function
// ...


// Operation Handling
void	RayTracer_Dynamic_AABB_init		(std::vector<Dynamic_ContainerType*> *type_list);
void	RayTracer_Dynamic_AABB_info		();
void	RayTracer_Dynamic_AABB_del		();


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAIC_AABB_HPP
