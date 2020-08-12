// Created by Jack Tse on 2020/08/12
//
// Log
// 2020/08/12   initial update


#ifndef RAYTRACER_TEXTURE_CHAIN_HPP
#define RAYTRACER_TEXTURE_CHAIN_HPP


#include <vector>
#include "RayTracer_Texture.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture_Chain: public Texture {
	// Data
	public:
		std::vector<Texture*>	texture_list;

	// Operation
	public:
		// init
		// ...

		// operation
		bool			addTexture	(Texture *texture);
		bool			rmTexture	(Texture *texture);

		// interface
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


#endif  // RAYTRACER_TEXTURE_CHAIN_HPP
