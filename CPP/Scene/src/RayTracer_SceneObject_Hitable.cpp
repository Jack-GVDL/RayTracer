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


void SceneObject_Hitable::setMaterial(Material *material) {
	this->material = material;
}


int8_t SceneObject_Hitable::hit(RecordHit *record) const {
	return hit(record, std::numeric_limits<fp_t>::max());
}


int8_t SceneObject_Hitable::hit(RecordHit *record, fp_t t_max) const {
	return hit(record, 0.0, t_max);
}


// Static Function Implementation
// ...
