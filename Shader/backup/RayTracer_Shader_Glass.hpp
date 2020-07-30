// Created by Jack Tse on 2020/07/2
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/2   initial update


#ifndef RAYTRACER_SHADER_GLASS_HPP
#define RAYTRACER_SHADER_GLASS_HPP


#include "RayTracer_Shader.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Shader_Glass: public Shader {
	// Data
	public:
		Scatter_Reflection	scatter_reflection;
		Scatter_Refraction	scatter_refraction;
		Scatter_Light		scatter_light;

	// Operation
	public:
		// init
		Shader_Glass():
		scatter_reflection	( Scatter_Reflection(new Texture_Constant()) ),
		scatter_refraction	( Scatter_Refraction() ),
		scatter_light		( Scatter_Light(new Texture_Constant(),
											new Texture_Constant(),
											new Texture_Constant(),
											new Texture_Constant(),
											new Texture_Constant()) )
		{
			addScatter(&scatter_refraction);
			addScatter(&scatter_reflection);
			addScatter(&scatter_light);
		}
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SHADER_GLASS_HPP
