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
		Material	*material;

	// Operation
	public:
		// init
		SceneObject_Sphere()
		{}

		SceneObject_Sphere(Vec3f center, double radius, Material *material): 
		center		(center), 
		radius		(radius), 
		material	(material)
		{}

		// operation
		virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &record) const override;
};


// Macro Function
// ...


// Operation
// TODO: move to cpp
bool SceneObject_Sphere::hit(const Ray &r, float t_min, float t_max, HitRecord &record) const {
	Vec3f oc = r.getPosition() - center;

	float a = RayTracer::dot(r.getDirection() , r.getDirection());
	float b = RayTracer::dot(oc, r.getDirection());
	float c = RayTracer::dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	// no intersection
	if (discriminant <= 0) return false;

	// ...
	float temp;

	temp = (-b - sqrt(b * b - a * c)) / a;
	if (temp < t_max && temp > t_min) {
		record.distance	= temp;
		record.point	= r.pointAt(record.distance);
		record.normal	= (record.point - center) / radius;
		record.object	= (SceneObject_Hitable*)this;
		return true;
	}

	temp = (-b + sqrt(b * b - a * c)) / a;
	if (temp < t_max && temp > t_min) {
		record.distance	= temp;
		record.point	= r.pointAt(record.distance);
		record.normal	= (record.point - center) / radius;
		record.object	= (SceneObject_Hitable*)this;
		return true;
	}

	return false;
}


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_SPHERE_HPP
