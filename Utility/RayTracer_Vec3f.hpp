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


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Vec3f {
	// Data
	public:
		double n[3];

	// Operation
	public:
		// Init
		Vec3f() { 
			n[0] = 0.0; 
			n[1] = 0.0; 
			n[2] = 0.0;
		}

		Vec3f(double n0, double n1, double n2) {
			n[0] = n0; 
			n[1] = n1; 
			n[2] = n2;
		}

		Vec3f(const Vec3f &v) {
			n[0] = v.n[0];
			n[1] = v.n[1];
			n[2] = v.n[2];
		}

		// Operator
		double			operator	[]	( int i )			const { return n[i]; }
		double&			operator	[]	( int i )			{ return n[i]; }

		const Vec3f&	operator	+	()					const { return *this; }
		Vec3f			operator	-	()					const { return Vec3f(-n[0], -n[1], -n[2]); }

		Vec3f&			operator	=	( const Vec3f &v )	{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[2]; return *this; }
		Vec3f&			operator	+=	( const Vec3f &v )	{ n[0] += v.n[0]; n[1] += v.n[1]; n[2] += v.n[2]; return *this; }
		Vec3f&			operator	-=	( const Vec3f &v )	{ n[0] -= v.n[0]; n[1] -= v.n[1]; n[2] -= v.n[2]; return *this; }
		Vec3f&			operator	*=	( const Vec3f &v )	{ n[0] *= v.n[0]; n[1] *= v.n[1]; n[2] *= v.n[2]; return *this; }
		Vec3f&			operator	/=	( const Vec3f &v )	{ n[0] /= v.n[0]; n[1] /= v.n[1]; n[2] /= v.n[2]; return *this; }

		Vec3f&			operator	*=	( const double d )	{ n[0] *= d; n[1] *= d; n[2] *= d; return *this; }
		Vec3f&			operator	/=	( const double d )	{ n[0] /= d; n[1] /= d; n[2] /= d; return *this; }

		// Math Operation
		// TODO: clamp (0.0 <= n[i] <= 1.0)

		bool isZero() const {
			return n[0] == 0 && n[1] == 0 && n[2] == 0;
		}

		Vec3f cross(const Vec3f &v) const {
			return Vec3f(
			n[1] * v[2] - n[2] * v[1],
			n[2] * v[0] - n[0] * v[2],
			n[0] * v[1] - n[1] * v[0] );
		}

		double dot(const Vec3f &v) const {
			return n[0] * v[0] + n[1] * v[1] + n[2] * v[2];
		}

		Vec3f normalize() const {
			Vec3f ret (*this);
			ret /= length();
			return ret;
		}

		double length_squared() const {
			return n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
		} 

		double length() const {
			sqrt(length_squared());
		}
};


// Macro Function
// ...


// Inline Function Implementation
inline std::istream& operator>>(std::istream &is, Vec3f &v) {
	is >> v[0] >> v[1] >> v[2];
	return is;
}


inline std::ostream& operator<<(std::ostream &os, const Vec3f &v) {
	os << v[0] << " " << v[1] << " " << v[2];
	return os;
}


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


inline Vec3f operator*(float t, const Vec3f &v) {
	return Vec3f(t * v[0], t * v[1], t * v[2]);
}


inline Vec3f operator/(Vec3f v, float t) {
	return Vec3f(v[0] / t, v[1] /  t, v[2] / t);
}


inline Vec3f operator*(const Vec3f &v, float t) {
	return Vec3f(t * v[0], t * v[1], t * v[2]);
}


namespace RayTracer {

	inline double dot(const Vec3f &v1, const Vec3f &v2) {
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}


	inline Vec3f cross(const Vec3f &v1, const Vec3f &v2) {
		return Vec3f(
			v1[1] * v2[2] - v1[2] * v2[1],
			v1[2] * v2[0] - v1[0] * v2[2],
			v1[0] * v2[1] - v1[1] * v2[0] );
	}

}


#endif  // RAYTRACER_VEC3F_HPP
