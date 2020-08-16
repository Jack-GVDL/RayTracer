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


void Texture_Math_Additor::setPixel(const Vec3f &point, const Vec3f &pixel) {

}


void Texture_Math_Additor::_getPixel_(Vec3f &dst, const Vec3f &src) const {
	dst += additor;
}


// multiplier
void Texture_Math_Multiplier::setMultiplier(const Vec3f &value) {
	this->multiplier = value;
}


void Texture_Math_Multiplier::setPixel(const Vec3f &point, const Vec3f &pixel) {

}


void Texture_Math_Multiplier::_getPixel_(Vec3f &dst, const Vec3f &src) const {
	dst *= multiplier;
}


// Static Function Implementation
// ...