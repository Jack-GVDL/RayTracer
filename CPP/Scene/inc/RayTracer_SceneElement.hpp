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

// backup
// struct Vertex {
// 	Vec3f point;
// };


// struct Edge {
// 	Vertex	vertex_1;
// 	Vertex	vertex_2;
// };


// struct Plane {
// 	Vertex	*vertices;
// 	int		size_vertices;
// };


class SceneElement {
	// Data
	public:
		Vec3f						origin			= Vec3f(0);
		Vec3f						bounding_min	= Vec3f(0);
		Vec3f						bounding_max	= Vec3f(0);

		std::vector<SceneElement*>	child;

	// Operation
	public:
		// init
		SceneElement()
		{}

		// operation
		void		setOrigin		(const Vec3f &origin);
		void		setBounding_min	(const Vec3f &bounding);
		void		setBounding_max	(const Vec3f &bounding);

		// interface
		virtual bool addChild		(SceneElement *scene);
		virtual bool rmChild		(SceneElement *scene);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENE_HPP
