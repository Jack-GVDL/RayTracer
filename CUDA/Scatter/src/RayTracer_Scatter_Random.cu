#include "../inc/RayTracer_Scatter_Random.cuh"


// Define
// ...


// Typedef
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
__device__ Scatter_Random::Scatter_Random() {
	texture_list	= nullptr;
	texture_size	= MAX;
}


__device__ Scatter_Random::~Scatter_Random() {
}


__device__ void Scatter_Random::setRadius(fp_t radius) {
	this->radius = radius;
}


__device__ void Scatter_Random::setParallel(int8_t is_parallel) {
	this->is_parallel = is_parallel;
}


__device__ void Scatter_Random::setRaySize(uint8_t count) {
	this->count = count;
}


__device__ void Scatter_Random::scatter(RecordRay *src, MemoryControl_Scatter *memory_control) const {
	RecordHit	*record_hit	= &(src->record_hit.record);
	Vec3f 		ref_dir		= record_hit->ray.getDirection();

	// get the radius vector
	Vec3f vector_radius_1, vector_radius_2;
	
	// special case: ray vector is along with x-direction
	if (ref_dir.dot(Vec3f(1, 0, 0)) == 1) {
		vector_radius_1 = Vec3f(0, 1, 0);
		vector_radius_2 = Vec3f(0, 0, 1);

	} else {
		vector_radius_1 = ref_dir.cross(Vec3f(1, 0, 0));
		vector_radius_2 = ref_dir.cross(vector_radius_1);

		vector_radius_1.normalize();
		vector_radius_2.normalize();
	}

	for (uint8_t i = 0; i < count; ++i) {
		// set the length of the radius vectors	
		fp_t length_1 = radius * (UtilMath::randFloat(src->thread_id) - 0.5) * 2;
		fp_t length_2 = radius * (UtilMath::randFloat(src->thread_id) - 0.5) * 2;

		Vec3f	vector_radius_3	= vector_radius_1.prod(Vec3f(length_1));
		Vec3f	vector_radius_4	= vector_radius_2.prod(Vec3f(length_2));

		// configure ray position and direction
		// if new ray is parallel, then move the ray position
		// if new ray is not paralle, then move the ray direction
		Vec3f	new_pos	= record_hit->ray.getPosition();
		Vec3f	new_dir	= ref_dir;

		if (is_parallel)	new_pos += (vector_radius_3 + vector_radius_4);
		else				new_dir += (vector_radius_3 + vector_radius_4);

		// create new record
		RecordRay *record = (RecordRay*)memory_control->createRecord();
		if (record == nullptr) break;

		setRecord_tree(		record, src										);
		setRecord_ray(		record, src, Ray(new_pos, new_dir.normalize())	);
		setRecord_scatter(	record, src										);
		record->threshold = src->threshold / (fp_t)count;
	}

	// set src threshold
	// threshold should be all been used
	src->threshold = Vec3f(0);
}


// Static Function Implementation
// ...
