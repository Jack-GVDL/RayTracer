// Created by Jack Tse on 2020/07/24
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/24   initial update


#ifndef RAYTRACER_TEXTURE_CHECKERBOARD_HPP
#define RAYTRACER_TEXTURE_CHECKERBOARD_HPP


#include "RayTracer_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_CheckerBoard: public Texture {
	// Data
	public:
		Vec3f size_board;  // size of a board/box in length/width/height
	
	// Operation
	public:
		// init
		Texture_CheckerBoard()
		{}

		// operation
		void			setBoardSize	(const Vec3f &size);

		// interface
		virtual void	setPixel	(const Vec3f &point, const Vec3f &pixel) override;

	protected:
		// interface
		virtual Vec3f	_getPixel_	(const Ray *ray) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_CHECKERBOARD_HPP
