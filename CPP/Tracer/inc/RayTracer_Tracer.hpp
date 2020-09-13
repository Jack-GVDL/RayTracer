// Created by Jack Tse on 2020/06/25
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/25   initial update
// 2020/07/20   change include path
// 2020/07/26   add External.hpp


#ifndef RAYTRACER_TRACER_HPP
#define RAYTRACER_TRACER_HPP


#include "../../Utility/Utility.hpp"
#include "../../Scatter/Scatter.hpp"
#include "../../Scene/Scene.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class RayTracer {
	// Data
	public:
		Scene				*scene		= nullptr;

		// TODO: need to consider there will be multiple scheduler in future
		// may need to be list of scheduler
		Scheduler_Scatter	scheduler;

	// Operation
	public:
		// init
		RayTracer	();
		~RayTracer	();
		
		// operation
		void	setScene	(Scene *scene);

		Vec3f	trace		(const Camera *camera, fp_t x, fp_t y, int32_t depth);
		Vec3f	trace		(const Ray *ray, int32_t depth);
		Vec3f	trace		(RecordRay *record);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TRACER_HPP
