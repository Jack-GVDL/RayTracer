// Created by Jack Tse on 2020/07/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/20   initial update


#ifndef RAYTRACER_TEXTURE_HPP
#define RAYTRACER_TEXTURE_HPP


#include <stdint.h>
#include "../../Utility/Utility.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture {
	// Operation
	public:
		virtual Vec3f	getPixel	(const Vec3f &point) const = 0;
		virtual void	setPixel	(const Vec3f &point, const Vec3f &pixel) = 0;
};


class Texture_Constant: public Texture {
	// Data
	public:
		Vec3f   color   = Vec3f();

	// Operation
	public:
		// init
		Texture_Constant()
		{}

		Texture_Constant(const Vec3f &color):
		color(color)
		{}

		// operation
		virtual Vec3f	getPixel	(const Vec3f &point) const override;
		virtual void	setPixel	(const Vec3f &point, const Vec3f &pixel) override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_HPP
