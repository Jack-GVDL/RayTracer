#include "../inc/RayTracer_SceneElement.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
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