#include "../inc/RayTracer_SuperSampler_Jittered.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
void SuperSampler_Jittered::setGridSize(int w, int h) {
	width	= w;
	height	= h;
	point_list.resize(w * h);
}


Vec3f SuperSampler_Jittered::sample(const Vec3f &point, const Vec3f &region, int depth, Vec3f(*get_color)(double x, double y, void *info), void *info) {
	// get point list
	const double 	w_half		= region[0];
	const double 	h_half		= region[1];
	const double 	w_pixel		= w_half * 2 / (width - 1);
	const double 	h_pixel		= h_half * 2 / (height - 1);

	int index = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {

			const double random_w	= (drand48() * 2 - 1) * w_pixel;
			const double random_h	= (drand48() * 2 - 1) * h_pixel;
			
			point_list[index] = Vec3f(
				-w_half + x * w_pixel + random_w,  
				-h_half + y * h_pixel + random_h, 
				0);
			index++;

		}
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
