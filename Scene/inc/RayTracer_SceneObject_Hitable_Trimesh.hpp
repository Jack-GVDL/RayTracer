// Created by Jack Tse on 2020/07/03
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/03   initial update


#ifndef RAYTRACER_SCENEOBJECT_HITABLE_TRIMESH_HPP
#define RAYTRACER_SCENEOBJECT_HITABLE_TRIMESH_HPP


#include "RayTracer_SceneObject_Hitable.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class SceneObject_Trimesh: public SceneObject_Hitable {
	// Data
	public:
		Vec3f	point[3];

	// Operation
	public:
		// init
		SceneObject_Trimesh() {
		}

		SceneObject_Trimesh(Vec3f p0, Vec3f p1, Vec3f p2) {
			point[0]	= p0;
			point[1]	= p1;
			point[2]	= p2;
		}

		// operation
		virtual bool hit(const Ray *ray, float t_min, float t_max, HitRecord *record) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_TRIMESH_HPP
