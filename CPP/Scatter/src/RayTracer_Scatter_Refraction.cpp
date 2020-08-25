#include "../inc/RayTracer_Scatter_Refraction.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline bool	refract		(Vec3f &refracted, const Vec3f &incident, const Vec3f &normal, double index_from, double index_to);


// Operation Handling
Scatter_Refraction::Scatter_Refraction() {
	texture_list	= nullptr;
	texture_size	= MAX;
}


ScatterState Scatter_Refraction::scatter_shootRay(RecordScatter *dst, RecordScatter *src, ScatterState state) const {
	// first check if hit a target
	// if hit a target
	// then do refraction
	if (!src->is_hit) return SCATTER_NONE;

	// variable preparation
	const Material	*material	= &(src->record_hit.object->material);
	const Ray		*ray		= &(src->record_hit.ray);
	const Vec3f		&hit_point	= src->record_hit.point;
	const Vec3f		&hit_normal	= src->record_hit.normal;

	// check if this material is refractive
	Vec3f vec_transmissive;
	material->transmissive->getPixel(vec_transmissive, hit_point);
	
	if (vec_transmissive.isZero()) return SCATTER_NONE;
	
	// to check if the ray is entering or leaving the object
	// need to check the angle between ray and the normal
	//
	// as createRecord_tree will copy the RecordScatter::outer
	// so it must be put before createRecord_outer
	double index_from, index_to;
	createRecord_tree(dst, src);
	createRecord_outer(dst, src, &index_from, &index_to);

	// refraction
	Vec3f refracted;
	if (!refract(refracted, ray->getDirection(), hit_normal, index_from, index_to)) return SCATTER_NONE;

	// fire a new ray
	// need to push the point a little bit forward to prevent hit the same point
	const Vec3f	&point_out = hit_point + refracted * RAY_EPSILON;

	// create new child record
	createRecord_ray(dst, src, Ray(point_out, refracted));
	createRecord_threshold(dst, src, vec_transmissive);

	return SCATTER_NEXT;
}


// index_out:	ray from
// index_in:	ray to
bool Scatter_Refraction::createRecord_outer(RecordScatter *dst, RecordScatter *src, double *index_from, double *index_to) const {
	// variable preparation
	const Material		*material		= &(src->record_hit.object->material);
	const RecordScatter	*record_outer	= src->outer;
	
	// check if outer space is air
	// i.e. the most outer space
	if (record_outer == nullptr) {
		*index_from	= RAY_INDEX_AIR;
		*index_to	= material->index;
		dst->outer	= src;
		return false;
	}

	// if exit from inner space
	if (record_outer->record_hit.object == src->record_hit.object) {

		// if exit from inner space to the most outer space
		if (record_outer->outer == nullptr) {
			*index_from = material->index;
			*index_to	= RAY_INDEX_AIR;
			dst->outer	= nullptr;
			return true;
		}

		*index_from	= material->index;
		*index_to	= record_outer->outer->record_hit.object->material.index;
		dst->outer	= record_outer->outer;
		return true;
	}

	// if entering from outer space
	*index_from	= record_outer->record_hit.object->material.index;
	*index_to	= material->index;
	dst->outer	= src;
	return false;
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
static inline bool refract(Vec3f &refracted, const Vec3f &incident, const Vec3f &normal, double index_from, double index_to) {
	const double dot_ln			= normal.dot(-incident);
	const double index_ratio	= index_from / index_to;
	const double root			= 1 - index_ratio * index_ratio * (1 - dot_ln * dot_ln);
	if (root <= 0) return false;

	const double coeff			= index_ratio * dot_ln - sqrt(root);
	refracted = (coeff * normal - index_ratio * (-incident)).normalize();
	return true;
}
