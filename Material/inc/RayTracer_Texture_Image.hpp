// Created by Jack Tse on 2020/07/24
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/24   initial update


#ifndef RAYTRACER_TEXTURE_IMAGE_HPP
#define RAYTRACER_TEXTURE_IMAGE_HPP


#include "RayTracer_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Image: public Texture {
	// Data
	public:
		Vec3f	*color;
		int		width, height;

	// Operation
	public:
		// init
		Texture_Image()
		{}

		// interface
		virtual	Vec3f	getPixel	(const Vec3f &point) const override;
		virtual	void	setPixel	(const Vec3f &point, const Vec3f &pixel) override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_IMAGE_HPP
