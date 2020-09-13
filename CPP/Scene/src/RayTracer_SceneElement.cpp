#include "../inc/RayTracer_SceneElement.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
void SceneElement::setOrigin(const Vec3f &origin) {
	this->origin = origin;
}


// TODO: missing uniqueness check
error_t SceneElement::addChild(SceneElement *scene) {
	child.push_back(scene);
	return ERROR_NO;
}


// TODO: not yet completed
error_t SceneElement::rmChild(SceneElement *scene) {
	return ERROR_ANY;
}


// Static Function Implementation
// ...
