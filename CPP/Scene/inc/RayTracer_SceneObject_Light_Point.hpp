// Created by Jack Tse on 2020/08/28
//
// Log
// 2020/08/28   initial update


#ifndef RAYTRACER_SCENEOBJECT_LIGHT_POINT_HPP
#define RAYTRACER_SCENEOBJECT_LIGHT_POINT_HPP


#include "RayTracer_SceneObject_Light.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class SceneObject_Light_Point: public SceneObject_Light {
	// Data
	public:
		Vec3f	attenuation	= Vec3f(0, 0, 0.25);

	// Operation
	public:
		// init
		SceneObject_Light_Point		();
		~SceneObject_Light_Point	();

		// operation
		void			setAttenuation			(const Vec3f &coeff);

		// interface
		// TODO: backup
		// virtual Vec3f	getShadowAttenuation	(const Scene *scene, const Vec3f &point) const;
		// virtual fp_t	getDistanceAttenuation	(const Vec3f &point) const;

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


#endif  // RAYTRACER_SCENEOBJECT_LIGHT_POINT_HPP
