// Created by Jack Tse on 2020/07/20
//
// Log
// 2020/07/20   initial update
// 2020/08/26   Scheduler_Scatter


#ifndef RAYTRACER_SCATTER_HPP
#define RAYTRACER_SCATTER_HPP


#include <stdint.h>
#include "../../Utility/Utility.hpp"
#include "../../Scene/Scene.hpp"
#include "../../Material/Material.hpp"


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
	// tree
	RecordRay 			*top		= nullptr;
	RecordRay			*parent		= nullptr;
	int16_t				depth		= 0;
	
	const Scene			*scene		= nullptr;
	
	// scatter
	RecordScatter		record_scatter;

	// control
	int8_t	 			is_enable_hit	= 1;

	// source of scatter
	// 0: already in record
	// 1: hit scene object, else NULL
	uint8_t				scatter_source	= 1;

	// space ordering
	//
	// used by refraction,
	// where need the index of the outer space
	// therefore the order of entering object is required
	const RecordRay		*outer		= nullptr;

	// collision info
	bool				is_hit		= false;
	RecordHit_Extend	record_hit;

	Vec3f				threshold	= Vec3f(1);
	Vec3f				intensity	= Vec3f(0);
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
		MemoryControl_Scatter		();
		~MemoryControl_Scatter		();

		// operation
		void	setMemory			(void *memory, int32_t size);  // is 4GB enough ?
		void	reset				();

		void*	createRecord		();

		// backup
		// set record state: ready -> wait (read-only mode)
		// void	waitRecord			(RecordRay *record);
		//
		// release entire memory space at the end
		// void	destroyRecord		(RecordRay *record);
		
		// helper
		void*	getRecord			(int index);
};


class Scatter {
	// Data
	public:
		Texture*	*texture_list	= nullptr;
		int32_t		texture_size	= 0;

	// Operation
	public:
		// init, del
		Scatter		();
		~Scatter	();

		// operation
		// ...

		bool					setTexture				(Texture *texture, int32_t offset);
		Texture*				getTexture				(int32_t offset);

		// interface
		virtual void			scatter					(RecordRay *src, MemoryControl_Scatter *control) const = 0;
	
	protected:
		// operation
		void					setRecord_tree			(RecordRay *dst, RecordRay *src) const;
		void					setRecord_ray			(RecordRay *dst, RecordRay *src, const Ray &ray) const;
		void					setRecord_threshold		(RecordRay *dst, RecordRay *src, const Vec3f &ratio) const;

		// interface
		// ...
}; 


class Scheduler_Scatter {
	// Data
	public:
		MemoryControl_Scatter		memory_control;
		int32_t						queue			= 0;

		Scene						*scene			= nullptr;

		// TODO: find a better name for Shader
		Shader						shader_not_hit;
		Shader						shader_hit;

	// Operation
	public:
		// init, del
		Scheduler_Scatter			();
		~Scheduler_Scatter			();

		// operation
		void		setRoot			(RecordRay *record);
		void		getRoot			(RecordRay *record);

		void		setScene		(Scene *scene);

		int8_t		schedule		();
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_HPP
