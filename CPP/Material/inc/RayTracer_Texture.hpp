// Created by Jack Tse on 2020/07/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/20   initial update
// 2020/07/26   add mapper_list


#ifndef RAYTRACER_TEXTURE_HPP
#define RAYTRACER_TEXTURE_HPP


#include <stdint.h>
#include <vector>
#include "../../Utility/Utility.hpp"
#include "RayTracer_Mapper.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Texture {
	// Data
	public:
		// better to call it mapper_chain
		// as order matter
		std::vector<Mapper*> mapper_list;

	// Operation
	public:
		// operation
		bool			addMapper	(Mapper *mapper);
		bool			rmMapper	(Mapper *mapper);
		void			getPixel	(Vec3f &dst, const Vec3f &src) const;

		// interface
		virtual void	setPixel	(const Vec3f &point, const Vec3f &pixel) = 0;

	protected:
		// interface
		// TODO: change to getPixel for consistency
		virtual void	_getPixel_	(Vec3f &dst, const Vec3f &src) const = 0;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_HPP
