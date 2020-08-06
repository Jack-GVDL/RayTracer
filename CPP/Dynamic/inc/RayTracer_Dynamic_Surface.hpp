// Created by Jack Tse on 2020/07/30
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/30   initial update


#ifndef RAYTRACER_DYNAMIC_SURFACE_HPP
#define RAYTRACER_DYNAMIC_SURFACE_HPP


#include <vector>
#include "../../Tracer/Tracer.hpp"
#include "../inc/RayTracer_DynamicContainer.hpp"


// Define
// ...


// Typedef
// ...


// Enum
enum TypeSurface {
    SURFACE_CONSTANT    = 0,
    SURFACE_IMAGE,
    SURFACE_MAX
};


// Data Structure
// ...


// Macro Function
// ...


// Operation Handling
void	RayTracer_Dynamic_Surface_init	(std::vector<init_func_t>* init_list, std::vector<config_func_t>* config_list);
void    RayTracer_Dynamic_Surface_info  ();
void	RayTracer_Dynamic_Surface_del	();


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAMIC_SURFACE_HPP	
