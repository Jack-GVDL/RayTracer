// Created by Jack Tse on 2020/08/17
//
// Log
// 2020/08/17   initial update


#ifndef RAYTRACER_TEXTURE_INPUT_HPP
#define RAYTRACER_TEXTURE_INPUT_HPP


#include "RayTracer_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Input: public Texture {
	// Data
	public:
		// ...

	// Operation
	public:	
		// init
		Texture_Input()
		{
			input_size	= 0;
			input_list	= nullptr;
			for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
		}

		// operation
		// ...

		// interface
		virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_INPUT_HPP
