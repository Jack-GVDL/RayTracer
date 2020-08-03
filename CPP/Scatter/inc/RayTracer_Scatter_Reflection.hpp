// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update
// 2020/07/20   change structure
// 2020/07/30   add texture_list


#ifndef RAYTRACER_SCATTER_REFLECTION_HPP
#define RAYTRACER_SCATTER_REFLECTION_HPP


#include "RayTracer_Scatter.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scatter_Reflection: public Scatter {
	// Enum
	public:
		enum ScatterTexture {
			REFLECTIVE = 0,
			MAX
		};

	// Data
	public:
		// backup
		// Texture		*reflective	= nullptr;

	// Operation
	public:
		// init
		Scatter_Reflection()
		{
			texture_list = new Texture*[MAX];
			texture_size = MAX;

			texture_list[REFLECTIVE]	= nullptr;

		}


		Scatter_Reflection(Texture *reflective)
		{
			texture_list = new Texture*[MAX];
			texture_size = MAX;

			texture_list[REFLECTIVE]	= reflective;
		}

		// interface
		virtual ScatterState	scatter_shootRay	(RecordScatter *dst, RecordScatter *src, ScatterState state) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_REFLECTION_HPP
