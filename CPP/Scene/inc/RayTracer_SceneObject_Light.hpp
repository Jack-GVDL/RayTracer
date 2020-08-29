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
	// Data
	public:
		Vec3f	color;
		
	// Operation
	public:
		// init
		// ...

		// operation
		void			setColor				(const Vec3f &color);
	
		// interface
		// TODO: backup
		// virtual Vec3f	getShadowAttenuation	(const Scene *scene, const Vec3f &point) const	= 0;
		// virtual fp_t	getDistanceAttenuation	(const Vec3f &point) const	= 0;

		virtual fp_t	getAttenuation			(const Vec3f &point) const	= 0;
		virtual fp_t	getDistance				(const Vec3f &point) const	= 0;
		virtual Vec3f	getColor				(const Vec3f &point) const	= 0;
		virtual Vec3f	getDirection			(const Vec3f &point) const	= 0;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_LIGHT_HPP
