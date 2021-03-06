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
		// init
		Texture_Math_Additor()
		{
			input_size	= 1;
			input_list	= new Texture*[input_size];
			for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
		}

		// operation
		void			setAdditor      (const Vec3f &value);

		// interface
		virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// ...
};


class Texture_Math_Multiplier: public Texture {
	// Data
	public:
		Vec3f	multiplier	= Vec3f(1);

	// Operation
	public:
		// init
		Texture_Math_Multiplier()
		{
			input_size	= 1;
			input_list	= new Texture*[input_size];
			for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
		}

		// operation
		void			setMultiplier	(const Vec3f &value);

		// interface
		virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// ...
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_MATH_HPP
