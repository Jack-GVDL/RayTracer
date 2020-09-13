#include "../inc/RayTracer_Scatter_Refraction.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline bool	refract		(Vec3f &refracted, const Vec3f &incident, const Vec3f &normal, fp_t index_from, fp_t index_to);


// Operation Handling
Scatter_Refraction::Scatter_Refraction() {
	texture_list	= nullptr;
	texture_size	= MAX;
}


void Scatter_Refraction::scatter(RecordRay *src, MemoryControl_Scatter *memory_control) const {
	// variable preparation
	RecordHit		*record_hit	= &(src->record_hit.record);
	Material		*material	= record_hit->object->material;

	// check if this material is refractive
	Vec3f vec_transmissive;
	material->transmissive->getPixel(vec_transmissive, record_hit->point);

	// check if hit a target or material is not refractive
	if (!src->is_hit || vec_transmissive.isZero()) {
		src->threshold *= (Vec3f(1) - vec_transmissive);
		return;
	}
	
	// to check if the ray is entering or leaving the object
	// need to check the angle between ray and the normal
	//
	// as createRecord_tree will copy the RecordRay::outer
	// so it must be put before createRecord_outer
	RecordRay	temp;
	fp_t		index_from, index_to;

	setRecord_tree(&temp, src);
	// TODO: need to separate functionality of index configure and space ordering
	setRecord_outer(&temp, src, &index_from, &index_to);

	// refraction
	Vec3f refracted;
	if (!refract(refracted, record_hit->ray.getDirection(), record_hit->normal, index_from, index_to)) {
		src->threshold *= (Vec3f(1) - vec_transmissive);
		return;
	}

	// init record
	setRecord_ray(&temp, src, Ray(record_hit->point, refracted));
	setRecord_threshold(&temp, src, vec_transmissive);

	// copy to new record
	RecordRay *record = (RecordRay*)memory_control->createRecord();
	if (record == nullptr) return;
	
	memcpy(record, &temp, sizeof(RecordRay));
}


// index_out:	ray from
// index_in:	ray to
bool Scatter_Refraction::setRecord_outer(RecordRay *dst, RecordRay *src, fp_t *index_from, fp_t *index_to) const {
	// variable preparation
	const RecordHit	*record_hit		= &(src->record_hit.record);
	const Material	*material		= record_hit->object->material;
	const RecordRay	*record_outer	= src->outer;
	
	// check if outer space is air
	// i.e. the most outer space
	if (record_outer == nullptr) {
		*index_from	= RAY_INDEX_AIR;
		*index_to	= material->index;
		dst->outer	= src;
		return false;
	}

	// if exit from inner space
	// TODO: hard read code
	if (record_outer->record_hit.record.object == src->record_hit.record.object) {

		// if exit from inner space to the most outer space
		if (record_outer->outer == nullptr) {
			*index_from = material->index;
			*index_to	= RAY_INDEX_AIR;
			dst->outer	= nullptr;
			return true;
		}

		*index_from	= material->index;
		*index_to	= record_outer->outer->record_hit.record.object->material->index;
		dst->outer	= record_outer->outer;
		return true;
	}

	// if entering from outer space
	// TODO: hard read code
	*index_from	= record_outer->record_hit.record.object->material->index;
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
static inline bool refract(Vec3f &refracted, const Vec3f &incident, const Vec3f &normal, fp_t index_from, fp_t index_to) {
	const fp_t	dot_ln			= normal.dot(-incident);
	const fp_t	index_ratio		= index_from / index_to;
	const fp_t	root			= 1 - index_ratio * index_ratio * (1 - dot_ln * dot_ln);
	if (root <= 0) return false;

	const fp_t	coeff			= index_ratio * dot_ln - sqrt(root);
	refracted = (coeff * normal - index_ratio * (-incident)).normalize();
	return true;
}
