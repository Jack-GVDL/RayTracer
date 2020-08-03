#include "../inc/RayTracer_Scatter_Emitter.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
ScatterState Scatter_Emitter::scatter_shootRay(RecordScatter *dst, RecordScatter *src, ScatterState state) const {
	dst->intensity = color;
	return SCATTER_YIELD;
}


// Static Function Implementation
// ...
