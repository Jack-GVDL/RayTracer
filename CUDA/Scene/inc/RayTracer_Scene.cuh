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
		// TODO: may be use struct to make thing easier
		SceneObject_Hitable*		*hitable_list	= nullptr;
		int32_t						hitable_size	= 0;
		int32_t						hitable_index	= 0;

		SceneObject_Light*			*light_list		= nullptr;
		int32_t						light_size		= 0;
		int32_t						light_index		= 0;

		SceneObject_Light*			*ambient_list	= nullptr;
		int32_t						ambient_size	= 0;
		int32_t						ambient_index	= 0;

	// Operation
	public:
		// init
		__device__	Scene	();
		__device__	~Scene	();

		// operation
		__device__ error_t	allocateHitable		(int32_t size);
		__device__ error_t	addHitable			(SceneObject_Hitable *hitable);
		__device__ error_t	rmHitable			(SceneObject_Hitable *hitable);

		__device__ error_t	allocateLight		(int32_t size);
		__device__ error_t	addLight			(SceneObject_Light *light);
		__device__ error_t	rmLight				(SceneObject_Light *light);

		__device__ error_t	allocateAmbient		(int32_t size);
		__device__ error_t	addAmbient			(SceneObject_Light *light);
		__device__ error_t	rmAmbient			(SceneObject_Light *light);

		__device__ Vec3f	getAmbientIntensity	() const;
		__device__ int8_t	hit					(RecordHit_Extend *hit) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENE_CUH
