// Created by Jack Tse on 2020/06/25
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/25   initial update
// 2020/07/20   change include path
// 2020/07/26   add External.hpp


#ifndef RAYTRACER_TRACER_HPP
#define RAYTRACER_TRACER_HPP


#include "../../Utility/Utility.hpp"
#include "../../Scatter/Scatter.hpp"
#include "../../Shader/Shader.hpp"
#include "../../Scene/Scene.hpp"


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
		Scene	*scene			= nullptr;

		Shader	shader_not_hit;
		Shader	shader_hit;

	// Operation
	public:
		// init
		RayTracer():
		scene			(nullptr)
		{}

		RayTracer(Scene *scene):
		scene			(scene)
		{}
		
		// operation
		Vec3f	trace	(const Camera *camera, double x, double y, int depth) const;
		Vec3f	trace	(const Ray *ray, int depth) const;
		Vec3f	trace	(RecordScatter *record) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TRACER_HPP