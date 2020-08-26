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


// Enum
// TODO: backup
// enum ScatterState {
// 	SCATTER_NONE,
// 	SCATTER_NEXT,
// 	SCATTER_YIELD,
// 	SCATTER_SPLIT
// };


// Data Structure
struct RecordScatter {
	// tree
	RecordScatter 		*top		= nullptr;
	RecordScatter		*parent		= nullptr;

	// backup
	// int32_t				sibling_prev		= -1;
	// int32_t				sibling_next		= -1;
	
	const Scene			*scene		= nullptr;
	const Scatter		*scatter	= nullptr;

	// to be more accurate
	// it should called space ordering
	//
	// used by refraction,
	// where need the index of the outer space
	// therefore the order of entering object is required
	const RecordScatter	*outer		= nullptr;

	int32_t				depth		= 0;

	// collision info
	bool				is_hit		= false;
	RecordHit			record_hit;

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

		// backup
		// int32_t			index_empty		= -1;
		// int32_t			ready_list		= -1;
		// int32_t			wait_list		= -1;

	// Operation
	public:
		// init, del
		MemoryControl_Scatter		();
		~MemoryControl_Scatter		();

		// operation
		void	setMemory			(void *memory, int32_t size);  // is 4GB enough ?
		void	reset				();

		void*	createRecord		();
		void*	createRecord		(RecordScatter *record);

		// backup
		// set record state: ready -> wait (read-only mode)
		// void	waitRecord			(RecordScatter *record);
		//
		// release entire memory space at the end
		// void	destroyRecord		(RecordScatter *record);
		
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
		// TODO: backup
		// ScatterState			scatter					(RecordScatter *dst, RecordScatter *src) const;

		bool					setTexture				(Texture *texture, int32_t offset);
		Texture*				getTexture				(int32_t offset);

		// interface
		virtual void			scatter					(RecordScatter *src, MemoryControl_Scatter *control) const = 0;
	
	protected:
		// operation
		// TODO: backup
		// void					createRecord_tree		(RecordScatter *dst, RecordScatter *src) const;
		// void					createRecord_ray		(RecordScatter *dst, RecordScatter *src, const Ray &ray) const;
		// void					createRecord_threshold	(RecordScatter *dst, RecordScatter *src, const Vec3f &ratio) const;

		// interface
		// TODO: backup
		// virtual ScatterState	scatter_shootRay		(RecordScatter *dst, RecordScatter *src, ScatterState state) const = 0;
};


class Scheduler_Scatter {
	// Data
	public:
		MemoryControl_Scatter		memory_control;
		int							queue			= 0;

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
		void		setRoot			(RecordScatter *record);
		void		getRoot			(RecordScatter *record);

		void		setScene		(Scene *scene);

		int8_t		schedule		();
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_SCATTER_HPP
