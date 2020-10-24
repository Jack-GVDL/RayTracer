#include "../inc/RayTracer_Hitable_AABB.cuh"


// Define
#define MAX_LIST_SIZE_RECORD	32


// Typedef
typedef int32_t(*compare_func_t)(const void*, const void*);


// Data Structure
struct RecordAABB {
	const AABB	*aabb;
	int8_t		state;
	fp_t		t_max;
};


// Static Function Prototype
// ...


// Operation Handling
__device__ Hitable_AABB::Hitable_AABB() {
}


__device__ Hitable_AABB::~Hitable_AABB() {
}


__device__ void Hitable_AABB::setAABB(AABB *aabb) {
	this->aabb = aabb;
}


// backup
/*
__device__ error_t Hitable_AABB::load(SceneObject_Hitable *hitable_list, int32_t size) {
	return ERROR_NO;
}


// TODO: not yet completed
__device__ error_t Hitable_AABB::dump() {
	return ERROR_ANY;
}
*/


// only return hit child and never return self
__device__ int8_t Hitable_AABB::hit(RecordHit *record, fp_t t_min, fp_t t_max) const {
	// iterative
	RecordAABB	stack_aabb[MAX_LIST_SIZE_RECORD];
	int8_t		index_aabb = 0;

	stack_aabb[index_aabb].aabb		= aabb;
	stack_aabb[index_aabb].state	= 0;
	stack_aabb[index_aabb].t_max	= t_max;

	int8_t is_hit = 0;
	while (index_aabb != -1) {

		RecordAABB	*cur	= stack_aabb + index_aabb;
		const AABB	*aabb	= cur->aabb;

		if (aabb == nullptr) {
			--index_aabb;
			continue;
		}

		// TODO: may use static inline to separate this long function
		// leaf
		if (aabb->getIsLeaf()) {
			RecordHit	temp_record;

			// left hitable
			if (aabb->hitable_left != nullptr && 
				aabb->hitable_left->hit(&temp_record, t_min, t_max)) {

				is_hit	= 1;
				t_max	= temp_record.distance;
				*record	= temp_record;
			}

			// right hitable
			if (aabb->hitable_right != nullptr && 
				aabb->hitable_right->hit(&temp_record, t_min, t_max)) {

				is_hit	= 1;
				t_max	= temp_record.distance;
				*record	= temp_record;
			}

			--index_aabb;
			continue;
		}

		// not leaf
		fp_t temp_max = cur->t_max;
		switch (cur->state) {

			// not visit
			case 0: {
				// if not hit, then reduce by one level
				// else push to next level (visit left)
				if (!aabb->hit(record, &t_min, &temp_max)) {
					--index_aabb;
					goto NOT_VISIT_END;
				}
					
				cur->state = 1;
				++index_aabb;

				stack_aabb[index_aabb].aabb		= aabb->aabb_left;
				stack_aabb[index_aabb].state	= 0;
				stack_aabb[index_aabb].t_max	= temp_max;

				NOT_VISIT_END: {break;}
			}

			// visited left, next is to visit right
			case 1: {
				cur->state = 2;
				++index_aabb;
				
				stack_aabb[index_aabb].aabb		= aabb->aabb_right;
				stack_aabb[index_aabb].state	= 0;
				stack_aabb[index_aabb].t_max	= temp_max;
				break;
			}

			// visited right, next is to reduce by one level
			case 2: {
				--index_aabb;
				break;
			}
		}
	}

	return is_hit;
}


// Static Function Implementation
// ...
