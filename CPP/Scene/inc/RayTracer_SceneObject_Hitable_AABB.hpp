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
	// Static Function
	public:
		static Hitable_AABB*	create	(SceneObject_Hitable* *list, int size_list, int size_leaf);

	// Data
	public:
		std::vector<SceneObject_Hitable*>	hitable_list;

	// Operation
	public:
		// init
		Hitable_AABB()
		{}

		// operation
		virtual bool	addHitable		(SceneObject_Hitable *hitable);
		virtual bool	rmHitable		(SceneObject_Hitable *hitable);
		virtual int		getHitableSize	() const;

		// interface
		virtual bool	hit				(RecordHit *record, double t_min, double t_max) const override;
};


// backup
// binary search tree strucutre
// class Hitable_AABBNode: public Hitable_AABB {
// 	// Static Function
// 	public:
// 		static Hitable_AABB*	create	(SceneObject_Hitable* *list, int size_list, int size_leaf, int size_node);
//
// 	// Data
// 	public:
// 		Hitable_AABB		*aabb_left;
// 		Hitable_AABB		*aabb_right;
// 		int					hitable_size	= 0;
//
// 	// Operation
// 	public:
// 		// init
// 		Hitable_AABBNode()
// 		{}
//
// 		~Hitable_AABBNode()
// 		{}
//
// 		// operation
// 		virtual bool	addHitable		(SceneObject_Hitable *hitable) override;
// 		virtual bool	rmHitable		(SceneObject_Hitable *hitable) override;
// 		virtual int		getHitableSize	() const override;
//
// 		// interface
// 		virtual bool	hit				(RecordHit *record, double t_min, double t_max) const override;
// };


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_AABB_HPP
