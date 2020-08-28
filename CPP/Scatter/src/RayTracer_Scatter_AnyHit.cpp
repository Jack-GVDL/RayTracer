#include "../inc/RayTracer_Scatter_AnyHit.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
Scatter_AnyHit::Scatter_AnyHit() {
	scatter_list[0] = this;
}


Scatter_AnyHit::~Scatter_AnyHit() {
}


void Scatter_AnyHit::scatter(RecordRay *src, MemoryControl_Scatter *memory_control) const {
	// check if hit
	// then check if can pass the hitable
	if (!src->is_hit) {
		src->threshold = Vec3f(0);
		return;
	}

	// new intensity *= transmissive
	RecordHit		*record_hit	= &(src->record_hit.record);
	const Material	*material	= &(record_hit->object->material);

	Vec3f vec_transmissive;
	material->transmissive->getPixel(vec_transmissive, record_hit->point);

	// fire a new ray
	const Vec3f &point_out = record_hit->point + record_hit->ray.getDirection() * RAY_EPSILON;

	// create new child record
	RecordRay *record = (RecordRay*)memory_control->createRecord();

	setRecord_tree(record, src);
	setRecord_ray(record, src, Ray(point_out, record_hit->ray.getDirection()));
	setRecord_threshold(record, src, vec_transmissive);

	// set next scatter source
	record->record_scatter.scatter_list	= (Scatter**)scatter_list;
	record->record_scatter.size			= 1;
	record->scatter_source				= 0;

	// reduce length
	record->record_hit.length_max		= src->record_hit.length_max - record_hit->distance;
}


// Static Function Implementation
// ...
