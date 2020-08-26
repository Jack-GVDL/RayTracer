#include "../inc/RayTracer_Scatter.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline void*	get_record	(int32_t index, void *memory, int32_t offset);


// Operation Handling
// memory control
MemoryControl_Scatter::MemoryControl_Scatter() {
	// offset must be power of 2 and divisible by 4KB
	// offset must larger than sizeof RecordScatter
	offset = (int32_t)(sizeof(RecordScatter));

	offset = UtilMath::getLeadingZero(offset);
	offset = offset << 1;
}


MemoryControl_Scatter::~MemoryControl_Scatter() {
}


void MemoryControl_Scatter::setMemory(void *memory, int32_t size) {
	// when take over another memory space,
	// need to reset the queue
	record_list		= memory;
	record_size		= size / offset;

	// reset memory space
	reset();

	// backup
	// no record is ready and wait
	// ready_list	= -1;
	// wait_list	= -1;

	// backup
	// all record should be empty
	// RecordScatter *record;
	// for (int32_t i = 0; i < record_size - 1; i++) {
	// 	record = (RecordScatter*)get_record(i, memory, offset);
	// 	record->sibling = i + 1;
	// }
	//
	// last one should pointer to nothing (sibling = -1)
	// record = (RecordScatter*)get_record(record_size - 1, memory, offset);
	// record->sibling = -1;
}


void MemoryControl_Scatter::reset() {
	index_empty = 0;
}


void* MemoryControl_Scatter::createRecord() {
	if (index_empty == -1) return nullptr;

	// get an empty record
	RecordScatter *record = (RecordScatter*)get_record(index_empty, record_list, offset);
	index_empty++;

	// no need to clear record content
	// bzero(record, sizeof(RecordScatter));

	return record;
}


void* MemoryControl_Scatter::createRecord(RecordScatter *record) {
	RecordScatter *record = (RecordScatter*)createRecord();
	record->parent = record;
	return record;
}


// backup
// it is assume that record must be in ready queue
// void MemoryControl_Scatter::waitRecord(RecordScatter *record) {
// }
// 
// 
// void MemoryControl_Scatter::destroyRecord(RecordScatter *record) {
// }


void* MemoryControl_Scatter::getRecord(int index) {
	return get_record(index, record_list, offset);
}


// scatter
Scatter::Scatter() {
}


Scatter::~Scatter() {
	delete[] texture_list;
}


// TODO: backup
// ScatterState Scatter::scatter(RecordScatter *dst, RecordScatter *src) const {
// 	ScatterState state = SCATTER_NONE;
// 	state = scatter_shootRay(dst, src, state);
// 	// state = scatter_buildTree(dst, src, state);
// 	return state;
// }


bool Scatter::setTexture(Texture *texture, int offset) {
	if (texture_list == nullptr)				return false;
	if (offset < 0 || offset >= texture_size)	return false;
	
	texture_list[offset] = texture;
	return true;
}


Texture* Scatter::getTexture(int offset) {
	if (offset < 0 || offset >= texture_size) return nullptr;
	return texture_list[offset];
}


// TODO: backup
// void Scatter::createRecord_tree(RecordScatter *dst, RecordScatter *src) const {
// 	// if (dst->parent == nullptr)		dst->parent		= src;
// 	// if (dst->scene == nullptr)		dst->scene		= src->scene;
// 	// if (dst->scatter == nullptr)	dst->scatter	= this;
// 	// if (dst->outer == nullptr)		dst->outer		= src->outer;
// 	// dst->depth		= src->depth - 1;
//
// 	dst->parent		= src;
// 	dst->scene		= src->scene;
// 	dst->scatter	= this;
// 	dst->outer		= src->outer;
// 	dst->depth		= src->depth - 1;
// }
//
//
// void Scatter::createRecord_ray(RecordScatter *dst, RecordScatter *src, const Ray &ray) const {
// 	dst->record_hit.ray = ray;
// }
//
//
// void Scatter::createRecord_threshold(RecordScatter *dst, RecordScatter *src, const Vec3f &ratio) const {
// 	dst->threshold	= src->threshold.prod(ratio);
// 	src->threshold	-= dst->threshold;
// }


// scheduler
Scheduler_Scatter::Scheduler_Scatter() {
}


Scheduler_Scatter::~Scheduler_Scatter() {
}


void Scheduler_Scatter::setRoot(RecordScatter *record) {
	memory_control.reset();

	// create record
	RecordScatter *temp = (RecordScatter*)memory_control.createRecord();
	if (temp == nullptr) return;

	// copy from other source
	memcpy(temp, record, sizeof(RecordScatter));
}


void Scheduler_Scatter::getRoot(RecordScatter *record) {
	RecordScatter *temp = (RecordScatter*)memory_control.getRecord(0);
	if (temp == nullptr) return;

	memcpy(record, temp, sizeof(RecordScatter));
}


void Scheduler_Scatter::setScene(Scene *scene) {
	this->scene = scene;
}


// currently no parallel processing
// so all the stuff will be done here
//
// return 0 if no record is queuing, else 1
int8_t Scheduler_Scatter::schedule() {
	// read ray queue
	// quit if no record is queuing
	if (queue == memory_control.index_empty) return 0;
	int index_empty = memory_control.index_empty;
	
	RecordScatter	*top		= (RecordScatter*)memory_control.getRecord(0);
	RecordScatter	*record;
	const Shader	*shader;

	// collision check
	// currently no parallel processing
	for (int i = queue; i < index_empty; i++) {
		record			= (RecordScatter*)memory_control.getRecord(i);
		record->is_hit	= scene->hit(&(record->record_hit));
	}

	// scatter operation
	// currently no parallel processing
	for (int i = queue; i < index_empty; i++) {
		record = (RecordScatter*)memory_control.getRecord(i);

		// get scatter list
		if (record->is_hit) {
			const SceneObject_Hitable *object = record->record_hit.object;
			shader = &(object->shader);
		} else {
			shader = &shader_not_hit;
		}

		// scatter operation
		for (auto *scatter : shader->scatter_list) scatter->scatter(record, &memory_control);
	}

	// TODO: not yet completed
	// intensity accumulation
	// currently no parallel processing
	for (int i = queue; i < index_empty; i++) {
		record			= (RecordScatter*)memory_control.getRecord(i);
		top->intensity	+= record->threshold * record->intensity; 
	}

	// configure to get ready to next scheduling
	queue = index_empty;

	return 1;
}


// Static Function Implementation
static inline void* get_record(int32_t index, void *memory, int32_t offset) {
	return (uint8_t*)memory + index * offset;
}
