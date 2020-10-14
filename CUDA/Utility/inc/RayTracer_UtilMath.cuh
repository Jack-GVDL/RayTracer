// Created by Jack Tse on 2020/07/19
// Follow TrackingStandard 0.1
//
// Log
// 2020/09/11   initial update
// 2020/10/11   add curand


#ifndef RAYTRACER_UTILMATH_CUH
#define RAYTRACER_UTILMATH_CUH


#include <curand.h>
#include <curand_kernel.h>
#include "RayTracer_Vec3f.cuh"
#include "RayTracer_Ray.cuh"
#include "RayTracer_Bounding.cuh"


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


// Operation Handling
// ...


// Inline Function Implementation
namespace UtilMath {
	template <class T>
	__device__ const T& clamp(const T &v, const T &lo, const T &hi) {
		return (v < lo) ? lo : (hi < v) ? hi : v;
	}

	__device__ static inline fp_t randFloat() {
		// return rand() / (RAND_MAX + 1.0);
		
		curandState state;
		curand_init(0, 0, 0, &state);
		return curand_uniform(&state);
	}


	// reference
	// 1. https://stackoverflow.com/questions/9718453/extract-n-most-significant-non-zero-bits-from-int-in-c-without-loops
	__device__ static inline int32_t getLeadingZero(int32_t value) {
		uint8_t count = 0;

		if ((value & 0xffff0000u) == 0) {
			count += 16;
			value <<= 16;
    	}
		if ((value & 0xff000000u) == 0) {
			count += 8;
			value <<= 8;
   		 }
		if ((value & 0xf0000000u) == 0) {
			count += 4;
			value <<= 4;
		}
		if ((value & 0xc0000000u) == 0) {
			count += 2;
			value <<= 2;
		}
		if ((value & 0x80000000u) == 0) {
			count += 1;
		}

		return 1 << count;
	}
}


namespace VecMath {

	__host__ __device__ static inline fp_t dot(const Vec3f &v1, const Vec3f &v2) {
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}


	__host__ __device__ static inline Vec3f cross(const Vec3f &v1, const Vec3f &v2) {
		return Vec3f(
			v1[1] * v2[2] - v1[2] * v2[1],
			v1[2] * v2[0] - v1[0] * v2[2],
			v1[0] * v2[1] - v1[1] * v2[0]);
	}


	// reverse the vector based on the threhold
	// i.e. if dot product is smaller than the threshold
	// then reverse the vector
	__host__ __device__ static inline void reverseVector_thresholdSmaller(Vec3f &v1, const Vec3f &v2, fp_t threshold) {
		if (v1.dot(v2) >= threshold) return;
		v1 = -v1;
	}


	// reverse the vector based on the threshold
	// i.e. if dot product is larger than the threshold
	// then reverse the vector
	__host__ __device__ static inline void reverseVector_thresholdLarger(Vec3f &v1, const Vec3f &v2, fp_t threshold) {
		if (v1.dot(v2) <= threshold) return;
		v1 = -v1;
	}


	// reverse the vector based on the incident ray
	__host__ __device__ static inline void reverseNormal_incidentRay(Vec3f &normal, const Vec3f &ray) {
		reverseVector_thresholdLarger(normal, ray, 0);
	}


	// find the intersection point of ray on a plane
	// it should be noticed that a plane can be defined by a point and a normal vector
	// reference
	// 1. https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
	__host__ __device__ static inline bool intersectPoint_rayPlane(Vec3f &point, fp_t &length, const Ray *ray, const Ray *plane) {
		Vec3f normal = plane->getDirection();
		
		// check if ray and plane are parallel
		if (abs(normal.dot(ray->getDirection())) < RAY_EPSILON) return false;

		// adjust direction of normal
		if (normal.dot(ray->getDirection()) < 0) normal = -normal;

		// find projection
		// they should be in same direction
		Vec3f projection_plane	= (plane->getPosition() - ray->getPosition()).projectOn(normal);
		Vec3f projection_ray	= ray->getDirection().projectOn(normal);
		if (projection_plane.dot(projection_ray) <= 0) return false;

		// find point and length
		point	= ray->getPosition() + (projection_plane.length() / projection_ray.length()) * ray->getDirection();
		length	= (point - ray->getPosition()).length();

		if (length < 0) return false;
		return true;

		// another approach
		// but there are some problem 
		/*
		Vec3f	plane_normal			= plane->getDirection();
		double	distance_origin_plane	= plane_normal.dot(plane->getPosition());
		double	distance_ray			= -(plane_normal.dot(ray->getPosition()) + distance_origin_plane) / plane_normal.dot(ray->getDirection());

		// get the point of intersection
		point	= ray->getPosition() + distance_ray * ray->getDirection();
		length	= distance_ray;

		// there must be intersection
		return true;
		*/
	}


	// check if a point inside a convex polygon
	// normal is one of parameter as it is usually calculated in previous step
	__host__ __device__ static inline bool checkInside_convexPolygon(const Vec3f &point, const Vec3f *polygon, int size, const Vec3f &normal) {
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
	__host__ __device__ static inline bool checkDirection_oppose(const Vec3f &v1, const Vec3f &v2) {
		if (v1.dot(v2) >= 0) return false;
		return true;
	}


	// TODO: future coding
	// - parallel
	// - perpendicular


}


#endif  // RAYTRACER_UTILMATH_CUH
