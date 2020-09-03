#include <limits>
#include "../inc/RayTracer_SceneObject_Hitable.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// hitable
SceneObject_Hitable::SceneObject_Hitable() {
}


SceneObject_Hitable::~SceneObject_Hitable() {
}


bool SceneObject_Hitable::hit(RecordHit *record) const {
	return hit(record, std::numeric_limits<fp_t>::max());
}


bool SceneObject_Hitable::hit(RecordHit *record, fp_t t_max) const {
	return hit(record, 0.0, t_max);
}


// hitable list
bool SceneObject_HitableList::hit(RecordHit *record, fp_t t_min, fp_t t_max) const {
	RecordHit	temp_record;
	bool		is_hit			= false;
	fp_t		closest			= t_max;

	// set ray
	temp_record.ray = record->ray;

	// search for hitable in child
	for (auto *hitable : hitable_list) {
		if (!hitable->hit(&temp_record, t_min, closest)) continue;

		is_hit			= true;
		closest			= temp_record.distance;
		*record			= temp_record;
	}

	return is_hit;
}


bool SceneObject_HitableList::addHitable(SceneObject_Hitable *hitable) {
	hitable_list.push_back(hitable);
	addChild((SceneElement*)hitable);
	return true;
}


// TODO: not yet completed
bool SceneObject_HitableList::rmHitable(SceneObject_Hitable *hitable) {
	return false;
}


// Static Function Implementation
// ...
