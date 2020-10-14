#include "../inc/RayTracer_Tracer.cuh"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
__device__ RayTracer::RayTracer() {
	// TODO: temporary allocate some space for memory control
	// void *memory = malloc(sizeof(uint8_t) * 1024 * 50);
	void *memory;
	cudaMalloc(&memory, 1024 * 50 * sizeof(uint8_t));

	scheduler.memory_control.setMemory(memory, sizeof(uint8_t) * 1024 * 20);
}


__device__ RayTracer::~RayTracer() {
}


__device__ void RayTracer::setScene(Scene *scene) {
	this->scene = scene;
	scheduler.setScene(scene);
}


__device__ Vec3f RayTracer::trace(const Camera *camera, fp_t x, fp_t y, int32_t depth) {
	Ray ray = camera->getRay(x, y);
	return trace(&ray, depth);
}


__device__ Vec3f RayTracer::trace(const Ray *ray, int depth) {
	// init scatter record
	RecordRay scatter_record;
	scatter_record.parent	= nullptr;
	scatter_record.scene	= scene;
	scatter_record.depth	= depth;

	RecordHit *record_hit	= &(scatter_record.record_hit.record);
	record_hit->ray 		= *ray;

	return trace(&scatter_record);
}


__device__ Vec3f RayTracer::trace(RecordRay *record) {
	// set record
	scheduler.setRoot(record);

	// run the scheduler until there is nothing to be scheduled
	while (scheduler.schedule());

	// return intensity
	scheduler.getRoot(record);
	return record->intensity;
}


// Static Function Implementation
// ...
