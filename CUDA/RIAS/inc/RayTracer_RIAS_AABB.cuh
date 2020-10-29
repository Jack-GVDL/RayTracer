// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/28   initial update


#ifndef RAYTRACER_RIAS_AABB_CUH
#define RAYTRACER_RIAS_AABB_CUH


#include "RayTracer_RIAS.cuh"
#include "RayTracer_Hitable_AABB.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class RIAS_AABB: public RIAS {
	// Data
	public:
		// ...

	// Operation
	public:
		// __init__
		__host__	RIAS_AABB	();
		__host__	~RIAS_AABB	();

		// interface
		__host__ virtual error_t	load	(SceneObject_Hitable* *hitable_list, int32_t size) override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_RIAS_AABB_CUH
