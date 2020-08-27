// Created by Jack Tse on 2020/08/12
//
// Log
// 2020/08/12   initial update


#ifndef RAYTRACER_TEXTURE_CONVOLUTOR_HPP
#define RAYTRACER_TEXTURE_CONVOLUTOR_HPP


#include "RayTracer_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Convolutor: public Texture {
	// Data
	public:
		Texture		*texture		= nullptr;

		fp_t		*kernel			= nullptr;
		int32_t		kernel_width	= 0;

	// Operation
	public:
		// init
		Texture_Convolutor()
		{
			input_size	= 1;
			input_list	= new Texture*[input_size];
			for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
		}

		// operation
		void			setTexture	(Texture *texture);
		void			setKernel	(fp_t *kernel, int32_t width);  // width and height should be the same

		// interace
		virtual void	setPixel	(const Vec3f &point, const Vec3f &pixel) override;
		virtual void	_getPixel_	(Vec3f &dst, Vec3f *src) const override;

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


#endif  // RAYTRACER_TEXTURE_CONVOLUTOR_HPP
