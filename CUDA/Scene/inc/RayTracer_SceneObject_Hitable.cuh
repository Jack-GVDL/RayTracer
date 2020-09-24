// Author: Jack Tse
// Email: jacktsetcy@gmail.com
//
// Log
// 2020/09/12   initial update


#ifndef RAYTRACER_SCENEOBJECT_HITABLE_CUH
#define RAYTRACER_SCENEOBJECT_HITABLE_CUH


#include "RayTracer_SceneElement.cuh"


// Define
// ...


// Typedef
// ...


// Macro Function
// ...


// Enum
// ...


// Data Structure
class SceneObject_Hitable;


struct RecordHit {
	// incident ray
	Ray						ray;

	// object intersected
	SceneObject_Hitable		*object;

	// info on the point of intersection
	Vec3f					normal;
	Vec3f					point;  // remove this when need to reduce size of struct
	fp_t					distance;
};


struct RecordHit_Extend {
	RecordHit				record;
	fp_t					length_min		= RAY_EPSILON;
	fp_t					length_max		= FLOAT_MAX;
};


class SceneObject_Hitable: public SceneElement {
	// Data
	public:
		Material	*material	= nullptr;

	// Operation
	public:
		// init
		__device__	SceneObject_Hitable		();
		__device__	~SceneObject_Hitable	();
		
		// operation
		__device__ void				setMaterial				(Material *material);
		
		__device__ int8_t			hit						(RecordHit *record) const;
		__device__ int8_t			hit						(RecordHit *record, fp_t t_max) const;

		// interface
		__device__ virtual int8_t	hit						(RecordHit *record, fp_t t_min, fp_t t_max) const = 0;
};


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_CUH
