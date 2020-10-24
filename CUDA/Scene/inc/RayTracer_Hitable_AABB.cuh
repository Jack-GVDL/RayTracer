// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/23   initial update


#ifndef RAYTRACER_HITABLE_AABB_CUH
#define RAYTRACER_HITABLE_AABB_CUH


#include "RayTracer_SceneObject_Hitable.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class AABB {
	// Data
	public:
		AABB				*aabb_left		= nullptr;
		AABB				*aabb_right		= nullptr;

		SceneObject_Hitable	*hitable_left	= nullptr;
		SceneObject_Hitable *hitable_right	= nullptr;

		Bounding			bounding;

	// Operation
	public:
		// init
		__device__ AABB() {
			update();
		}

		__device__ AABB(AABB *aabb_left, AABB *aabb_right, SceneObject_Hitable *hitable_left, SceneObject_Hitable *hitable_right):
		aabb_left(aabb_left),
		aabb_right(aabb_right),
		hitable_left(hitable_left),
		hitable_right(hitable_right)
		{
			update();
		}

		// getter
		__device__ int8_t getIsLeaf() const {
			return hitable_left != nullptr || hitable_right != nullptr ? 1 : 0;
		}

		// operation
		__device__ void setAABB_left(AABB *aabb) {
			aabb_left = aabb;
			update();
		}

		__device__ void setAABB_right(AABB *aabb) {
			aabb_right = aabb;
			update();
		}

		__device__ void setHitable_left(SceneObject_Hitable *hitable) {
			hitable_left = hitable;
			update();
		}

		__device__ void setHitable_right(SceneObject_Hitable *hitable) {
			hitable_right = hitable;
			update();
		}

		// TODO: may make hit() into an interface
		// TODO: find a better way to show the below statement
		// only check if self is hit or not
		// not check if child is hit or not
		__device__ int8_t hit(RecordHit *record, fp_t *t_min, fp_t *t_max) const {
			const Vec3f	ray_pos	= record->ray.getPosition();
			const Vec3f	ray_dir	= record->ray.getDirection();

			fp_t temp_min = *t_min;
			fp_t temp_max = *t_max;

			for (uint8_t i = 0; i < 3; ++i) {
				
				fp_t	inv_d	= 1.0 / ray_dir[i];
				fp_t	t0		= (bounding.min_[i] - ray_pos[i]) * inv_d;
				fp_t	t1		= (bounding.max_[i] - ray_pos[i]) * inv_d;

				// swap
				if (inv_d < 0.0) {
					fp_t temp = t0;
					t0 = t1;
					t1 = temp;
				}

				temp_min	= t0 > temp_min ? t0 : temp_min;
				temp_max	= t1 < temp_max ? t1 : temp_max;

				if (temp_max <= temp_min) return 0;
			}

			*t_min = temp_min;
			*t_max = temp_max;

			return 1;
		}

	protected:
		__device__ void update() {
			bounding.setEmpty();
			if (aabb_left != nullptr)		bounding.unionBounding(aabb_left->bounding);
			if (aabb_right != nullptr)		bounding.unionBounding(aabb_right->bounding);
			if (hitable_left != nullptr)	bounding.unionBounding(hitable_left->bounding);
			if (hitable_right != nullptr)	bounding.unionBounding(hitable_right->bounding);
		}
};


class Hitable_AABB: public SceneObject_Hitable {
	// Static Function
	public:
		// TODO: remove
		// TODO: static -> member function
		// static Hitable_AABB*	create	(SceneObject_Hitable* *list, int32_t size_list, int32_t size_leaf);

	// Data
	public:
		AABB		*aabb;

		// TODO: remove
		// std::vector<SceneObject_Hitable*>	hitable_list;

	// Operation
	public:
		// init
		__device__	Hitable_AABB	();
		__device__	~Hitable_AABB	();

		// operation
		__device__ void	setAABB		(AABB *aabb);

		// backup
		/*
		__device__ error_t	load			(SceneObject_Hitable *hitable_list, int32_t size);
		__device__ error_t	dump			();
		*/

		// interface
		__device__ virtual int8_t	hit				(RecordHit *record, fp_t t_min, fp_t t_max) const override;
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_HITABLE_AABB_CUH
