// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/14   initial update
// 2020/10/16   support multi thread


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
// TODO: should rename to Tracer
class Tracer {
	// Data
	public:
		Scene				*scene		= nullptr;

		Vector				scheduler_list;

	// Operation
	public:
		// init
		__device__	Tracer	();
		__device__	~Tracer	();
		
		// operation
		__device__	void	setScene			(Scene *scene);

		__device__	error_t	addScheduler		(Scheduler_Scatter *scheduler);
		__device__	error_t	rmScheduler			(Scheduler_Scatter *scheduler);

		__device__	Vec3f	trace				(const Camera *camera, fp_t x, fp_t y, int32_t depth, int32_t index);
		__device__	Vec3f	trace				(const Ray *ray, int32_t depth, int32_t index);
		__device__	Vec3f	trace				(RecordRay *record, int32_t index);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_TRACER_CUH
