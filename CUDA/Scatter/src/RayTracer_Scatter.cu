#include "../inc/RayTracer_Scatter.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
__device__ static inline void*	get_record						(int32_t index, void *memory, int32_t offset);

// backup
/*
__device__ static inline void	schedule_check_collision		(Scene *scene, MemoryControl_Scatter *control, RecordRay *top, int32_t front, int32_t back);
__device__ static inline void	schedule_load_scatter			(Scene *scene, MemoryControl_Scatter *control, RecordRay *top, int32_t front, int32_t back);
__device__ static inline void	schedule_execute_scatter		(Scene *scene, MemoryControl_Scatter *control, RecordRay *top, int32_t front, int32_t back);
__device__ static inline void	schedule_accumulate_intensity	(Scene *scene, MemoryControl_Scatter *control, RecordRay *top, int32_t front, int32_t back);
*/


// Operation Handling
// memory control
__device__ MemoryControl_Scatter::MemoryControl_Scatter() {
	// offset must be power of 2 and divisible by 4KB
	// offset must larger than sizeof RecordRay
	int32_t size_record	= (int32_t)(sizeof(RecordRay));
	offset				= 1;

	for (uint8_t i = 0; i < 8; i++) {

		// offset must be power of 2 and larger than sizeof RecordRay
		if (offset < size_record) {
			offset *= 2;
			continue;
		}

		break;
	}
}


__device__ MemoryControl_Scatter::~MemoryControl_Scatter() {
}


__device__ void MemoryControl_Scatter::setMemory(void *memory, int32_t size) {
	// when take over another memory space,
	// need to reset the queue
	record_list		= memory;
	record_size		= size / offset;

	// reset memory space
	reset();
}


__device__ void MemoryControl_Scatter::reset() {
	index_empty = 0;
}


__device__ void* MemoryControl_Scatter::createRecord() {
	if (index_empty == -1 || index_empty == record_size) return nullptr;

	// get an empty record
	RecordRay *record = (RecordRay*)get_record(index_empty, record_list, offset);
	index_empty++;

	// no need to clear record content
	// bzero(record, sizeof(RecordRay));

	return record;
}


// backup
// it is assume that record must be in ready queue
// __device__ void MemoryControl_Scatter::waitRecord(RecordRay *record) {
// }
// 
// 
// __device__ void MemoryControl_Scatter::destroyRecord(RecordRay *record) {
// }


__device__ void* MemoryControl_Scatter::getRecord(int index) {
	return get_record(index, record_list, offset);
}


// scatter
__device__ Scatter::Scatter() {
}


__device__ Scatter::~Scatter() {
	delete[] texture_list;
}


// TODO: missing: CUDA operation check (checkCudaErrors)
__device__ error_t Scatter::allocateScatter(int size) {
	// free the original memory space
	cudaFree(scatter_list);

	// allocate new space
	cudaMalloc(&scatter_list, size * sizeof(Scatter*));
	scatter_size	= size;
	scatter_index	= 0;

	return ERROR_NO;
}


// TODO: missing: uniqueness check
__device__ error_t Scatter::addScatter(Scatter *scatter) {
	if (scatter_index == scatter_size) return ERROR_ANY;
	scatter_list[scatter_index] = scatter;
	scatter_index++;
	return ERROR_NO;
}


// TODO: not yet completed
__device__ error_t Scatter::rmScatter(Scatter *scatter) {
	return ERROR_ANY;
}


__device__ error_t Scatter::setTexture(Texture *texture, int offset) {
	if (texture_list == nullptr)				return false;
	if (offset < 0 || offset >= texture_size)	return false;
	
	texture_list[offset] = texture;
	return true;
}


__device__ Texture* Scatter::getTexture(int offset) {
	if (offset < 0 || offset >= texture_size) return nullptr;
	return texture_list[offset];
}


