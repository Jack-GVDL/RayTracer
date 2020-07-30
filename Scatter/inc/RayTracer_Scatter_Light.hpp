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
			MAX
		};

	// Data
	public:
		// backup
		// Texture	*diffuse	= nullptr;
		// Texture	*specular	= nullptr;
		// Texture	*emissive	= nullptr;
		// Texture	*ambient	= nullptr;
		// Texture *shininess	= nullptr;

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
		}

		Scatter_Light(Texture *diffuse, Texture *specular, Texture *emissive, Texture *ambient, Texture *shininess)
		{
			texture_list = new Texture*[MAX];
			texture_size = MAX;

			texture_list[DIFFUSE]	= diffuse;
			texture_list[SPECULAR]	= specular;
			texture_list[EMISSIVE]	= emissive;
			texture_list[AMBIENT]	= ambient;
			texture_list[SHININESS]	= shininess;
		}

		// interface
		virtual ScatterState	scatter_shootRay	(RecordScatter *dst, RecordScatter *src, ScatterState state) const override;

	protected:
		// operation
		// ...
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_LIGHT_HPP