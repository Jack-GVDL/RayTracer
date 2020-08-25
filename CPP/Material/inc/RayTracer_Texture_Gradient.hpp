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
		Texture_Gradient()
		{
			input_size	= 1;
			input_list	= new Texture*[input_size];
			for (int i = 0; i < input_size; i++) input_list[i] = nullptr;
		}

		// interface
		virtual void	setPixel	(const Vec3f &point, const Vec3f &pixel) override;
		virtual void	_getPixel_	(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// backup
		// virtual void	_getPixel_	(Vec3f &dst, const Vec3f &src) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_GRADIENT_HPP
