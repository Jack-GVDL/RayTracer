// Created by Jack Tse on 2020/06/11
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/11   initial update
// 2020/08/11   add Mapper_Sphere


#ifndef RAYTRACER_SCENEOBJECT_HITABLE_SPHERE_HPP
#define RAYTRACER_SCENEOBJECT_HITABLE_SPHERE_HPP


#include "RayTracer_SceneObject_Hitable.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Hitable_Sphere: public SceneObject_Hitable {
	// Data
	public:
		Vec3f		center	= Vec3f();
		double		radius	= 0;

	// Operation
	public:
		// init
		Hitable_Sphere()
		{
			updateBoundingBox();
		}

		// backup
		// SceneObject_Sphere(Vec3f center, double radius)
		// {
		// 	setCenter(center);
		// 	setRadius(radius);
		// }

		// operation
		void			setCenter	(const Vec3f &center);
		void			setRadius	(double radius);

		// interface
		virtual bool	hit			(RecordHit *record, double t_min, double t_max) const override;
	
	protected:
		// operation
		void			updateBoundingBox	();
};


class Mapper_Sphere: public Mapper {
	// Data
	public:
		Hitable_Sphere		*sphere;

	// Operation
	public:
		// init
		Mapper_Sphere()
		{}

		// operation
		void			setSphere		(Hitable_Sphere *sphere);

		// interface
		virtual void	map				(Vec3f &vector) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_SPHERE_HPP
