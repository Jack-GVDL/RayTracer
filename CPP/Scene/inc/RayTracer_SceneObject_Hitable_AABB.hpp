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
		// TODO: static -> member function
		static Hitable_AABB*	create	(SceneObject_Hitable* *list, int32_t size_list, int32_t size_leaf);

	// Data
	public:
		std::vector<SceneObject_Hitable*>	hitable_list;

	// Operation
	public:
		// init
		Hitable_AABB	();
		~Hitable_AABB	();

		// operation
		int8_t 			addHitable		(SceneObject_Hitable *hitable);
		int8_t			rmHitable		(SceneObject_Hitable *hitable);
		uint32_t		getHitableSize	() const;

		// interface
		virtual bool	hit				(RecordHit *record, fp_t t_min, fp_t t_max) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_AABB_HPP
