// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/28   initial update


#ifndef RAYTRACER_RIAS_OCTREE_CUH
#define RAYTRACER_RIAS_OCTREE_CUH


#include "RayTracer_RIAS.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
// TODO: not yet completed
class RIAS_Octree: public RIAS {
	// Data
	public:
		// ...

	// Operation
	public:
		// __init__
		__host__	RIAS_Octree		();
		__host__	~RIAS_Octree	();

		// interface
		__host__ virtual error_t	load	(SceneObject_Hitable* *hitable_list, int32_t size) override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_RIAS_OCTREE_CUH
