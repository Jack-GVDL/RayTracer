// Created by Jack Tse on 2020/07/26
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/26   initial update


#ifndef RAYTRACER_MAPPER_MATH_HPP
#define RAYTRACER_MAPPER_MATH_HPP


#include "RayTracer_Mapper.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Mapper_Additor: public Mapper {
	// Data
	public:
		Vec3f	additor	= Vec3f(0);

	// Operation
	public:
		virtual void	map (Vec3f &vector) const override;
};


class Mapper_Multiplier: public Mapper {
	// Data
	public:
		Vec3f	multiplier	= Vec3f(1);

	// Operation
	public:
		virtual void	map	(Vec3f &vector) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_MAPPER_MATH_HPP
