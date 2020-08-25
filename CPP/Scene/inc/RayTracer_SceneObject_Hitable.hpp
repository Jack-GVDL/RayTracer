// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update


#ifndef RAYTRACER_SCENEOBJECT_HITABLE_HPP
#define RAYTRACER_SCENEOBJECT_HITABLE_HPP


#include "RayTracer_SceneElement.hpp"
#include "../../Shader/Shader.hpp"


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
class Shader;


struct RecordHit {
	// incident ray
	Ray						ray;

	// object intersected
	SceneObject_Hitable		*object;

	// info on the point of intersection
	Vec3f					normal;
	Vec3f					point;
	double					distance;
};


class SceneObject_Hitable: public SceneElement {
	// Data
	public:
		// TODO: but the problem is that not all the hitable need the material
		Material	material;
		Shader		shader;

	// Operation
	public:
		// init
		SceneObject_Hitable()
		{}

		// TODO: backup
		// SceneObject_Hitable(Material *material):
		// material(*material)
		// {}
		
		// operation
		bool			hit		(RecordHit *record) const;
		bool			hit		(RecordHit *record, double t_max) const;

		// interface
		virtual bool	hit		(RecordHit *record, double t_min, double t_max) const = 0;
};


class SceneObject_HitableList: public SceneObject_Hitable {
	// Data
	public:
		std::vector<SceneObject_Hitable*>	hitable_list;

	// Operation
	public:
		// operation
		virtual bool	addHitable	(SceneObject_Hitable *hitable);
		virtual bool	rmHitable	(SceneObject_Hitable *hitable);
		
		// interface
		virtual bool	hit			(RecordHit *record, double t_min, double t_max) const override;
};


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_HPP
