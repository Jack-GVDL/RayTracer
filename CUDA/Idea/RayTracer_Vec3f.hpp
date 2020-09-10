// Created by Jack Tse on 2020/06/09
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/09   initial update


#ifndef RAYTRACER_VEC3F_HPP
#define RAYTRACER_VEC3F_HPP


#include <iostream>
#include <cmath>
#include <algorithm>
#include "RayTracer_Base.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Vec3f {
	// Static Data
	public:
		const static Vec3f vec_one;
		const static Vec3f vec_zero;

	// Data
	public:
		fp_t n[3];

	// Operation
	public:
		// init
		Vec3f() { 
			n[0] = 0.0; 
			n[1] = 0.0; 
			n[2] = 0.0;
		}

		Vec3f(fp_t n0) {
			n[0] = n0;
			n[1] = n0;
			n[2] = n0;
		}

		Vec3f(fp_t n0, fp_t n1, fp_t n2) {
			n[0] = n0; 
			n[1] = n1; 
			n[2] = n2;
		}

		Vec3f(const Vec3f &v) {
			n[0] = v.n[0];
			n[1] = v.n[1];
			n[2] = v.n[2];
		}

		// operator
		fp_t			operator	[]	( int i )			const { return n[i]; }
		fp_t&			operator	[]	( int i )			{ return n[i]; }

		const Vec3f&	operator	+	()					const { return *this; }
		Vec3f			operator	-	()					const { return Vec3f(-n[0], -n[1], -n[2]); }

		Vec3f&			operator	=	( const Vec3f &v )	{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[2]; return *this; }
		Vec3f&			operator	+=	( const Vec3f &v )	{ n[0] += v.n[0]; n[1] += v.n[1]; n[2] += v.n[2]; return *this; }
		Vec3f&			operator	-=	( const Vec3f &v )	{ n[0] -= v.n[0]; n[1] -= v.n[1]; n[2] -= v.n[2]; return *this; }
		Vec3f&			operator	*=	( const Vec3f &v )	{ n[0] *= v.n[0]; n[1] *= v.n[1]; n[2] *= v.n[2]; return *this; }
		Vec3f&			operator	/=	( const Vec3f &v )	{ n[0] /= v.n[0]; n[1] /= v.n[1]; n[2] /= v.n[2]; return *this; }

		Vec3f&			operator	*=	( const fp_t d )	{ n[0] *= d; n[1] *= d; n[2] *= d; return *this; }
		Vec3f&			operator	/=	( const fp_t d )	{ n[0] /= d; n[1] /= d; n[2] /= d; return *this; }

		// Math Operation
		// TODO: clamp (0.0 <= n[i] <= 1.0)

		Vec3f clamp(fp_t val_min, fp_t val_max) const {
			return Vec3f(
				std::max(val_min, std::min(n[0], val_max)),
				std::max(val_min, std::min(n[1], val_max)),
				std::max(val_min, std::min(n[2], val_max)));
		}

		bool isZero() const {
			return n[0] == 0 && n[1] == 0 && n[2] == 0;
		}

		Vec3f cross(const Vec3f &v) const {
			return Vec3f(
			n[1] * v[2] - n[2] * v[1],
			n[2] * v[0] - n[0] * v[2],
			n[0] * v[1] - n[1] * v[0] );
		}

		fp_t dot(const Vec3f &v) const {
			return n[0] * v[0] + n[1] * v[1] + n[2] * v[2];
		}

		Vec3f prod(const Vec3f &v) const {
			return Vec3f(n[0] * v[0], n[1] * v[1], n[2] * v[2]);
		}

		// reference
		// 1. https://en.wikipedia.org/wiki/Vector_projection
		fp_t projectLength(const Vec3f &v) const {
			fp_t dot_result	= dot(v);
			fp_t length_v2	= v.lengthSquared();
			return dot_result / length_v2;
		}

		// reference
		// 1. https://en.wikipedia.org/wiki/Vector_projection
		// projection of a on b = a.dot(b) / b.lengthSquared() * b
		Vec3f projectOn(const Vec3f &v) const {
			fp_t length		= projectLength(v);
			return Vec3f(length * v[0], length * v[1], length * v[2]);
		}

		Vec3f normalize() const {
			Vec3f ret (*this);
			ret /= length();
			return ret;
		}

		fp_t length() const {
			return sqrt(lengthSquared());
		}

		fp_t lengthSquared() const {
			return n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
		}
};


// Macro Function
// ...


// Inline Function Implementation
// inline std::istream& operator>>(std::istream &is, Vec3f &v) {
// 	is >> v[0] >> v[1] >> v[2];
// 	return is;
// }


// inline std::ostream& operator<<(std::ostream &os, const Vec3f &v) {
// 	os << v[0] << " " << v[1] << " " << v[2];
// 	return os;
// }


inline Vec3f operator+(const Vec3f &v1, const Vec3f &v2) {
	return Vec3f(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}


inline Vec3f operator-(const Vec3f &v1, const Vec3f &v2) {
	return Vec3f(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}


inline Vec3f operator*(const Vec3f &v1, const Vec3f &v2) {
	return Vec3f(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}


inline Vec3f operator/(const Vec3f &v1, const Vec3f &v2) {
	return Vec3f(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}


inline Vec3f operator*(fp_t t, const Vec3f &v) {
	return Vec3f(t * v[0], t * v[1], t * v[2]);
}


inline Vec3f operator/(Vec3f v, fp_t t) {
	return Vec3f(v[0] / t, v[1] /  t, v[2] / t);
}


inline Vec3f operator*(const Vec3f &v, fp_t t) {
	return Vec3f(t * v[0], t * v[1], t * v[2]);
}


inline bool operator==(const Vec3f &v1, const Vec3f &v2) {
	return v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2];
}


#endif  // RAYTRACER_VEC3F_HPP
