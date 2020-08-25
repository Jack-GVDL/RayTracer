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


void SceneElement::setBounding_max(const Vec3f &bounding) {
	this->bounding_max = bounding;
}


void SceneElement::setBounding_min(const Vec3f &bounding) {
	this->bounding_min = bounding;
}


bool SceneElement::addChild(SceneElement *scene) {
	child.push_back(scene);
	return true;
}


// TODO: not yet completed
bool SceneElement::rmChild(SceneElement *scene) {
	return false;
}


// Static Function Implementation
// ...
