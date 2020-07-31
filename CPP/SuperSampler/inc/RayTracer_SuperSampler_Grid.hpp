// Created by Jack Tse on 2020/07/03
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/03   initial update


#ifndef RAYTRACER_SUPERSAMPLE_GRID_HPP
#define RAYTRACER_SUPERSAMPLE_GRID_HPP


#include "RayTracer_SuperSampler.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class SuperSampler_Grid: public SuperSampler {
	// Data
	public:
		int width	= 1;
		int	height	= 1;

	// Operation
	public:
		// init
		SuperSampler_Grid() {
			point_list.resize(width * height);
		}

		// operation
		void setGridSize(int w, int h);

		// interface
		virtual Vec3f	sample	(const Vec3f &point, const Vec3f &region, int depth, Vec3f(*get_color)(double x, double y, void *info), void *info);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SUPERSAMPLE_GRID_HPP
