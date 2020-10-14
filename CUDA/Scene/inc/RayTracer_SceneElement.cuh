// Author: Jack Tse
// Email: jacktsetcy@gmail.com
//
// Log
// 2020/09/12   initial update


#ifndef RAYTRACER_SCENEELEMENT_HPP
#define RAYTRACER_SCENEELEMENT_HPP


#include "../../Utility/Utility.cuh"
#include "../../Material/Material.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class SceneElement {
	// Data
	public:
		Vec3f						origin		= Vec3f(0);
		Bounding					bounding;

	// Operation
	public:
		// init
		__device__	SceneElement	();
		__device__	~SceneElement	();

		// operation
		__device__ void				setOrigin		(const Vec3f &origin);
		__device__ void				setBounding		(const Bounding &bounding);

		// interface
		// backup
		/*
		__device__ virtual error_t	addChild		(SceneElement *scene);
		__device__ virtual error_t	rmChild			(SceneElement *scene);
		*/
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENE_HPP
