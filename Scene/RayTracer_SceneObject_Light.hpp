// Created by Jack Tse on 2020/06/24
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/24   initial update


#ifndef RAYTRACER_SCENEOBJECT_LIGHT_HPP
#define RAYTRACER_SCENEOBJECT_LIGHT_HPP


#include "RayTracer_SceneElement.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class SceneObject_Light: public SceneElement {
	// Operation
	public:
		// interface
		virtual Vec3f	getShadowAttenuation	(const Vec3f &point) const	= 0;
		virtual double	getDistanceAttenuation	(const Vec3f &point) const	= 0;
		virtual Vec3f	getColor				(const Vec3f &point) const	= 0;
		virtual Vec3f	getDirection			(const Vec3f &point) const	= 0;
};


class SceneObject_Light_Directional: public SceneObject_Light {
	// Data
	public:
		Vec3f	orientation;

	// Operation
	public:
		// init
		SceneObject_Light_Directional():
		orientation(Vec3f())
		{}

		// interface
		virtual Vec3f	getShadowAttenuation	(const Vec3f &point) const;
		virtual double	getDistanceAttenuation	(const Vec3f &point) const;
		virtual Vec3f	getColor				(const Vec3f &point) const;
		virtual Vec3f	getDirection			(const Vec3f &point) const;
};


class SceneObject_Light_Point: public SceneObject_Light {
	// Data
	public:
		Vec3f	attenuation_coeff;

	// Operation
	public:
		// init
		SceneObject_Light_Point():
		attenuation_coeff(Vec3f(0.0, 0.0, 1.0))
		{}

		// interface
		virtual Vec3f	getShadowAttenuation	(const Vec3f &point) const;
		virtual double	getDistanceAttenuation	(const Vec3f &point) const;
		virtual Vec3f	getColor				(const Vec3f &point) const;
		virtual Vec3f	getDirection			(const Vec3f &point) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_LIGHT_HPP
