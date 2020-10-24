// Created by Jack Tse on 2020/09/02
//
// Log
// 2020/09/11   initial update


#ifndef RAYTRACER_BOUNDING_CUH
#define RAYTRACER_BOUNDING_CUH


#include "RayTracer_Vec3f.cuh"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Bounding {
	// Data
	public:
		Vec3f	min_	= Vec3f(1);
		Vec3f	max_	= Vec3f(-1);
	
	// Operation
	public:
		// init
		__host__ __device__ Bounding() {}

		__host__ __device__ Bounding(const Vec3f &min_, const Vec3f &max_)
		{
			setBounding(min_, max_);
		}

		__host__ __device__ Bounding(const Bounding &b):
		min_(b.min_), max_(b.max_)
		{}

		// operation
		__host__ __device__ bool isEmpty() const {
			return min_[0] > max_[0];
		}

		__host__ __device__ bool isIntersect(const Bounding &bounding) const {
			if (isEmpty()) return false;

			for (uint8_t i = 0; i < 3; i++) {
				if (min_[i] < bounding.max_[i] && max_[i] > bounding.min_[i]) continue;
				return false;
			}
			return true;
		}

		__host__ __device__ bool isIntersect(const Vec3f &point) const {
			if (isEmpty()) return false;
			
			for (uint8_t i = 0; i < 3; i++) {
				if (min_[i] <= point[i] && point[i] <= max_[i]) continue;
				return false;
			}
			return true;
		}

		__host__ __device__ void setEmpty() {
			min_	= Vec3f(1);
			max_	= Vec3f(-1);
		}

		__host__ __device__ void setBounding(const Vec3f &min_, const Vec3f &max_) {
			for (uint8_t i = 0; i < 3; ++i) {

				if (min_[i] <= max_[i]) {
					this->min_[i]	= min_[i];
					this->max_[i]	= max_[i];
				} else {
					this->min_[i]	= max_[i];
					this->max_[i]	= min_[i];
				}

			}
		}

		__host__ __device__ void unionBounding(const Bounding &bounding) {
			// when input bounding is empty
			if (bounding.isEmpty()) return;

			// when input bounding will be the first bounding in the list
			if (isEmpty()) {
				*this = bounding;
				return;
			}

			for (uint8_t i = 0; i < 3; ++i) {
				min_[i]	= min<fp_t>(min_[i], bounding.min_[i]);
				max_[i]	= max<fp_t>(max_[i], bounding.max_[i]);
			}
		}

		__host__ __device__ void unionBounding(const Vec3f &point) {
			if (isEmpty()) {
				min_ = point;
				max_ = point;
				return;
			}

			for (uint8_t i = 0; i < 3; ++i) {
				min_[i]	= min<fp_t>(min_[i], point[i]);
				max_[i]	= max<fp_t>(max_[i], point[i]);
			}
		}
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_BOUNDING_CUH
