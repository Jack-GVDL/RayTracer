#include <limits>
#include "../inc/RayTracer_Tracer.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
RayTracer::RayTracer() {
	// TODO: temporary allocate some space for memory control
	void *memory = malloc(sizeof(uint8_t) * 1024 * 20);
	scheduler.memory_control.setMemory(memory, sizeof(uint8_t) * 1024 * 20);
}


RayTracer::~RayTracer() {
}


void RayTracer::setScene(Scene *scene) {
	this->scene = scene;
	scheduler.setScene(scene);
}


Vec3f RayTracer::trace(const Camera *camera, fp_t x, fp_t y, int32_t depth) {
	Ray ray = camera->getRay(x, y);
	return trace(&ray, depth);
}


Vec3f RayTracer::trace(const Ray *ray, int depth) {
	// init scatter record
	RecordRay scatter_record;
	scatter_record.parent		= nullptr;
	scatter_record.scene		= scene;
	scatter_record.depth		= depth;

	scatter_record.record_hit.ray = *ray;

	return trace(&scatter_record);
}


Vec3f RayTracer::trace(RecordRay *record) {
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
