#include "../inc/RayTracer_Scatter_Refraction.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline bool refract(Vec3f &refracted, const Vec3f &incident, const Vec3f &normal, double index_1, double index_2);


// Operation Handling
ScatterState Scatter_Refraction::_scatter_(ScatterRecord *dst, ScatterRecord *src) const {
	// first check if hit a target
	if (!src->is_hit) return SCATTER_NONE;

	// if hit a target
	// then do refraction
	const HitRecord &hit_record	= src->hit_record;
	const Material	&material	= hit_record.object->material;
	
	// to check if the ray is entering or leaving the object
	// need to check the angle between ray and the normal
	double index_1, index_2;
	// TODO: not yet completed

	Vec3f refracted;
	if (!refract(refracted, src->ray.getDirection(), hit_record.normal, index_1, index_2)) return SCATTER_NONE;

	// TODO: need to handle the threshold
	// ...

	dst->ray = Ray(hit_record.point, refracted);
	return SCATTER_NEXT;
}


// Static Function Implementation
// from other source
/*
 * Vec3f uv = v.normalize()
 * float dt = dot(v, n);
 * float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
 * if (discriminant <= 0) return false;
 * refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
 * return true;
 * 
 */
static inline bool refract(Vec3f &refracted, const Vec3f &incident, const Vec3f &normal, double index_1, double index_2) {
	const double dot_ln			= normal.dot(-incident);
	const double index_ratio	= index_1 / index_2;
	const double root			= 1 - index_ratio * index_ratio * (1 - dot_ln * dot_ln);

	// check if total internal refraction
	if (root <= 0.0) return false;

	const double coeff = index_ratio * dot_ln - sqrt(root);
	refracted = (coeff * normal - index_ratio * (-incident)).normalize();
	return true;
}
