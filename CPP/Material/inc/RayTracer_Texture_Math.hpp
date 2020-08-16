// Created by Jack Tse on 2020/08/14
//
// Log
// 2020/08/14   initial update


#ifndef RAYTRACER_TEXTURE_MATH_HPP
#define RAYTRACER_TEXTURE_MATH_HPP


#include "RayTracer_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Math_Additor: public Texture {
	// Data
	public:
		Vec3f	additor		= Vec3f(0);

	// Operation
	public:
		// operation
		void			setAdditor      (const Vec3f &value);

		// interface
		virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;

	protected:
		// interface
		virtual void	_getPixel_		(Vec3f &dst, const Vec3f &src) const override;
};


class Texture_Math_Multiplier: public Texture {
	// Data
	public:
		Vec3f	multiplier	= Vec3f(1);

	// Operation
	public:
		// operation
		void			setMultiplier	(const Vec3f &value);

		// interface
		virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;

	protected:
		// interface
		virtual void	_getPixel_		(Vec3f &dst, const Vec3f &src) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_MATH_HPP