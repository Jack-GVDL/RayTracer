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
		// interface
		virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &record) const = 0;
};


class SceneObject_HitableList: public SceneObject_Hitable {
	// Data
	public:
		std::vector<SceneObject_Hitable*>	hitable_list;

	// Operation
	public:
		// interface
		// TODO: move to cpp
		virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &record) const override {
			HitRecord	temp_record;
			bool		is_hit			= false;
			double		closest			= t_max;

			for (int i = 0; i < hitable_list.size(); i++) {
				if (!hitable_list[i]->hit(r, t_min, closest, temp_record)) continue;

				is_hit	= true;
				closest	= temp_record.distance;
				record	= temp_record;
			}

			return is_hit;
		}

		// operation
		// TODO: move to cpp
		virtual bool addHitable(SceneObject_Hitable *hitable) {
			hitable_list.push_back(hitable);
			addChild((SceneElement*)hitable);
			return true;
		}

		// TOOD: move to cpp
		// TODO: not yet completed
		virtual bool rmHitable(SceneObject_Hitable *hitable) {
		}
};


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_HPP
