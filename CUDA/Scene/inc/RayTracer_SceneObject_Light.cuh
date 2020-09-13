// Author: Jack Tse
// Email: jacktsetcy@gmail.com
//
// Log
// 2020/09/12   initial update


#ifndef RAYTRACER_SCENEOBJECT_LIGHT_CUH
#define RAYTRACER_SCENEOBJECT_LIGHT_CUH


#include "RayTracer_SceneElement.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class SceneObject_Light: public SceneElement {
	// Data
	public:
		Vec3f	color;
		
	// Operation
	public:
		// init
		// ...

		// operation
		__device__ void			    setColor				(const Vec3f &color);
	
		// interface
		__device__ virtual fp_t     getAttenuation			(const Vec3f &point) const	= 0;
		__device__ virtual fp_t     getDistance				(const Vec3f &point) const	= 0;
		__device__ virtual Vec3f	getColor				(const Vec3f &point) const	= 0;
		__device__ virtual Vec3f	getDirection			(const Vec3f &point) const	= 0;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_LIGHT_CUH
