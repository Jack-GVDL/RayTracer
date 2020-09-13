// Created by Jack Tse on 2020/06/24
//
// Log
// 2020/09/12   initial update


#ifndef RAYTRACER_SCENE_CUH
#define RAYTRACER_SCENE_CUH


#include "RayTracer_SceneElement.cuh"
#include "RayTracer_SceneObject_Hitable.cuh"
#include "RayTracer_SceneObject_Light.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scene: public SceneElement {
	// Data
	public:
		// TODO: need to change this
		std::vector<SceneObject_Hitable*>	hitable_list;
		std::vector<SceneObject_Light*>		light_list;
		std::vector<SceneObject_Light*>		ambient_list;

	// Operation
	public:
		// operation
		__device__ error_t	addHitable			(SceneObject_Hitable *hitable);
		__device__ error_t	rmHitable			(SceneObject_Hitable *hitable);
		__device__ error_t	addLight			(SceneObject_Light *light);
		__device__ error_t	rmLight				(SceneObject_Light *light);
		__device__ error_t	addAmbientLight		(SceneObject_Light *light);
		__device__ error_t	rmAmbientLight		(SceneObject_Light *light);

		__device__ Vec3f	getAmbientIntensity	() const;
		__device__ error_t	hit					(RecordHit_Extend *hit) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENE_CUH
