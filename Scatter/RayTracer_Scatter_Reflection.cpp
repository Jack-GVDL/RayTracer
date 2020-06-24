#include "RayTracer_Scatter_Reflection.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline Vec3f reflect(const Vec3f &incident, const Vec3f &normal);


// Operation Handling
ScatterStatus Scatter_Reflection::_scatter_(ScatterRecord *dst, ScatterRecord *src) const {
	// first check if hit a target
	if (!src->is_hit) return SCATTER_NONE;

	// if hit a target
	// then do reflection
	const HitRecord &hit_record = src->hit_record;
	const Vec3f &reflected = reflect(src->ray.getDirection(), hit_record.normal);

	dst->ray = Ray(hit_record.point, reflected);

	// TODO: need to handle the threshold
	// ...

	return SCATTER_NEXT;
}


// Static Function Implementation
// or from the another source
// return v - 2 * dot(incident, normal) * normal;
static inline Vec3f reflect(const Vec3f &incident, const Vec3f &normal) {
	return (2.0 * normal.dot(-incident) * normal + incident).normalize();
}
