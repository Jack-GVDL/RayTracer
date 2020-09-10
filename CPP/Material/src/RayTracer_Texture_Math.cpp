#include "../inc/RayTracer_Texture_Math.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
// additor
void Texture_Math_Additor::setAdditor(const Vec3f &value) {
	this->additor = value;
}


// do nothing
void Texture_Math_Additor::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


void Texture_Math_Additor::_getPixel_(Vec3f &dst, Vec3f *src) const {
	dst = src[0] + additor;
}


// multiplier
void Texture_Math_Multiplier::setMultiplier(const Vec3f &value) {
	this->multiplier = value;
}


// do nothing
void Texture_Math_Multiplier::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


void Texture_Math_Multiplier::_getPixel_(Vec3f &dst, Vec3f *src) const {
	dst = src[0] * multiplier;
}


// Static Function Implementation
// ...
