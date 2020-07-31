// Created by Jack Tse on 2020/06/11
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/11   initial update


#ifndef RAYTRACER_HITABLE_HPP
#define RAYTRACER_HITABLE_HPP


#include "RayTracer_Ray.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Material;


struct HitRecord {
	float		t;
	Vec3f		p;
	Vec3f		normal;
	Material	*material;
};


class Hitable {
	// Operation
	public:
		// virtual
		virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &record) const = 0;
};


class HitableList: public Hitable {
	// Data
	public:
		Hitable*    *list;
		int         list_size;

	// Operation
	public:
		// init
		HitableList(){
		}

		HitableList(Hitable* *l, int n) {
			list        = l;
			list_size   = n;
		}

		// operation
		virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &record) const;
};


// Macro Function
// ...


// Operation
bool HitableList::hit(const Ray &r, float t_min, float t_max, HitRecord &record) const {
	HitRecord	temp_record;
	bool		is_hit = false;
	double		closest_so_far = t_max;

	for (int i = 0; i < list_size; i++) {
		if (!( list[i]->hit(r, t_min, closest_so_far, temp_record) )) continue;

		is_hit = true;
		closest_so_far = temp_record.t;
		record = temp_record;
	}

	return is_hit;
}


// Inline Function Implementation
// ...


#endif  // RAYTRACER_HITABLE_HPP
