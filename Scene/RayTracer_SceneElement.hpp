// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update


#ifndef RAYTRACER_SCENEELEMENT_HPP
#define RAYTRACER_SCENEELEMENT_HPP


#include <vector>
#include "RayTracer_Ray.hpp"
#include "RayTracer_Material.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
struct Vertex {
	Vec3f point;
};


struct Edge {
	Vertex	vertex_1;
	Vertex	vertex_2;
};


struct Plane {
	Vertex	*vertices;
	int		size_vertices;
};


class SceneElement {
	// Data
	public:
		Vec3f						origin;
		std::vector<SceneElement*>	child;

	// Operation
	public:
		// init
		SceneElement():
		origin		(Vec3f())
		{}

		// operation
		virtual bool addChild(SceneElement *scene) {
			child.push_back(scene);
			return true;
		}

		// TODO: not yet completed
		virtual bool rmChild(SceneElement *scene) {
		}
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENE_HPP
