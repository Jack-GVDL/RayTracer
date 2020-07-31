#include "../inc/RayTracer_Scatter_Reflection.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline Vec3f reflect(const Vec3f &incident, const Vec3f &normal);


// Operation Handling
ScatterState Scatter_Reflection::scatter_shootRay(RecordScatter *dst, RecordScatter *src, ScatterState state) const {
	// first check if hit a target
	if (!src->is_hit)				return SCATTER_NONE;

	// variable preparation
	const Ray	*ray		= &(src->record_hit.ray);
	const Vec3f	&hit_point	= src->record_hit.point;
	const Vec3f	&hit_normal	= src->record_hit.normal;

	// check if the material is reflective
	const Vec3f &vec_reflective = texture_list[REFLECTIVE]->getPixel(hit_point);
	if (vec_reflective.isZero())	return SCATTER_NONE;

	// reflection
	const Vec3f &reflected = reflect(ray->getDirection(), hit_normal).normalize();

	// fire a new ray
	// need to push the point a little bit forward to prevent hit the same point
	const Vec3f &point_out = hit_point + reflected * RAY_EPSILON;

	// create new child record
	createRecord_tree(dst, src);
	createRecord_ray(dst, src, Ray(point_out, reflected));
	createRecord_threshold(dst, src, vec_reflective);

	return SCATTER_NEXT;
}


// Static Function Implementation
// or from the another source
// return v - 2 * dot(incident, normal) * normal;
static inline Vec3f reflect(const Vec3f &incident, const Vec3f &normal) {
	return (2.0 * normal.dot(-incident) * normal + incident).normalize();
}
