#include "../inc/RayTracer_Scatter_Hit.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
ScatterState Scatter_Hit::scatter_shootRay(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const {
	if (!src->is_hit)	dst->intensity = Vec3f(0, 0, 0);
	else				dst->intensity = color;
	return SCATTER_YIELD;
}


// Static Function Implementation
// ...
