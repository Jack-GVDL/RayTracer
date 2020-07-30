// Created by Jack Tse on 2020/06/11
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/11   initial update


#ifndef RAYTRACER_SCENEOBJECT_HITABLE_SPHERE_HPP
#define RAYTRACER_SCENEOBJECT_HITABLE_SPHERE_HPP


#include "RayTracer_SceneObject_Hitable.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class SceneObject_Sphere: public SceneObject_Hitable {
	// Data
	public:
		Vec3f		center;
		double		radius;

	// Operation
	public:
		// init
		SceneObject_Sphere() {
		}

		SceneObject_Sphere(Vec3f center, double radius):
		center		(center), 
		radius		(radius) 
		{}

		// operation
		virtual bool hit(RecordHit *record, double t_min, double t_max) const override;
};


// Macro Function
// ...


// Operation
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_SPHERE_HPP