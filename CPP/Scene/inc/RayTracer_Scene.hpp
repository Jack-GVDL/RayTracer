// Created by Jack Tse on 2020/06/24
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/24   initial update


#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP


#include "RayTracer_SceneElement.hpp"
#include "RayTracer_SceneObject_Hitable.hpp"
#include "RayTracer_SceneObject_Light.hpp"


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
		std::vector<SceneObject_Hitable*>	hitable_list;
		std::vector<SceneObject_Light*>		light_list;
		std::vector<SceneObject_Light*>		ambient_list;

	// Operation
	public:
		// operation
		bool	addHitable			(SceneObject_Hitable *hitable);
		bool	rmHitable			(SceneObject_Hitable *hitable);
		bool	addLight			(SceneObject_Light *light);
		bool	rmLight				(SceneObject_Light *light);
		bool	addAmbientLight		(SceneObject_Light *light);
		bool	rmAmbientLight		(SceneObject_Light *light);

		Vec3f	getAmbientIntensity	() const;

		bool	hit					(RecordHit_Extend *hit) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENE_HPP
