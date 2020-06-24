// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update
// 2020/06/23   change scatter structure


#ifndef RAYTRACER_SCATTER_HPP
#define RAYTRACER_SCATTER_HPP


#include <vector>
#include "RayTracer_Scene.hpp"


// Define
// ...


// Typedef
// ...


// Enum
enum ScatterStatus {
	SCATTER_NONE,
	SCATTER_NEXT,
	SCATTER_YIELD
};


// Data Structure
class Scatter;


struct ScatterRecord {
	const ScatterRecord	*parent;
	const Scene			*scene;
	const Scatter		*scatter;
	
	int			depth;
	Ray			ray;
	bool		is_hit;
	HitRecord	hit_record;

	Vec3f		thresh;
	Vec3f		intensity;
};


class Scatter {
	// Data
	public:
		std::vector<Scatter*>	scatter_list;

	// Operation
	public:
		// operation
		ScatterStatus	scatter		(ScatterRecord *dst, ScatterRecord *src) const;
		bool			addChild	(Scatter *scatter);
		bool    		rmChild		(Scatter *scatter);

	protected:
		// interface
		virtual ScatterStatus	_scatter_	(ScatterRecord *dst, ScatterRecord *src) const = 0;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_HPP
