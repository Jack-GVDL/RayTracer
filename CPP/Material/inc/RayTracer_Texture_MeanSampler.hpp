// Created by Jack Tse on 2020/08/12
//
// Log
// 2020/08/12   initial update


#ifndef RAYTRACER_TEXTURE_MEANSAMPLER_HPP
#define RAYTRACER_TEXTURE_MEANSAMPLER_HPP


#include "RayTracer_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_MeanSampler: public Texture {
	// Data
	public:
		Texture		*texture	= nullptr;

	// Operation
	public:
		// init
		// ...

		// operation
		void			setTexture	(Texture *texture);

		// interace
		virtual void	setPixel	(const Vec3f &point, const Vec3f &pixel) override;

	protected:
		virtual Vec3f	_getPixel_	(const Ray *ray) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_MEANSAMPLER_HPP
