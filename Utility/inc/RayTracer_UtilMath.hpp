// Created by Jack Tse on 2020/07/19
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/19   initial update


#ifndef RAYTRACER_UTILMATH_HPP
#define RAYTRACER_UTILMATH_HPP


#include <cstdlib>
#include "RayTracer_Vec3f.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
// ...


// Macro Function
// ...


// Inline Function Implementation
namespace UtilMath {
	template <class T>
	const T& clamp(const T &v, const T &lo, const T &hi) {
		return (v < lo) ? lo : (hi < v) ? hi : v;
	}

	static inline double randDouble() {
		return rand() / (RAND_MAX + 1.0);
	}
}


namespace VecMath {


	static inline double dot(const Vec3f &v1, const Vec3f &v2) {
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}


	static inline Vec3f cross(const Vec3f &v1, const Vec3f &v2) {
		return Vec3f(
			v1[1] * v2[2] - v1[2] * v2[1],
			v1[2] * v2[0] - v1[0] * v2[2],
			v1[0] * v2[1] - v1[1] * v2[0]);
	}


	// reverse the vector based on the threhold
	// i.e. if dot product is smaller than the threshold
	// then reverse the vector
	static inline void reverseVector_thresholdSmaller(Vec3f &v1, const Vec3f &v2, double threshold) {
		if (v1.dot(v2) >= threshold) return;
		v1 = -v1;
	}


	// reverse the vector based on the threshold
	// i.e. if dot product is larger than the threshold
	// then reverse the vector
	static inline void reverseVector_thresholdLarger(Vec3f &v1, const Vec3f &v2, double threshold) {
		if (v1.dot(v2) <= threshold) return;
		v1 = -v1;
	}


	// reverse the vector based on the incident ray
	static inline void reverseNormal_incidentRay(Vec3f &normal, const Vec3f &ray) {
		reverseVector_thresholdLarger(normal, ray, 0);
	}


	// check if a point inside a convex polygon
	// normal is one of parameter as it is usually calculated in previous step
	static inline bool checkInside_convexPolygon(const Vec3f &point, const Vec3f *polygon, int size, const Vec3f &normal) {
		Vec3f temp;
		for (int i = 0; i < size - 1; i++) {
			temp = (polygon[i + 1] - polygon[i]).cross(point - polygon[i]);
			if (normal.dot(temp) < 0) return false;
		}

		// be careful wrapping problem
		// i.e. from last point to the first point
		temp = (polygon[0] - polygon[size - 1]).cross(point - polygon[size - 1]);
		if (normal.dot(temp) < 0) return false;
		return true;
	}


	// check if two ray has oppose direction
	// i.e. cos(theta) < 0
	static inline bool checkDirection_oppose(const Vec3f &v1, const Vec3f &v2) {
		if (v1.dot(v2) >= 0) return false;
		return true;
	}


	// TODO: future coding
	// - parallel
	// - perpendicular


}


#endif  // RAYTRACER_UTILMATH_HPP
