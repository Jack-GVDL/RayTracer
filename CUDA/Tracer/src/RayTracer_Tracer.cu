#include "../inc/RayTracer_Tracer.cuh"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
__device__ Tracer::Tracer() {
}


__device__ Tracer::~Tracer() {
}


__device__ void Tracer::setScene(Scene *scene) {
	this->scene = scene;
}


__device__ error_t Tracer::addScheduler(Scheduler_Scatter *scheduler) {
	if (scheduler == nullptr) return ERROR_ANY;

	scheduler_list.push_back(&scheduler, sizeof(Scheduler_Scatter*));
	return ERROR_NO;
}


// TODO: not yet completed
__device__ error_t Tracer::rmScheduler(Scheduler_Scatter *scheduler) {
	return ERROR_ANY;
}


__device__ Vec3f Tracer::trace(const Camera *camera, fp_t x, fp_t y, int32_t depth, int32_t index) {
	Ray ray = camera->getRay(x, y);
	return trace(&ray, depth, index);
}


__device__ Vec3f Tracer::trace(const Ray *ray, int depth, int32_t index) {
	// init scatter record
	RecordRay scatter_record;
	scatter_record.parent	= nullptr;
	scatter_record.scene	= scene;
	scatter_record.depth	= depth;

	RecordHit *record_hit	= &(scatter_record.record_hit.record);
	record_hit->ray 		= *ray;

	return trace(&scatter_record, index);
}


__device__ Vec3f Tracer::trace(RecordRay *record, int32_t index) {
	// request for a scheduler
	int32_t scheduler_size = scheduler_list.index / sizeof(Scheduler_Scatter*);
	if (index >= scheduler_size) return Vec3f();

	Scheduler_Scatter *scheduler = ((Scheduler_Scatter**)scheduler_list.list)[index];

	// first set record
	// then run the scheduler until there is nothing to be scheduled
	scheduler->setScene(scene);
	scheduler->setRoot(record);

	while (scheduler->schedule());

	// return intensity
	scheduler->getRoot(record);
	return record->intensity;
}


// Static Function Implementation
// ...
