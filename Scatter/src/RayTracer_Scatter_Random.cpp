#include "../inc/RayTracer_Scatter_Random.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
ScatterState Scatter_RandomGrid::scatter_shootRay(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const {
	Vec3f ref_dir = src->ray.getDirection();
	// ref_dir.normalize();  // trust operation, ray.getDirection will return a normalized vector

	// get the radius vector
	Vec3f vector_radius_1, vector_radius_2;
	
	// special case: ray vector is along with x-direction
	if (ref_dir.dot(Vec3f(1, 0, 0)) == 1) {
		vector_radius_1 = Vec3f(0, 1, 0);
		vector_radius_2 = Vec3f(0, 0, 1);

	} else {
		vector_radius_1 = ref_dir.cross(Vec3f(1, 0, 0));
		vector_radius_2 = ref_dir.cross(vector_radius_1);

		vector_radius_1.normalize();
		vector_radius_2.normalize();
	}

	// set the length of the radius vectors	
	const double length_1 = radius * (UtilMath::randDouble() - 0.5) * 2;
	const double length_2 = radius * (UtilMath::randDouble() - 0.5) * 2;

	vector_radius_1 = vector_radius_1.prod(Vec3f(length_1));
	vector_radius_2 = vector_radius_2.prod(Vec3f(length_2));
	
	// configure ray position and direction
	// if new ray is parallel, then move the ray position
	// if new ray is not paralle, then move the ray direction
	Vec3f new_pos = src->ray.getPosition();
	Vec3f new_dir = ref_dir;
	if (is_parallel)	new_pos += vector_radius_1 + vector_radius_2;
	if (!is_parallel)	new_dir += vector_radius_1 + vector_radius_2;

	// create new ray
	dst->ray = Ray(new_pos, new_dir.normalize());

	// split the threshold of src
	// TODO: currently this number is static and cannot be changed
	const double	split_ratio			= 1.0 / double(loop_count); 
	const Vec3f		&threshold_child	= src->thresh.prod(Vec3f(split_ratio));
	dst->thresh							= threshold_child;
	// src->thresh = src->thresh - threshold_child;
	
	return SCATTER_EQUAL_SPLIT;
}


// Static Function Implementation
// ...
