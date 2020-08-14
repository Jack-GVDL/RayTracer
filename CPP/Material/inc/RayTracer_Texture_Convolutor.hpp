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

		double		*kernel			= nullptr;
		int			kernel_width	= 0;

	// Operation
	public:
		// init
		// ...

		// operation
		void			setTexture	(Texture *texture);
		void			setKernel	(double *kernel, int width);  // width and height should be the same

		// interace
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


#endif  // RAYTRACER_TEXTURE_CONVOLUTOR_HPP
