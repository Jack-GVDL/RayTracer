// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update


#ifndef RAYTRACER_SCENEOBJECT_HITABLE_HPP
#define RAYTRACER_SCENEOBJECT_HITABLE_HPP


#include "RayTracer_SceneElement.hpp"


// Define
// ...


// Typedef
// ...


// Macro Function
// ...


// Enum
// ...


// Data Structure
class SceneObject_Hitable;


struct HitRecord {
	float					distance;
	Vec3f					point;
	Vec3f					normal;
	SceneObject_Hitable		*object;
};


class SceneObject_Hitable: public SceneElement {
	// Data
	public:
		Material	material;

	// Operation
	public:
		// init
		SceneObject_Hitable()
		{}

		SceneObject_Hitable(Material *material):
		material(*material)
		{}
		
		// operation
		bool			hit	(const Ray *ray, HitRecord *record) const;
		bool			hit	(const Ray *ray, float t_max, HitRecord *record) const;

		// interface
		virtual bool	hit	(const Ray *ray, float t_min, float t_max, HitRecord *record) const = 0;
};


class SceneObject_HitableList: public SceneObject_Hitable {
	// Data
	public:
		std::vector<SceneObject_Hitable*>	hitable_list;

	// Operation
	public:
		// interface
		virtual bool hit(const Ray *ray, float t_min, float t_max, HitRecord *record) const override;

		// operation
		virtual bool addHitable	(SceneObject_Hitable *hitable);
		virtual bool rmHitable	(SceneObject_Hitable *hitable);
};


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_HPP
