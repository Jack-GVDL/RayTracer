// Created by Jack Tse on 2020/08/28
//
// Log
// 2020/08/28   initial update


#ifndef RAYTRACER_SCENEOBJECT_LIGHT_AMBIENT_HPP
#define RAYTRACER_SCENEOBJECT_LIGHT_AMBIENT_HPP


#include "RayTracer_SceneObject_Light.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Light_Ambient: public SceneObject_Light {
	// Data
	public:
		// ...
		
	// Operation
	public:
		// interface
		virtual fp_t	getAttenuation			(const Vec3f &point) const override;
		virtual fp_t	getDistance				(const Vec3f &point) const override;
		virtual Vec3f	getColor				(const Vec3f &point) const override;
		virtual Vec3f	getDirection			(const Vec3f &point) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_LIGHT_AMBIENT_HPP
