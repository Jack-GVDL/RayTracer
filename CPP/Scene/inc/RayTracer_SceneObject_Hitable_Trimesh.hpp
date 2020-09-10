// Created by Jack Tse on 2020/07/03
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/03   initial update
// 2020/08/11   add Mapper_Trimesh


#ifndef RAYTRACER_SCENEOBJECT_HITABLE_TRIMESH_HPP
#define RAYTRACER_SCENEOBJECT_HITABLE_TRIMESH_HPP


#include "../../Material/Material.hpp"
#include "RayTracer_SceneObject_Hitable.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Hitable_Trimesh: public SceneObject_Hitable {
	// Data
	public:
		Vec3f	point[3];

	// Operation
	public:
		// init
		Hitable_Trimesh		();
		~Hitable_Trimesh	();

		// operation
		void			setPoint	(const Vec3f &p0, const Vec3f &p1, const Vec3f &p2);

		// interface
		virtual bool	hit			(RecordHit *record, fp_t t_min, fp_t t_max) const override;

	protected:
		// operation
		void			updateBoundingBox	();
};


class Texture_Mapper_Trimesh: public Texture {
	// Data
	public:
		Hitable_Trimesh		*trimesh	= nullptr;

	// Operation
	public:
		// init
		Texture_Mapper_Trimesh()
		{
			input_size	= 1;
			input_list	= new Texture*[input_size];
			for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
		}

		// operation
		void			setTrimesh		(Hitable_Trimesh *trimesh);

		// interfce
		virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// ...
};


class Texture_Direction_Trimesh: public Texture {
	// Data
	public:
		Hitable_Trimesh		*trimesh	= nullptr;

	// Operation
	public:
		// init
		Texture_Direction_Trimesh()
		{
			input_size	= 2;
			input_list	= new Texture*[input_size];
			for (int32_t i = 0; i < input_size; i++) input_list[i] = nullptr;
		}

		// operation
		void			setTrimesh		(Hitable_Trimesh *trimesh);

		// interfce
		virtual void	setPixel		(const Vec3f &point, const Vec3f &pixel) override;
		virtual void	_getPixel_		(Vec3f &dst, Vec3f *src) const override;

	protected:
		// interface
		// ...
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCENEOBJECT_HITABLE_TRIMESH_HPP
