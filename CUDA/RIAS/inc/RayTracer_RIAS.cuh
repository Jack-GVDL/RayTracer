// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/28   initial update


#ifndef RAYTRACER_RIAS_CUH
#define RAYTRACER_RIAS_CUH


#include "../../Scene/Scene.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class RIAS {
	// Data
	public:
		// TODO: not yet decided
		SceneObject_Hitable	*hitable	= nullptr;
	
	// Operation
	public:
		// __init__
		__host__ 	RIAS	();
		__host__	~RIAS	();

		// interface
		__host__ virtual error_t	load	(SceneObject_Hitable* *hitable_list, int32_t size) = 0;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_RIAS_CUH
