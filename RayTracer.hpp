// Created by Jack Tse on 2020/06/25
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/25   initial update


#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP


#include "./Scatter/Scatter.hpp"
#include "./Scene/Scene.hpp"
#include "./Utility/Utility.hpp"
#include "./SuperSampler/SuperSampler.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class RayTracer {
	// Data
	public:
		Scene	*scene;
		Scatter	*scatter;

	// Operation
	public:
		// init
		RayTracer():
		scene(nullptr),
		scatter(nullptr)
		{}

		RayTracer(Scene *scene, Scatter *scatter):
		scene(scene),
		scatter(scatter)
		{}
		
		// operation
		Vec3f	trace	(const Camera *camera, double x, double y, int depth) const;
		Vec3f	trace	(const Ray *ray, int depth) const;
		Vec3f	trace	(ScatterRecord *record) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_HPP
