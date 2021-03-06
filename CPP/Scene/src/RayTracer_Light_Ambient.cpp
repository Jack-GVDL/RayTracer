#include "../inc/RayTracer_Light_Ambient.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
fp_t Light_Ambient::getAttenuation(const Vec3f &point) const {
	return 1.0;
}


fp_t Light_Ambient::getDistance(const Vec3f &point) const {
	return std::numeric_limits<fp_t>::max();
}


Vec3f Light_Ambient::getColor(const Vec3f &point) const {
	return color;
}


Vec3f Light_Ambient::getDirection(const Vec3f &point) const {
	return Vec3f(0);
}


// Static Function Implementation
// ...
