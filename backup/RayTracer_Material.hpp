// Created by Jack Tse on 2020/06/12
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/12   initial update


#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP


#include "RayTracer_Ray.hpp"
#include "RayTracer_Hitable.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Operation Prototype
float	schlick					(float cosine, float ref_idx);
Vec3f	reflect					(const Vec3f &v, const Vec3f &n);
bool	refract					(const Vec3f &v, const Vec3f &n, float ni_over_nt, Vec3f &refracted);
Vec3f 	random_in_unit_sphere	();


// Data Structure
class Material {
	// Operation
	public:
		// operation
		virtual bool scatter(const Ray &r_in, const HitRecord &record, Vec3f &attenuation, Ray &scattered) const = 0;
};


class Material_Empty: public Material {
	// Data
	public:
		Vec3f	albedo;

	// Operation
	public:
		// init
		Material_Empty(const Vec3f &a)
		: albedo(a) {
		}

		// operation
		virtual bool scatter(const Ray &r_in, const HitRecord &record, Vec3f &attenuation, Ray &scattered) const override {
			return true;
		}
};


class Material_Lambertian: public Material {
	// Data
	public:
		Vec3f   albedo;

	// Operation
	public:
		// init
		Material_Lambertian(const Vec3f &a)
		: albedo(a) {
		}

		// operation
		virtual bool scatter(const Ray &r_in, const HitRecord &record, Vec3f &attenuation, Ray &scattered) const override {
			Vec3f target = record.p + record.normal + random_in_unit_sphere();
			scattered = Ray(record.p, target - record.p);
			attenuation = albedo;
			return true;
		}
};



class Material_Metal: public Material {
	// Data
	public:
		Vec3f   albedo;
		float	fuzz;

	// Operation
	public:
		// init
		Material_Metal(const Vec3f &a, float f)
		: albedo(a) {
			if (f < 1)	fuzz = f;
			else		fuzz = 1;
		}

		// operation
		virtual bool scatter(const Ray &r_in, const HitRecord &record, Vec3f &attenuation, Ray &scattered) const override {
			Vec3f reflected = reflect(r_in.getDirection().normalize(), record.normal);
			scattered = Ray(record.p, reflected + fuzz * random_in_unit_sphere());
			attenuation = albedo;
			return (scattered.getDirection().dot(record.normal) > 0);
		}
};


class Material_Dielectric: public Material {
	// Data
	public:
		float ref_idx;

	// Operation
	public:
		// init
		Material_Dielectric(float ri): 
		ref_idx(ri)
		{}

		// override
		virtual bool scatter(const Ray &r_in, const HitRecord &record, Vec3f &attenuation, Ray &scattered) const {
			Vec3f	outward_normal;
			Vec3f	reflected = reflect(r_in.getDirection(), record.normal);
			float	ni_over_nt;

			attenuation = Vec3f(1.0, 1.0, 1.0);
			Vec3f	refracted;
			float	reflect_prob;
			float	cosine;
			
			if (dot(r_in.getDirection(), record.normal) > 0) {
				outward_normal	= -record.normal;
				ni_over_nt		= ref_idx;
				cosine			= ref_idx * dot(r_in.getDirection(), record.normal) / r_in.getDirection().length();
			} else {
				outward_normal	= record.normal;
				ni_over_nt		= 1.0 / ref_idx;
				cosine			= -dot(r_in.getDirection(), record.normal) / r_in.getDirection().length();
			}

			if (refract(r_in.getDirection(), outward_normal, ni_over_nt, refracted)) {
				reflect_prob = schlick(cosine, ref_idx);
			} else {
				scattered = Ray(record.p, reflected);
				reflect_prob = 1.0;
			}
			if (drand48() < reflect_prob) {
				scattered = Ray(record.p, reflected);
			} else{
				scattered = Ray(record.p, refracted);
			}

			return true;
		}
};


// Operation Implementation
float schlick(float cosine, float ref_idx) {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}


Vec3f reflect(const Vec3f &v, const Vec3f &n) {
	return v - 2 * dot(v, n) * n;
}


bool refract(const Vec3f &v, const Vec3f &n, float ni_over_nt, Vec3f &refracted) {
	Vec3f uv = v.normalize();
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	} else {
		return false;
	}
}


Vec3f random_in_unit_sphere() {
	Vec3f p;
	do {
		p = 2.0 * Vec3f(drand48(), drand48(), drand48()) - Vec3f(1, 1, 1);
	} while (p.length_squared() >= 1.0);
	return p;
}


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_MATERIAL_HPP
