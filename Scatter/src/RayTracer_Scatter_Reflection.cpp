#include "../inc/RayTracer_Scatter_Reflection.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline Vec3f reflect(const Vec3f &incident, const Vec3f &normal);


// Operation Handling
ScatterState Scatter_Reflection::scatter_shootRay(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const {
	// first check if hit a target
	if (!src->is_hit) return SCATTER_NONE;

	// check if the material is reflective
	if (src->hit_record.object->material.reflective.isZero()) return SCATTER_NONE;

	// if hit a target
	// then do reflection
	const HitRecord	&hit_record	= src->hit_record;
	const Vec3f		&reflected	= reflect(src->ray.getDirection(), hit_record.normal).normalize();

	// fire a new ray
	// need to push the point a little bit forward to prevent hit the same point
	const Vec3f		&point_out	= hit_record.point + reflected * RAY_EPSILON;
	dst->ray = Ray(point_out, reflected);

	// split the threshold of src
	const Material	&material			= src->hit_record.object->material;
	const Vec3f		&threshold_child	= src->thresh.prod(material.reflective);
	dst->thresh							= threshold_child;
	src->thresh							-= threshold_child;

	return SCATTER_NEXT;
}


// Static Function Implementation
// or from the another source
// return v - 2 * dot(incident, normal) * normal;
static inline Vec3f reflect(const Vec3f &incident, const Vec3f &normal) {
	return (2.0 * normal.dot(-incident) * normal + incident).normalize();
}
