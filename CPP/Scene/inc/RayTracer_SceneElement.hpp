// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update


#ifndef RAYTRACER_SCENEELEMENT_HPP
#define RAYTRACER_SCENEELEMENT_HPP


#include <vector>
#include "../../Utility/Utility.hpp"
#include "../../Material/Material.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class SceneElement {
	// Data
	public:
		Vec3f						origin			= Vec3f(0);
		Bounding					bounding;

		std::vector<SceneElement*>	child;

	// Operation
	public:
		// init
		SceneElement()
		{}

		// operation
		void			setOrigin		(const Vec3f &origin);
		void			setBounding		(const Bounding &bounding);

		// interface
		virtual error_t addChild		(SceneElement *scene);
		virtual error_t rmChild			(SceneElement *scene);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENE_HPP
