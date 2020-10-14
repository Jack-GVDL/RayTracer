// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/06/21   initial update
// 2020/09/12   remove Shader


#ifndef RAYTRACER_SCENEOBJECT_HITABLE_HPP
#define RAYTRACER_SCENEOBJECT_HITABLE_HPP


#include "RayTracer_SceneElement.hpp"


// Define
// ...


// Typedef
// ...


// Macro Function
// ...


// Enum
// ...


// Data Structure
class SceneObject_Hitable;


struct RecordHit {
	// incident ray
	Ray						ray;

	// object intersected
	SceneObject_Hitable		*object;

	// info on the point of intersection
	Vec3f					normal;
	Vec3f					point;  // remove this when need to reduce size of struct
	fp_t					distance;
};


struct RecordHit_Extend {
	RecordHit				record;
	fp_t					length_min		= RAY_EPSILON;
	fp_t					length_max		= std::numeric_limits<fp_t>::max();
};


class SceneObject_Hitable: public SceneElement {
	// Data
	public:
		Material	*material;

	// Operation
	public:
		// init
		SceneObject_Hitable		();
		~SceneObject_Hitable	();
		
		// operation
		void			setMaterial	(Material *material);
		
		int8_t			hit			(RecordHit *record) const;
		int8_t			hit			(RecordHit *record, fp_t t_max) const;

		// interface
		virtual int8_t	hit			(RecordHit *record, fp_t t_min, fp_t t_max) const = 0;
};


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_HPP
