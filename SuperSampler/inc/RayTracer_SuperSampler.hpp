// Created by Jack Tse on 2020/07/03
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/03   initial update


#ifndef RAYTRACER_SUPERSAMPLER_HPP
#define RAYTRACER_SUPERSAMPLER_HPP


#include <vector>
#include "../../Utility/Utility.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class SuperSampler {
	// Data
	public:
		std::vector<Vec3f>	point_list;

	// Operation
	public:
		// operation
		virtual Vec3f	sample	(const Vec3f &point, const Vec3f &region, int depth, Vec3f(*get_color)(double x, double y, void *info), void *info) = 0;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SUPERSAMPLER_HPP
