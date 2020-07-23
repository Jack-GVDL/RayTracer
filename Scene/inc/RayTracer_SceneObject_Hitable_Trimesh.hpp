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
			point[0]	= Vec3f();
			point[1]	= Vec3f();
			point[2]	= Vec3f();
		}

		// SceneObject_Trimesh(Vec3f p0, Vec3f p1, Vec3f p2) {
		// 	point[0]	= p0;
		// 	point[1]	= p1;
		// 	point[2]	= p2;
		// }

		SceneObject_Trimesh(Vec3f p0, Vec3f p1, Vec3f p2, Material *material):
		SceneObject_Hitable::SceneObject_Hitable(material)
		{
			point[0]	= p0;
			point[1]	= p1;
			point[2]	= p2;
		}

		// operation
		virtual bool hit(RecordHit *record, double t_min, double t_max) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_TRIMESH_HPP
