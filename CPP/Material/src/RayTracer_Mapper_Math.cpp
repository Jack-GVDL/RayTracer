#include "../inc/RayTracer_Mapper_Math.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// additor
void Mapper_Additor::setAdditor(const Vec3f &value) {
	this->additor = value;
}


// TODO: currently mapper only handle the point part
void Mapper_Additor::map(Vec3f &vector) const {
	vector = vector + additor;
}


// multiplier
void Mapper_Multiplier::setMultiplier(const Vec3f &value) {
	this->multiplier = value;
}


// TODO: currently mapper only handle the point part
void Mapper_Multiplier::map(Vec3f &vector) const {
	vector = vector * multiplier;
}


// Static Function Implementation
// ...
