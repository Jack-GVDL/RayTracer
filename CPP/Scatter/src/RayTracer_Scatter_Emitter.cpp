#include "../inc/RayTracer_Scatter_Emitter.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
void Scatter_Emitter::scatter(RecordRay *src, MemoryControl_Scatter *memory_control) const {
	src->intensity = (src->threshold * color);
	src->threshold = Vec3f(0);
}


// Static Function Implementation
// ...
