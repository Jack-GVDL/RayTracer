// Created by Jack Tse on 2020/06/24
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/24   initial update


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
	// Data
	public:
		Texture	*diffuse;
		Texture	*specular;
		Texture	*emissive;
		Texture	*ambient;
		Texture *shininess;

	// Operation
	public:
		// init
		Scatter_Light(Texture *diffuse, Texture *specular, Texture *emissive, Texture *ambient, Texture *shininess):
		diffuse		(diffuse),
		specular	(specular),
		emissive	(emissive),
		ambient		(ambient),
		shininess	(shininess)
		{}

		// interface
		virtual ScatterState	scatter_shootRay	(RecordScatter *dst, RecordScatter *src, ScatterState state) const override;

	protected:
		// operation
		Vec3f getEmissive	(const RecordScatter *record) const;
		Vec3f getAmbient	(const RecordScatter *record) const;
		Vec3f getDiffuse	(const RecordScatter *record, const SceneObject_Light *light, double dot_ln) const;
		Vec3f getSpecular	(const RecordScatter *record, const SceneObject_Light *light, double dot_ln) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_LIGHT_HPP
