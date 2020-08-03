// Created by Jack Tse on 2020/07/26
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/26   initial update


#ifndef RAYTRACER_GRADIENT_HPP
#define RAYTRACER_GRADIENT_HPP


#include "RayTracer_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Gradient: public Texture {
	// Enum
	public:
		enum GradientSource {
			EMPTY,
			DIRECTION,
			POSITION,
			CUSTOM,
			SOURCE_MAX
		};

	// Data
	public:
		Vec3f			additor		= Vec3f(1);
		Vec3f			multiplier	= Vec3f(1);
		GradientSource	source		= POSITION;

	// Operation
	public:
		// init
		// ...

		// interface
		virtual void	setPixel	(const Vec3f &point, const Vec3f &pixel) override;

	protected:
		// interface
		virtual Vec3f	_getPixel_	(const Ray *ray) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_GRADIENT_HPP
