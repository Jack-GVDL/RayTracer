// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update
// 2020/07/03   add scatter_list


#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP


#include <vector>
#include "RayTracer_Ray.hpp"
#include "RayTracer_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Material {
	// Data
	public:
		Texture		*emissive		= nullptr;
		Texture		*ambient		= nullptr;
		Texture		*specular		= nullptr;
		Texture		*diffuse		= nullptr;
		Texture		*reflective		= nullptr;
		Texture		*transmissive	= nullptr;
		Texture		*shininess		= nullptr;
		Texture		*index			= nullptr;

	// Operation
	public:
		// operation
		virtual Vec3f	getEmissive		(Vec3f &point);
		virtual Vec3f	getAmbient		(Vec3f &point);
		virtual Vec3f	getSpecular		(Vec3f &point);
		virtual Vec3f	getDiffuse		(Vec3f &point);
		virtual Vec3f	getReflective	(Vec3f &point);
		virtual Vec3f	getTransmissive	(Vec3f &point);
		virtual Vec3f	getShininess	(Vec3f &point);
		virtual Vec3f	getIndex		(Vec3f &point);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_MATERIAL_HPP
