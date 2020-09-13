// Author: Jack Tse
// Email: jacktsetcy@gmail.com
//
// Log
// 2020/09/11   initial update


#ifndef RAYTRACER_SCATTER_CUH
#define RAYTRACER_SCATTER_CUH


#include "../../Utility/Utility.cuh"
#include "../../Scene/Scene.cuh"
#include "../../Material/Material.cuh"


// Define
// ...


// Typedef
// ...


// Data Structure
class Scatter;


struct RecordScatter {
	Scatter*		*scatter_list	= nullptr;
	int16_t			size			= 0;
	int16_t			index			= 0;
};


struct RecordRay {
// Data
public:
	// tree
	RecordRay			*parent			= nullptr;
	int16_t				depth			= 0;
	
	const Scene			*scene			= nullptr;
	
	// scatter
	// source of scatter
	// 0: already in record
	// 1: hit scene object, else NULL
	uint8_t				scatter_source	= 1;
	RecordScatter		record_scatter;

	// space ordering
	//
	// used by refraction,
	// where need the index of the outer space
	// therefore the order of entering object is required
	const RecordRay		*outer			= nullptr;

	// collision info
	int8_t	 			is_enable_hit	= 1;
	int8_t				is_hit			= 0;
	RecordHit_Extend	record_hit;

	Vec3f				threshold		= Vec3f(1);
	Vec3f				intensity		= Vec3f(0);

// Operation
public:
	// operation
	// ...
};


class MemoryControl_Scatter {
	// Data
	public:
		void			*record_list	= nullptr;
		int32_t			record_size		= 0;
		int32_t			offset			= 0;

		// int32_t should be enough
		// if queue larger than this
		// it should consider use more than 1 scheduler
		int32_t			index_empty			= -1;

	// Operation
	public:
		// init, del
		__device__ MemoryControl_Scatter	();
		__device__ ~MemoryControl_Scatter	();

		// operation
		__device__ void		setMemory			(void *memory, int32_t size);  // currently use int32_t, is 4GB enough ?
		__device__ void		reset				();

		__device__ void*	createRecord		();

		// backup
		// set record state: ready -> wait (read-only mode)
		// void	waitRecord			(RecordRay *record);
		//
		// release entire memory space at the end
		// void	destroyRecord		(RecordRay *record);
		
		// helper
		__device__ void*	getRecord			(int index);
};


class Scatter {
	// Data
	public:
		// TODO: consider to use vector
		Texture*	*texture_list	= nullptr;
		int32_t		texture_size	= 0;

		Scatter*	*scatter_list	= nullptr;
		int32_t		scatter_size	= 0;
		int32_t		scatter_index	= 0;

	// Operation
	public:
		// init, del
		__device__ Scatter		();
		__device__ ~Scatter		();

		// operation
		// ...

		__device__ error_t				allocateScatter			(int size);
		__device__ error_t				addScatter				(Scatter *scatter);
		__device__ error_t				rmScatter				(Scatter *scatter);

		__device__ error_t				setTexture				(Texture *texture, int32_t offset);
		__device__ Texture*				getTexture				(int32_t offset);

		// interface
		__device__ virtual void			scatter					(RecordRay *src, MemoryControl_Scatter *control) const = 0;
	
	protected:
		// operation
		__device__ void					setRecord_tree			(RecordRay *dst, RecordRay *src) const;
		__device__ void					setRecord_ray			(RecordRay *dst, RecordRay *src, const Ray &ray) const;
		__device__ void					setRecord_threshold		(RecordRay *dst, RecordRay *src, const Vec3f &ratio) const;
		__device__ void					setRecord_scatter		(RecordRay *dst, RecordRay *src) const;

		// interface
		// ...
}; 


class Scheduler_Scatter {
	// Data
	public:
		MemoryControl_Scatter		memory_control;
		int32_t						queue			= 0;

		Scene						*scene			= nullptr;

	// Operation
	public:
		// init, del
		__device__ Scheduler_Scatter		();
		__device__ ~Scheduler_Scatter		();

		// operation
		__device__ void		setRoot			(RecordRay *record);
		__device__ void		getRoot			(RecordRay *record);

		__device__ void		setScene		(Scene *scene);

		__device__ int8_t	schedule		();
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_CUH
