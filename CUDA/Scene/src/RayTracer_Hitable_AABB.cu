#include "../inc/RayTracer_Hitable_AABB.cuh"


// Define
// TODO: fixed number: change to dynamic
#define MAX_LIST_SIZE_RECORD	24


// Typedef
typedef int32_t(*compare_func_t)(const void*, const void*);


// Data Structure
struct RecordAABB {
	const AABB	*aabb;
	int8_t		state;
};


// Static Function Prototype
// ...


// Operation Handling
__device__ Hitable_AABB::Hitable_AABB() {
}


__device__ Hitable_AABB::~Hitable_AABB() {
}


__device__ void Hitable_AABB::setAABB(AABB *aabb) {
	this->root = aabb;
}


// only return hit child and never return self
// TODO: need to split the part
__device__ int8_t Hitable_AABB::hit(RecordHit *record, fp_t t_min, fp_t t_max) const {
	// iterative
	// variable preparation
	int8_t		is_hit		= 0;

	RecordAABB	stack_aabb[MAX_LIST_SIZE_RECORD];
	int8_t		index_aabb	= 0;

	RecordAABB	*cur;
	const AABB	*aabb;
	RecordHit	temp_record;

	// variable configuration
	stack_aabb[index_aabb].aabb		= root;
	stack_aabb[index_aabb].state	= 0;
	
	temp_record.ray					= record->ray;

	// loop until entire tree is searched
	while (index_aabb != -1) {

		cur		= stack_aabb + index_aabb;
		aabb	= cur->aabb;

		if (aabb == nullptr) {
			--index_aabb;
			continue;
		}

		// TODO: may use static inline to separate this long function
		// leaf
		if (aabb->getIsLeaf()) {
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
		switch (cur->state) {

			// not visit
			case 0: {
				// if not hit, then reduce by one level
				// else push to next level (visit left)
				if (!aabb->hit(record, t_min, t_max)) {
					--index_aabb;
					goto NOT_VISIT_END;
				}

				// to right
				if (aabb->aabb_left == nullptr) {
					++index_aabb;
					cur->state = 2;

					stack_aabb[index_aabb].aabb		= aabb->aabb_right;
					stack_aabb[index_aabb].state	= 0;

					goto NOT_VISIT_END;
				}
					
				// to left
				++index_aabb;
				cur->state = 1;

				stack_aabb[index_aabb].aabb		= aabb->aabb_left;
				stack_aabb[index_aabb].state	= 0;

				NOT_VISIT_END: {}
				break;
			}

			// visited left, next is to visit right
			case 1: {
				if (aabb->aabb_right == nullptr) {
					--index_aabb;
					goto VISITED_LEFT_END;
				}

				++index_aabb;
				cur->state = 2;
				
				stack_aabb[index_aabb].aabb		= aabb->aabb_right;
				stack_aabb[index_aabb].state	= 0;

				VISITED_LEFT_END: {}
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
