#include "../inc/RayTracer_Scatter_AnyHit.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
__device__ Scatter_AnyHit::Scatter_AnyHit() {
	// texture
	// ...

	// scatter
	// backup
	// scatter_list[scatter_index] = this;
	// scatter_index++;

	addScatter(this);
}


__device__ Scatter_AnyHit::~Scatter_AnyHit() {
}


__device__ void Scatter_AnyHit::scatter(RecordRay *src, MemoryControl_Scatter *memory_control) const {
	// check if not hit
	// if not hit, it means it can hit the light source
	if (!src->is_hit) {
		// src->intensity += Vec3f(1) * src->threshold;
		src->intensity += src->threshold;
		src->threshold = Vec3f(0);
		return;
	}

	// new intensity *= transmissive
	RecordHit		*record_hit	= &(src->record_hit.record);
	const Material	*material	= record_hit->object->material;

	Vec3f vec_transmissive;
	material->transmissive->getPixel(vec_transmissive, record_hit->point);

	// check if hit a solid hitable
	if (vec_transmissive.isZero()) return;
	
	// create new child record
	RecordRay *record = (RecordRay*)memory_control->createRecord();
	if (record == nullptr) return;

	setRecord_tree(			record, src															);
	setRecord_ray(			record, src, Ray(record_hit->point, record_hit->ray.getDirection())	);
	setRecord_threshold(	record, src, vec_transmissive										);
	setRecord_scatter(		record, src															);

	// reduce length
	record->record_hit.length_max = src->record_hit.length_max - record_hit->distance;
}


// Static Function Implementation
// ...
