#include "../inc/RayTracer_Scatter_Reflection.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline Vec3f reflect(const Vec3f &incident, const Vec3f &normal);


// Operation Handling
Scatter_Reflection::Scatter_Reflection() {
	texture_list				= new Texture*[MAX];
	texture_size				= MAX;

	texture_list[REFLECTIVE]	= nullptr;
}


void Scatter_Reflection::scatter(RecordRay *src, MemoryControl_Scatter *memory_control) const {
	// variable preparation
	const Ray	*ray		= &(src->record_hit.ray);
	const Vec3f	&hit_point	= src->record_hit.point;
	const Vec3f	&hit_normal	= src->record_hit.normal;

	// get proportion of reflection
	Vec3f vec_reflective;
	texture_list[REFLECTIVE]->getPixel(vec_reflective, hit_point);
	
	// first check if hit a target
	if (!src->is_hit || vec_reflective.isZero()) {
		src->threshold *= (Vec3f(1) - vec_reflective);
		return;
	}

	// reflection
	const Vec3f &reflected = reflect(ray->getDirection(), hit_normal).normalize();

	// fire a new ray
	// need to push the point a little bit forward to prevent hit the same point
	const Vec3f &point_out = hit_point + reflected * RAY_EPSILON;

	// create new child record
	RecordRay *record = (RecordRay*)memory_control->createRecord();

	setRecord_tree(record, src);
	setRecord_ray(record, src, Ray(point_out, reflected));
	setRecord_threshold(record, src, vec_reflective);

	// backup
	// src->intensity = Vec3f(0);
}


// Static Function Implementation
// or from the another source
// return v - 2 * dot(incident, normal) * normal;
static inline Vec3f reflect(const Vec3f &incident, const Vec3f &normal) {
	return (2.0 * normal.dot(-incident) * normal + incident).normalize();
}
