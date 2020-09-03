// Created by Jack Tse on 2020/09/02
//
// Log
// 2020/09/02   initial update


#ifndef RAYTRACER_BOUNDING_HPP
#define RAYTRACER_BOUNDING_HPP


#include "RayTracer_Vec3f.hpp"


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
		Vec3f	min = Vec3f(1);
		Vec3f	max	= Vec3f(-1);
	
	// Operation
	public:
		// init
		Bounding() {}

		Bounding(const Vec3f &min, const Vec3f &max)
		{
			setBounding(min, max);
		}

		Bounding(const Bounding &b):
		min(b.min), max(b.max)
		{}

		// operation
		bool isEmpty() const {
			return min[0] > max[0];
		}

		bool isIntersect(const Bounding &bounding) const {
			if (isEmpty()) return false;

			for (uint8_t i = 0; i < 3; i++) {
				if (min[i] < bounding.max[i] && max[i] > bounding.min[i]) continue;
				return false;
			}
			return true;
		}

		bool isIntersect(const Vec3f &point) const {
			if (isEmpty()) return false;
			
			for (uint8_t i = 0; i < 3; i++) {
				if (min[i] <= point[i] && point[i] <= max[i]) continue;
				return false;
			}
			return true;
		}

		void setBounding(const Vec3f &min, const Vec3f &max) {
			for (uint8_t i = 0; i < 3; i++) {

				if (min[i] <= max[i]) {
					this->min[i]	= min[i];
					this->max[i]	= max[i];
				} else {
					this->min[i]	= max[i];
					this->max[i]	= min[i];
				}

			}
		}

		void unionBounding(const Bounding &bounding) {
			// when input bounding is empty
			if (bounding.isEmpty()) return;

			// when input bounding will be the first bounding in the list
			if (isEmpty()) {
				*this = bounding;
				return;
			}

			for (uint8_t i = 0; i < 3; i++) {
				min[i]	= std::min<fp_t>(min[i], bounding.min[i]);
				max[i]	= std::max<fp_t>(max[i], bounding.max[i]);
			}
		}

		void unionBounding(const Vec3f &point) {
			if (isEmpty()) {
				min = point;
				max = point;
				return;
			}

			for (uint8_t i = 0; i < 3; i++) {
				min[i]	= std::min<fp_t>(min[i], point[i]);
				max[i]	= std::max<fp_t>(max[i], point[i]);
			}
		}
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_BOUNDING_HPP
