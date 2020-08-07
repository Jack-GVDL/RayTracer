// Created by Jack Tse on 2020/08/07
//
// Log
// 2020/08/07   initial update


#ifndef RAYTRACER_SCENEOBJECT_HITABLE_AABB_HPP
#define RAYTRACER_SCENEOBJECT_HITABLE_AABB_HPP


#include "RayTracer_SceneObject_Hitable.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Hitable_AABB: public SceneObject_Hitable {
	// Data
	public:
		std::vector<SceneObject_Hitable*>	hitable_list;

	// Operation
	public:
		// init
		Hitable_AABB();

		// operation
		bool			addHitable		(SceneObject_Hitable *hitable);
		bool			rmHitable		(SceneObject_Hitable *hitable);

		// interface
		virtual bool	hit				(RecordHit *record, double t_min, double t_max) const override;
};


// binary search tree strucutre
class Hitable_AABBNode: public SceneObject_Hitable {
	// Data
	public:
		Hitable_AABB		*aabb_left;
		Hitable_AABB		*aabb_right;

	// Operation
	public:
		// init
		Hitable_AABBNode()
		{}

		// operation
		void			setAABB_left	(Hitable_AABB *aabb);
		void			setAABB_right	(Hitable_AABB *aabb);

		// interface
		virtual bool	hit				(RecordHit *record, double t_min, double t_max) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_AABB_HPP
