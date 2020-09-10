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
		// std::vector<Mapper*>	mapper_list;
		Texture*				*input_list		= nullptr;
		int32_t					input_size		= 0;

	// Operation
	public:
		// init
		~Texture()
		{
			delete[] input_list;
		}

		// operation
		bool			addInput	(Texture *texture, int32_t index);
		bool			rmInput		(int32_t index);

		void			getPixel	(Vec3f &dst, const Vec3f &src) const;

		// interface
		virtual void	setPixel	(const Vec3f &point, const Vec3f &pixel) = 0;
		virtual void	_getPixel_	(Vec3f &dst, Vec3f *src) const = 0;

	protected:
		// interface
		// ...
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_HPP