__device__ void Scatter::setRecord_tree(RecordRay *dst, RecordRay *src) const {
	dst->parent					= src;
	dst->scene					= src->scene;
	dst->outer					= src->outer;
	dst->depth					= src->depth - 1;

	dst->threshold				= Vec3f(1);
	dst->intensity				= Vec3f(0);

	dst->is_enable_hit			= 1;
	dst->scatter_source			= 1;

	dst->record_hit.length_min	= RAY_EPSILON;
	dst->record_hit.length_max	= std::numeric_limits<fp_t>::max();
}


__device__ void Scatter::setRecord_ray(RecordRay *dst, RecordRay *src, const Ray &ray) const {
	dst->record_hit.record.ray = ray;
}


__device__ void Scatter::setRecord_threshold(RecordRay *dst, RecordRay *src, const Vec3f &ratio) const {
	dst->threshold	= src->threshold.prod(ratio);
	src->threshold	-= dst->threshold;
}


__device__ void Scatter::setRecord_scatter(RecordRay *dst, RecordRay *src) const {
	if (scatter_index == 0) {
		dst->scatter_source = 1;
		return;
	}

	dst->scatter_source					= 0;
	dst->record_scatter.scatter_list	= scatter_list;
	dst->record_scatter.size			= scatter_index;
}


// scheduler
__device__ Scheduler_Scatter::Scheduler_Scatter() {
}


__device__ Scheduler_Scatter::~Scheduler_Scatter() {
}


__device__ void Scheduler_Scatter::setRoot(RecordRay *record) {
	memory_control.reset();
	queue = 0;

	// create record
	RecordRay *temp = (RecordRay*)memory_control.createRecord();
	if (temp == nullptr) return;

	// copy from other source
	cudaMemcpy(temp, record, sizeof(RecordRay));
}


__device__ void Scheduler_Scatter::getRoot(RecordRay *record) {
	RecordRay *temp = (RecordRay*)memory_control.getRecord(0);
	if (temp == nullptr) return;

	// need to normalize resultant intensity
	// it should be ranging between 0 and 1
	temp->intensity = temp->intensity.clamp(0, 1);
	cudaMemcpy(record, temp, sizeof(RecordRay));
}


__device__ void Scheduler_Scatter::setScene(Scene *scene) {
	this->scene = scene;
}


// currently no parallel processing
// so all the stuff will be done here
//
// return 0 if no record is queuing, else 1
// TODO: function too long, split the function, use static inline
__device__ int8_t Scheduler_Scatter::schedule() {
	// read ray queue
	// quit if no record is queuing
	if (queue == memory_control.index_empty) return 0;
	int32_t index_empty = memory_control.index_empty;
	
	RecordRay		*top		= (RecordRay*)memory_control.getRecord(0);
	RecordRay		*record;
	const Shader	*shader;

	// collision check
	// currently no parallel processing
	// backup
	// schedule_check_collision(		scene, &memory_control, top, queue, index_empty	);
	// schedule_load_scatter(			scene, &memory_control, top, queue, index_empty	);
	// schedule_execute_scatter(		scene, &memory_control, top, queue, index_empty	);
	// schedule_accumulate_intensity(	scene, &memory_control, top, queue, index_empty	);

	for (int32_t i = queue; i < index_empty; i++) {
		record = (RecordRay*)memory_control.getRecord(i);
	
		if (record->depth == 0)	{
			continue;
		}
		if (!record->is_enable_hit)	{
			record->is_hit = false;
			continue;
		}
	
		record->is_hit = scene->hit(&(record->record_hit));
	}

	// load scatter
	for (int32_t i = queue; i < index_empty; i++) {
		record = (RecordRay*)memory_control.getRecord(i);
		if (record->depth == 0) continue;
		
		switch (record->scatter_source) {
			// 0: already in record
			case 0:
				break;

			// 1: hit scene object, else NULL
			case 1:
				SceneObject_Hitable *object = record->record_hit.record.object;
				if (record->is_hit)	{
					record->record_scatter.scatter_list = object->shader.scatter_list.data();
					record->record_scatter.size			= object->shader.scatter_list.size();
					record->record_scatter.index		= 0;

				} else {
					record->record_scatter.scatter_list = nullptr;
					record->record_scatter.size			= 0;
					record->record_scatter.index		= 0;

				}
				break;
		}

	}

	// scatter operation
	for (int32_t i = queue; i < index_empty; i++) {
		record = (RecordRay*)memory_control.getRecord(i);
		if (record->depth == 0) 							continue;
		if (record->record_scatter.scatter_list == nullptr)	continue;

		// scatter operation
		// TODO: future
		// record = (RecordRay*)memory_control.getRecord(i);
		// record->record_scatter.scatter_list[record->record_scatter.index]->scatter(record, &memory_control);

		for (int16_t i = 0; i < record->record_scatter.size; i++) {
			record->record_scatter.scatter_list[i]->scatter(record, &memory_control);
		}
	}

	// intensity accumulation
	for (int32_t i = queue; i < index_empty; i++) {
		record = (RecordRay*)memory_control.getRecord(i);
		if (record->depth == 0) continue;

		top->intensity += record->intensity;
	}

	// configure to get ready to next scheduling
	queue = index_empty;

	if (top->intensity[0] > 1.0 && top->intensity[1] > 1.0 && top->intensity[2] > 1.0) return 0;
	return 1;
}


