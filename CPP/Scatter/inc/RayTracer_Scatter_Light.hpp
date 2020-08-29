// Created by Jack Tse on 2020/06/24
//
// Log
// 2020/06/24   initial update
// 2020/07/30   add texture_list
// 2020/08/28   Scatter_AnyHit


#ifndef RAYTRACER_SCATTER_LIGHT_HPP
#define RAYTRACER_SCATTER_LIGHT_HPP


#include "RayTracer_Scatter.hpp"
#include "RayTracer_Scatter_AnyHit.hpp"


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

		Scatter_AnyHit	scatter_anyHit;
		Scatter*		scatter_list[1];

	// Data
	public:
		// ...

	// Operation
	public:
		// init
		Scatter_Light	();
		~Scatter_Light	();

	protected:
		// interface
		virtual void			scatter				(RecordRay *src, MemoryControl_Scatter *memory_control) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_LIGHT_HPP
