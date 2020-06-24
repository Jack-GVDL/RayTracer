// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update


#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP


#include <vector>
#include "RayTracer_SceneObject_Hitable.hpp"
// #include "RayTracer_SceneObject_Light.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Scene {
	// Data
	public:
		SceneObject_HitableList					hitable_list;
		// std::vector<SceneObject_Light*>		light_list;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENE_HPP
