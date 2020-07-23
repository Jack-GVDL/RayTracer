#include <algorithm>
#include "../inc/RayTracer_Scatter_Hit.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
ScatterState Scatter_Hit::scatter_shootRay(RecordScatter *dst, RecordScatter *src, ScatterState state) const {
	if (!src->is_hit) {
		dst->intensity = Vec3f(0);
		return SCATTER_YIELD;
	}

	// get ray direction
	const Vec3f &ray_dir = src->record_hit.ray.getDirection();
	
	// before multiplication
	// the value of ray_dir is adjusted to range [0, 1]
	const double intensity_0 = ((ray_dir[0] + 1) / 2) * multiplier[0];
	const double intensity_1 = ((ray_dir[1] + 1) / 2) * multiplier[1];
	const double intensity_2 = ((ray_dir[2] + 1) / 2) * multiplier[2];

	// need clamping
	dst->intensity[0] = UtilMath::clamp<double>(intensity_0, 0.0, 1.0);
	dst->intensity[1] = UtilMath::clamp<double>(intensity_1, 0.0, 1.0);
	dst->intensity[2] = UtilMath::clamp<double>(intensity_2, 0.0, 1.0);

	return SCATTER_YIELD;
}


// Static Function Implementation
// ...
