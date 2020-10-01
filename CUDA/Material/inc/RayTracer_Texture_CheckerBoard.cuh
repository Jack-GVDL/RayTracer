// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/01   initial update


#ifndef RAYTRACER_TEXTURE_CHECKERBOARD_CUH
#define RAYTRACER_TEXTURE_CHECKERBOARD_CUH


#include "RayTracer_Texture.cuh"


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
		Vec3f	size_board;  // size of a board/box in length/width/height
		Vec3f	color_1	= Vec3f(0);
		Vec3f	color_2	= Vec3f(1);
	
	// Operation
	public:
		// init
		__device__	Texture_CheckerBoard();
		__device__	~Texture_CheckerBoard();

		// operation
		__device__ void				setBoardSize	(const Vec3f &size);
		__device__ void				setBoardColor	(const Vec3f &color_1, const Vec3f &color_2);

		// interface
		__device__ virtual void		setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		__device__ virtual void		_getPixel_		(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// backup
		// virtual void	_getPixel_		(Vec3f &dst, const Vec3f &src) const override;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TEXTURE_CHECKERBOARD_CUH
