// Created by Jack Tse on 2020/08/14
//
// Log
// 2020/08/14   initial update


#ifndef RAYTRACER_TEXTURE_CONSTANT_HPP
#define RAYTRACER_TEXTURE_CONSTANT_HPP


#include "RayTracer_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
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

		// interface
		virtual void	setPixel	(const Vec3f &point, const Vec3f &pixel) override;

	protected:
		// interface
		virtual void	_getPixel_	(Vec3f &dst, const Vec3f &src) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_CONSTANT_HPP
