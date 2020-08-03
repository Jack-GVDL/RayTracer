// Created by Jack Tse on 2020/06/12
// Follow TrackingStandard 0.1
//
// Log
// 2020/06/12   initial update


#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP


#include "../../Utility/Utility.hpp"


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Camera {
	// Data
	private:
		Vec3f	look_from;
		Vec3f	look_at, up;
		Vec3f	w, u, v;
		double	fov, aspect;

		// backup
		// double	width, height;

	// Operation
	public:
		// init
		Camera() {
			this->look_from		= Vec3f(0.0, 0.0, 0.0);
			this->look_at		= Vec3f(0.0, 0.0, 1.0);
			this->up			= Vec3f(0.0, 1.0, 0.0);
			this->fov			= 90;
			this->aspect		= 1;

			update();
		}

		Camera(const Vec3f look_from, const Vec3f look_at, const Vec3f up, double fov, double aspect) {
			this->look_from	= look_from;
			this->look_at	= look_at;
			this->up		= up;
			this->fov		= fov;
			this->aspect	= aspect;

			update();
		}

		// getter and setter
		void 	setLookFrom		(const Vec3f look_from);
		void	setLookAt		(const Vec3f look_at, const Vec3f up_dir);
		void 	setFOV			(double value);
		void	setAspectRatio	(double value);
		void	setAll			(const Vec3f look_from, const Vec3f look_at, const Vec3f up, double fov, double aspect);

		// operation
		Ray		getRay			(double x, double y) const;

	private:
		// helper
		void	update			();
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // RAYTRACER_CAMERA_HPP