// Static Function Implementation
__device__ static inline void* get_record(int32_t index, void *memory, int32_t offset) {
	return (uint8_t*)memory + index * offset;
}


// backup
/*
__device__ static inline void schedule_check_collision(Scene *scene, MemoryControl_Scatter *control, RecordRay *top, int32_t front, int32_t back) {
	RecordRay *record;

	for (int32_t i = front; i < back; i++) {
		record = (RecordRay*)control->getRecord(i);

		// skip record
		if (record->depth == 0)	{
			continue;
		}
		if (!record->is_enable_hit)	{
			record->is_hit = false;
			continue;
		}

		record->is_hit = scene->hit(&(record->record_hit));
	}
}


__device__ static inline void schedule_load_scatter(Scene *scene, MemoryControl_Scatter *control, RecordRay *top, int32_t front, int32_t back) {
	RecordRay *record;
	
	for (int32_t i = front; i < back; i++) {
		record = (RecordRay*)control->getRecord(i);

		// skip record
		if (record->depth == 0) continue;
		
		switch (record->scatter_source) {
			// 0: already in record
			case 0:
				break;

			// 1: hit scene object, else NULL
			case 1:
				SceneObject_Hitable *object = record->record_hit.record.object;
				if (record->is_hit)	{
					record->record_scatter.scatter_list = object->shader.scatter_list.data();
					record->record_scatter.size			= object->shader.scatter_list.size();
					record->record_scatter.index		= 0;

				} else {
					record->record_scatter.scatter_list = nullptr;
					record->record_scatter.size			= 0;
					record->record_scatter.index		= 0;

				}
				break;
		}

	}
}


__device__ static inline void schedule_execute_scatter(Scene *scene, MemoryControl_Scatter *control, RecordRay *top, int32_t front, int32_t back) {
	RecordRay *record;
	
	for (int32_t i = front; i < back; i++) {
		record = (RecordRay*)control->getRecord(i);

		// skip record
		if (record->depth == 0) 							continue;
		if (record->record_scatter.scatter_list == nullptr)	continue;

		// scatter operation
		// TODO: future
		// record = (RecordRay*)memory_control.getRecord(i);
		// record->record_scatter.scatter_list[record->record_scatter.index]->scatter(record, &memory_control);

		for (int16_t i = 0; i < record->record_scatter.size; i++) {
			record->record_scatter.scatter_list[i]->scatter(record, control);
		}
	}
}


__device__ static inline void schedule_accumulate_intensity(Scene *scene, MemoryControl_Scatter *control, RecordRay *top, int32_t front, int32_t back) {
	RecordRay *record;
	
	for (int32_t i = front; i < back; i++) {
		record = (RecordRay*)control->getRecord(i);
		if (record->depth == 0) continue;

		top->intensity += record->intensity;
	}
}
*/
