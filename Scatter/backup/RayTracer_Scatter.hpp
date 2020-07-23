// Created by Jack Tse on 2020/06/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/20   initial update
// 2020/06/23   change scatter structure
// 2020/06/30   change scatter structure - duplicate count


#ifndef RAYTRACER_SCATTER_HPP
#define RAYTRACER_SCATTER_HPP


#include <vector>
#include "../../Utility/Utility.hpp"
#include "../../Scene/Scene.hpp"


// Define
// ...


// Typedef
// ...


// Enum
enum ScatterState {
	// TODO: need description
	SCATTER_NONE,

	// TODO: need description
	SCATTER_NEXT,

	// this is for the loop scatter
	// basic mechanism
	//
	// int intensity = 0;
	// int count = 0;
	// while (scatter() == SCATTER_EQUAL_SPLIT) {
	//		intensity += scatter_record.intensity;
	//		count++;	
	// }
	// intensity /= count;
	//
	SCATTER_EQUAL_SPLIT,

	// TODO: need description
	SCATTER_YIELD
};


// Data Structure
class Scatter;


struct ScatterRecord {
	const ScatterRecord	*parent		= nullptr;
	const Scene			*scene		= nullptr;
	const Scatter		*scatter	= nullptr;

	// used by refraction,
	// where need the index of the outer space
	// therefore the order of entering object is required
	const ScatterRecord *outer		= nullptr;
	
	int					depth		= 0;
	int					loop		= 0;

	Ray					ray;
	bool				is_hit		= false;
	HitRecord			hit_record;

	Vec3f				thresh		= Vec3f(1);
	Vec3f				intensity	= Vec3f(0);
};


class Scatter {
	// Data
	public:
		std::vector<Scatter*>	scatter_list; 			// TODO: use the linux style linked list later

		// it is possible that to entering scatter multiple time
		// for example
		// scatter_1 -> scatter_2 -> scatter_2 -> scatter_2 -> scatter_3
		// to save space and make programmer lives easier
		// above structure can be descripted as 
		// scatter_1 -> scatter_2 (loop_count = 2) -> scatter_3
		int						loop_count		= 1; 	// default 1 (one pass)

	// Operation
	public:
		// operation
		bool			addChild	(Scatter *scatter);
		bool    		rmChild		(Scatter *scatter);
		ScatterState	scatter		(ScatterRecord *dst, ScatterRecord *src) const;

	protected:
		// interface
		virtual ScatterState	scatter_shootRay	(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const;
		virtual	ScatterState	scatter_buildTree	(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_HPP
