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
		Vec3f	*color	= nullptr;
		int		width	= 0;
		int		height	= 0;

	// Operation
	public:
		// init
		Texture_Image()
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
		// backu
		// virtual void	_getPixel_	(Vec3f &dst, const Vec3f &src) const override;
};


// TODO: change to this name later
typedef Texture_Image Texture_PixelMap;


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_IMAGE_HPP
