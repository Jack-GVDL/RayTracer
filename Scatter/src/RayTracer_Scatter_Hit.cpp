#include "../inc/RayTracer_Scatter_Hit.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
ScatterState Scatter_Hit::_scatter_(ScatterRecord *dst, ScatterRecord *src) const {
	if (!src->is_hit)	dst->intensity = Vec3f(0, 0, 0);
	else				dst->intensity = color;
	return SCATTER_YIELD;
}


// Static Function Implementation
// ...
