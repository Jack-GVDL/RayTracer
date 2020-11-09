// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/11/05   initial update


#ifndef RAYTRACER_SAMPLER_GRID_CUH
#define RAYTRACER_SAMPLER_GRID_CUH


#include "RayTracer_Sampler.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Sampler_Grid: public Sampler {
	// Data
	public:
		int32_t	grid_w;
		int32_t	grid_h;

	// Operation
	public:
		// __init__
		__host__	Sampler_Grid	();
		__host__	~Sampler_Grid	();

		// operation
		__host__ error_t			setSizeGrid			(int32_t w, int32_t h);

		// backup
		// virtual __host__ error_t	setSizeImage		(int32_t w, int32_t h) override;
		
		virtual __host__ error_t	convertPreMapper	(fp_t *dir_list, int32_t size) override;
		virtual __host__ error_t	convertPostMapper	(fp_t *image_list, int32_t size) override;

	protected:
		virtual __host__ void		update				() override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SAMPLER_GRID_CUH
