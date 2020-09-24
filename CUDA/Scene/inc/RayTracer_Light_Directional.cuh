// Author: Jack Tse
// Email: jacktsetcy@gmail.com
//
// Log
// 2020/09/12   initial update


#ifndef RAYTRACER_LIGHT_DIRECTIONAL_CUH
#define RAYTRACER_LIGHT_DIRECTIONAL_CUH


#include "RayTracer_SceneObject_Light.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Light_Directional: public SceneObject_Light {
	// Data
	public:
		Vec3f	orientation		= Vec3f(0, 0, -1);

	// Operation
	public:
		// init
		__device__	Light_Directional	();
		__device__	~Light_Directional	();

		// operation
		__device__ void				setOrientation			(const Vec3f &orientation);

		// interface
		__device__ virtual fp_t		getAttenuation			(const Vec3f &point) const override;
		__device__ virtual fp_t		getDistance				(const Vec3f &point) const override;
		__device__ virtual Vec3f	getColor				(const Vec3f &point) const override;
		__device__ virtual Vec3f	getDirection			(const Vec3f &point) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_LIGHT_DIRECTIONAL_CUH
