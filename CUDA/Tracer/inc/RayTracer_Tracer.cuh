// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/14   initial update


#ifndef RAYTRACER_TRACER_CUH
#define RAYTRACER_TRACER_CUH


#include "../../Utility/Utility.cuh"
#include "../../Scatter/Scatter.cuh"
#include "../../Scene/Scene.cuh"


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
		__device__	RayTracer	();
		__device__	~RayTracer	();
		
		// operation
		__device__	void	setScene	(Scene *scene);

		__device__	Vec3f	trace		(const Camera *camera, fp_t x, fp_t y, int32_t depth);
		__device__	Vec3f	trace		(const Ray *ray, int32_t depth);
		__device__	Vec3f	trace		(RecordRay *record);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TRACER_CUH
