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
// TODO: find a better way to do the same thing
class Scene;


class SceneObject_Light: public SceneElement {
	// Data
	public:
		Vec3f	color;
		
	// Operation
	public:
		// operation
		void			setColor				(const Vec3f &color);
	
		// interface
		virtual Vec3f	getShadowAttenuation	(const Scene *scene, const Vec3f &point) const	= 0;
		virtual double	getDistanceAttenuation	(const Vec3f &point) const	= 0;
		virtual Vec3f	getColor				(const Vec3f &point) const	= 0;
		virtual Vec3f	getDirection			(const Vec3f &point) const	= 0;
};


class SceneObject_Light_Directional: public SceneObject_Light {
	// Data
	public:
		Vec3f	orientation		= Vec3f(0, 0, -1);

	// Operation
	public:
		// init
		SceneObject_Light_Directional()
		{}

		SceneObject_Light_Directional(const Vec3f &orientation):
		orientation(orientation)
		{}

		// operation
		void			setOrientation			(const Vec3f &color);

		// interface
		virtual Vec3f	getShadowAttenuation	(const Scene *scene, const Vec3f &point) const;
		virtual double	getDistanceAttenuation	(const Vec3f &point) const;
		virtual Vec3f	getColor				(const Vec3f &point) const;
		virtual Vec3f	getDirection			(const Vec3f &point) const;
};


class SceneObject_Light_Point: public SceneObject_Light {
	// Data
	public:
		Vec3f	attenuation_coeff	= Vec3f(0, 0, 0.25);

	// Operation
	public:
		// init
		SceneObject_Light_Point()
		{}

		SceneObject_Light_Point(const Vec3f &atten_coeff):
		attenuation_coeff(atten_coeff)
		{}

		// operation
		void			setAttenuationCoeff		(const Vec3f &coeff);

		// interface
		virtual Vec3f	getShadowAttenuation	(const Scene *scene, const Vec3f &point) const;
		virtual double	getDistanceAttenuation	(const Vec3f &point) const;
		virtual Vec3f	getColor				(const Vec3f &point) const;
		virtual Vec3f	getDirection			(const Vec3f &point) const;
};


class SceneObject_Light_Ambient: public SceneObject_Light {
	// Data
	public:
		// ...
		
	// Operation
	public:
		// interface
		virtual Vec3f	getShadowAttenuation	(const Scene *scene, const Vec3f &point) const override;
		virtual double	getDistanceAttenuation	(const Vec3f &point) const override;
		virtual Vec3f	getColor				(const Vec3f &point) const override;
		virtual Vec3f	getDirection			(const Vec3f &point) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_LIGHT_HPP
