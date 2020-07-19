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
// TODO: find a better naming
namespace VecMath {
	// adjust normal with the incident ray
	// the ray normal should be oppose to the incident ray
	// i.e. normal.dot(incident_ray) < 0
	static inline Vec3f adjustNormal_incidentRay(const Vec3f &normal, const Vec3f &ray) {
		if (normal.dot(ray) < 0) return normal;
		return -normal;
	}

	// check if a point inside a convex polygon
	// normal is one of parameter as it is usually calculated in previous step
	static inline bool checkInside_convexPolygon(const Vec3f &point, const Vec3f *polygon, int size, const Vec3f &normal) {
		Vec3f temp;
		for (int i = 0; i < size - 1; i++) {
			temp = (polygon[i + 1] - polygon[i]).cross(point - polygon[i]);
			if (normal.dot(temp) < 0) return false;
		}

		// be careful wrapping problem
		// i.e. from last point to the first point
		temp = (polygon[0] - polygon[size - 1]).cross(point - polygon[size - 1]);
		if (normal.dot(temp) < 0) return false;
		return true;
	}
}


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_HPP
