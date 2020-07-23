#include "../inc/RayTracer_Scatter_Refraction.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline bool	update_outer	(ScatterRecord *dst, ScatterRecord *ssrc, double *index_out, double *index_in);
static inline bool	refract			(Vec3f &refracted, const Vec3f &incident, const Vec3f &normal, double index_from, double index_to);


// Operation Handling
ScatterState Scatter_Refraction::scatter_shootRay(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const {
	// first check if hit a target
	// if hit a target
	// then do refraction
	if (!src->is_hit) return SCATTER_NONE;

	// check if this material is refractive
	const HitRecord &hit_record	= src->hit_record;
	const Material	&material	= hit_record.object->material;
	if (material.transmissive.isZero()) return SCATTER_NONE;
	
	// to check if the ray is entering or leaving the object
	// need to check the angle between ray and the normal
	double index_from, index_to;
	update_outer(dst, src, &index_from, &index_to);
	
	Vec3f normal = hit_record.normal;
	if (normal.dot(-src->ray.getDirection()) < 0) normal = -normal;

	// refraction
	Vec3f refracted;
	if (!refract(refracted, src->ray.getDirection(), normal, index_from, index_to)) return SCATTER_NONE;

	// fire a new ray
	// need to push the point a little bit forward to prevent hit the same point
	const Vec3f	&point_out = hit_record.point + refracted * RAY_EPSILON;
	dst->ray = Ray(point_out, refracted);

	// spit the threshold of src
	const Vec3f	&threshold_child	= src->thresh.prod(material.transmissive);
	dst->thresh						= threshold_child;
	src->thresh						-= threshold_child;

	return SCATTER_NEXT;
}


ScatterState Scatter_Refraction::scatter_buildTree(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const {
	switch (state) {
		case SCATTER_NONE:
			break;

		// build connection between scatter tree
		// the statement
		// dst->outer			= src->outer;
		// is removed as it will updated in Scatter_Refraction::shootRay
		case SCATTER_NEXT:
		case SCATTER_EQUAL_SPLIT:
			dst->parent			= src;
			dst->scene			= src->scene;
			dst->scatter		= this;
			dst->depth			= src->depth - 1;
			break;

		case SCATTER_YIELD:
			break;
	};

	return state;
}


// Static Function Implementation
// index_out:	ray from
// index_in:	ray to
static inline bool update_outer(ScatterRecord *dst, ScatterRecord *src, double *index_from, double *index_to) {
	// variable preparation
	const Material		&material_hit	= src->hit_record.object->material;
	const ScatterRecord	*record_outer	= src->outer;
	
	// check if outer space is air
	// i.e. the most outer space
	if (record_outer == nullptr) {
		*index_from	= RAY_INDEX_AIR;
		*index_to	= material_hit.index;
		dst->outer	= src;
		return false;
	}

	// if exit from inner space
	if (record_outer->hit_record.object == src->hit_record.object) {

		// if exit from inner space to the most outer space
		if (record_outer->outer == nullptr) {
			*index_from = material_hit.index;
			*index_to	= RAY_INDEX_AIR;
			dst->outer	= nullptr;
			return true;
		}

		*index_from	= material_hit.index;
		*index_to	= record_outer->outer->hit_record.object->material.index;
		dst->outer	= record_outer->outer;
		return true;
	}

	// if entering from outer space
	*index_from	= record_outer->hit_record.object->material.index;
	*index_to	= material_hit.index;
	dst->outer	= src;
	return false;
}


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
static inline bool refract(Vec3f &refracted, const Vec3f &incident, const Vec3f &normal, double index_from, double index_to) {
	const double dot_ln			= normal.dot(-incident);
	const double index_ratio	= index_from / index_to;
	const double root			= 1 - index_ratio * index_ratio * (1 - dot_ln * dot_ln);
	if (root <= 0) return false;

	const double coeff			= index_ratio * dot_ln - sqrt(root);
	refracted = (coeff * normal - index_ratio * (-incident)).normalize();
	return true;
}
