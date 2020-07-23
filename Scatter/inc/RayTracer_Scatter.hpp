// Created by Jack Tse on 2020/07/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/20   initial update


#ifndef RAYTRACER_SCATTER_HPP
#define RAYTRACER_SCATTER_HPP


#include "../../Utility/Utility.hpp"
#include "../../Scene/Scene.hpp"
#include "../../Material/Material.hpp"


// Define
// ...


// Typedef
// ...


// Enum
enum ScatterState {
	SCATTER_NONE,
	SCATTER_NEXT,
	SCATTER_YIELD,
	SCATTER_SPLIT
};


// Data Structure
struct RecordScatter {
	const RecordScatter	*parent		= nullptr;
	const Scene			*scene		= nullptr;
	const Scatter		*scatter	= nullptr;

	// used by refraction,
	// where need the index of the outer space
	// therefore the order of entering object is required
	const RecordScatter	*outer		= nullptr;

	int					depth		= 0;

	bool				is_hit		= false;
	RecordHit			record_hit;

	Vec3f				threshold	= Vec3f(1);
	Vec3f				intensity	= Vec3f(0);
};


class Scatter {
	// Data
	public:
		Material *material	= nullptr;

	// Operation
	public:
		// operation
		virtual ScatterState	scatter	(RecordScatter *dst, RecordScatter *src) const;

	protected:
		// operation
		void					createRecord_tree		(RecordScatter *dst, RecordScatter *src) const;
		void					createRecord_ray		(RecordScatter *dst, RecordScatter *src, const Ray &ray) const;
		void					createRecord_threshold	(RecordScatter *dst, RecordScatter *src, const Vec3f &ratio) const;

		// interface
		virtual ScatterState	scatter_shootRay	(RecordScatter *dst, RecordScatter *src, ScatterState state) const = 0;
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_HPP
