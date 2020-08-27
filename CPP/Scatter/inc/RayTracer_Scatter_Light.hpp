// Created by Jack Tse on 2020/06/24
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/24   initial update
// 2020/07/30   add texture_list


#ifndef RAYTRACER_SCATTER_LIGHT_HPP
#define RAYTRACER_SCATTER_LIGHT_HPP


#include "RayTracer_Scatter.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter_Light: public Scatter {
	// Enum
	public:
		enum ScatterTexture {
			DIFFUSE = 0,
			SPECULAR,
			EMISSIVE,
			AMBIENT,
			SHININESS,
			NORMAL,
			MAX
		};

	// Data
	public:
		// ...

	// Operation
	public:
		// init
		Scatter_Light()
		{
			texture_list = new Texture*[MAX];
			texture_size = MAX;

			texture_list[DIFFUSE]	= nullptr;
			texture_list[SPECULAR]	= nullptr;
			texture_list[EMISSIVE]	= nullptr;
			texture_list[AMBIENT]	= nullptr;
			texture_list[SHININESS]	= nullptr;
			texture_list[NORMAL]	= nullptr;
		}

	protected:
		// interface
		virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_LIGHT_HPP
