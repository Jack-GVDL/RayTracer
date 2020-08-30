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
	RecordHit		*record_hit	= &(src->record_hit.record);
	Material		*material	= &(record_hit->object->material);

	// get proportion of reflection
	Vec3f vec_reflective;
	texture_list[REFLECTIVE]->getPixel(vec_reflective, record_hit->point);
	
	// first check if hit a target
	if (!src->is_hit || vec_reflective.isZero()) {
		src->threshold *= (Vec3f(1) - vec_reflective);
		return;
	}

	// reflection
	const Vec3f &reflected = reflect(record_hit->ray.getDirection(), record_hit->normal);

	// create new child record
	RecordRay *record = (RecordRay*)memory_control->createRecord();
	if (record == nullptr) return;

	setRecord_tree(			record, src										);
	setRecord_ray(			record, src, Ray(record_hit->point, reflected)	);
	setRecord_threshold(	record, src, vec_reflective						);
	setRecord_scatter(		record, src										);
}


// Static Function Implementation
// or from the another source
// return v - 2 * dot(incident, normal) * normal;
static inline Vec3f reflect(const Vec3f &incident, const Vec3f &normal) {
	return (2.0 * normal.dot(-incident) * normal + incident).normalize();
}
