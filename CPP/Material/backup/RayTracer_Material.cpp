#include "../inc/RayTracer_Material.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
Vec3f Material::getEmissive(Vec3f &point) {
	if (emissive == nullptr) return Vec3f();
	return emissive->getPixel(point);
}


Vec3f Material::getAmbient(Vec3f &point) {
	if (ambient == nullptr) return Vec3f();
	return ambient->getPixel(point);
}


Vec3f Material::getSpecular(Vec3f &point) {
	if (specular == nullptr) return Vec3f();
	return specular->getPixel(point);
}


Vec3f Material::getDiffuse(Vec3f &point) {
	if (diffuse == nullptr) return Vec3f();
	return diffuse->getPixel(point);
}


Vec3f Material::getReflective(Vec3f &point) {
	if (reflective == nullptr) return Vec3f();
	return reflective->getPixel(point);
}


Vec3f Material::getTransmissive(Vec3f &point) {
	if (transmissive == nullptr) return Vec3f();
	return transmissive->getPixel(point);
}


Vec3f Material::getShininess(Vec3f &point) {
	if (shininess == nullptr) return Vec3f();
	return shininess->getPixel(point);
}


Vec3f Material::getIndex(Vec3f &point) {
	if (index == nullptr) return Vec3f();
	return index->getPixel(point);
}



// Static Function Implementation
// ...
