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


// TODO: backup
// class Mapper_Sphere: public Mapper {
// 	// Data
// 	public:
// 		Hitable_Sphere		*sphere;

// 	// Operation
// 	public:
// 		// init
// 		Mapper_Sphere()
// 		{}

// 		// operation
// 		void			setSphere		(Hitable_Sphere *sphere);

// 		// interface
// 		virtual void	map				(Vec3f &vector) const override;
// };


class Texture_Mapper_Sphere: public Texture {
	// Data
	public:
		Hitable_Sphere		*sphere	= nullptr;

	// Operation
	public:
		// init
		Texture_Mapper_Sphere()
		{
			input_size	= 1;
			input_list	= new Texture*[input_size];
			for (int i = 0; i < input_size; i++) input_list[i] = nullptr;
		}

		// operation
		void			setSphere		(Hitable_Sphere *sphere);

		// interfce
		virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// TODO: backup
		// virtual void	_getPixel_		(Vec3f &dst, const Vec3f &src) const override;
};


class Texture_Direction_Sphere: public Texture {
	// Data
	public:
		Hitable_Sphere		*sphere = nullptr;

	// Operation
	public:
		// init
		Texture_Direction_Sphere()
		{
			input_size	= 2;
			input_list	= new Texture*[input_size];
			for (int i = 0; i < input_size; i++) input_list[i] = nullptr;
		}

		// operation
		void			setSphere		(Hitable_Sphere *sphere);

		// interfce
		virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// TODO: backup
		// virtual void	_getPixel_		(Vec3f &dst, const Vec3f &src) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_SPHERE_HPP
