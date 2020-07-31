#include "../inc/RayTracer_SuperSampler_Random.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
void SuperSampler_Random::setGridSize(int w, int h) {
	width	= w;
	height	= h;
	point_list.resize(w * h);
}


Vec3f SuperSampler_Random::sample(const Vec3f &point, const Vec3f &region, int depth, Vec3f(*get_color)(double x, double y, void *info), void *info) {
	// get point list
	const double 	w_half		= region[0];
	const double 	h_half		= region[1];

	for (int i = 0; i < int(point_list.size()); i++) {
		const double random_w	= (UtilMath::randDouble() * 2 - 1) * w_half;
		const double random_h	= (UtilMath::randDouble() * 2 - 1) * h_half;
		point_list[i] = Vec3f(random_w, random_h, 0);
	}

	// get color
	Vec3f 		result	= Vec3f();
	const int	n		= int(point_list.size());

	for (int i = 0; i < n; i++) {
		const double x = point[0] + point_list[i][0];
		const double y = point[1] + point_list[i][1];
		result += get_color(x, y, info);
	}

	return (result / n);
}


// Static Function Implementation
// ...
