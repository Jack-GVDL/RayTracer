#include <algorithm>
#include "../inc/RayTracer_Scatter_Gradient.hpp"


// Define
typedef Vec3f(*source_func_t)(RecordHit *record);


// Static Function Prototype
static Vec3f get_source_empty		(RecordHit *record);
static Vec3f get_source_direction	(RecordHit *record);
static Vec3f get_source_position	(RecordHit *record);
static Vec3f get_source_normal		(RecordHit *record);
static Vec3f get_source_custom		(RecordHit *record);


// Static Data
static source_func_t source_func_list[Scatter_Gradient::SOURCE_MAX] = {
	get_source_empty,
	get_source_direction,
	get_source_position,
	get_source_normal,
	get_source_custom
};


// Operation Handling
void Scatter_Gradient::scatter(RecordRay *src, MemoryControl_Scatter *memory_control) const {
	if (!src->is_hit) {
		src->threshold = Vec3f(0);
		return;
	}

	// get source
	Vec3f vec_source = source_func_list[source](&(src->record_hit.record));
	
	// value addition and multiplication
	const fp_t	intensity_0	= (vec_source[0] + additor[0]) * multiplier[0];
	const fp_t	intensity_1	= (vec_source[1] + additor[1]) * multiplier[1];
	const fp_t	intensity_2	= (vec_source[2] + additor[2]) * multiplier[2];

	// need clamping
	vec_source[0]	= UtilMath::clamp<fp_t>(intensity_0, 0.0, 1.0);
	vec_source[1]	= UtilMath::clamp<fp_t>(intensity_1, 0.0, 1.0);
	vec_source[2]	= UtilMath::clamp<fp_t>(intensity_2, 0.0, 1.0);

	src->intensity	+= (src->threshold * vec_source);
	src->threshold	= 0;
}


// Static Function Implementation
static Vec3f get_source_empty(RecordHit *record) {
	return Vec3f();
}


static Vec3f get_source_direction(RecordHit *record) {
	return record->ray.getDirection();
}


static Vec3f get_source_position(RecordHit *record) {
	return record->ray.getPosition();
}


static Vec3f get_source_normal(RecordHit *record) {
	return record->normal;
}


// TODO: not yet completed
static Vec3f get_source_custom(RecordHit *record) {
	return Vec3f();
}


// Backup Code
/*
	switch (source) {
		case GradientSource::EMPTY:
			vec_source = Vec3f();
			break;

		case GradientSource::DIRECTION:
			vec_source = src->record_hit.ray.getDirection();
			break;
		
		case GradientSource::POSITION:
			vec_source = src->record_hit.ray.getPosition();
			break;

		case GradientSource::NORMAL:
			vec_source = src->record_hit.normal;
			break;

		case GradientSource::CUSTOM:
			if (ops_source == nullptr)	vec_source = Vec3f(0);
			else						vec_source = (*ops_source)(&(src->record_hit.ray));
			break;
	}
*/
