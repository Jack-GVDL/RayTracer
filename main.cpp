#include <iostream>
#include "RayTracer_Vec3f.hpp"
#include "RayTracer_Ray.hpp"
#include "RayTracer_SceneObject_Sphere.hpp"
#include "RayTracer_Camera.hpp"
#include "RayTracer_Material.hpp"



Vec3f color(const Ray& r, Hitable *world, int depth) {
	HitRecord record;

	if (world->hit(r, 0.001, MAXFLOAT, record)) {
		Ray		scattered;
		Vec3f	attenuation;
		if (depth < 50 && record.material->scatter(r, record, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		} else {
			return Vec3f(0, 0, 0);
		}
	} else {
		Vec3f unit_direction = r.getDirection().normalize();
		float t = 0.5 * (unit_direction[1] + 1.0);
		return (1.0 - t) * Vec3f(1.0, 1.0, 1.0) + t * Vec3f(0.5, 0.7, 1.0);
	}

}


int main() {
	int nx = 200;
	int ny = 100;
	int ns = 50;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	// scene object
	Hitable *list[5];
	list[0] = new SceneObject_Sphere(Vec3f(0, 0, -1), 0.5, new Material_Empty(Vec3f(0.0, 0.0, 0.0)));
	list[0] = new SceneObject_Sphere(Vec3f(0, 0, -1), 0.5, new Material_Lambertian(Vec3f(0.8, 0.3, 0.3)));
	list[1] = new SceneObject_Sphere(Vec3f(0, -100.5, -1), 100, new Material_Lambertian(Vec3f(0.8, 0.8, 0.0)));
	list[2] = new SceneObject_Sphere(Vec3f(1, 0, -1), 0.5, new Material_Metal(Vec3f(0.8, 0.6, 0.2), 0.3));
	list[3] = new SceneObject_Sphere(Vec3f(-1, 0, -1), 0.5, new Material_Dielectric(1.5));
	list[4] = new SceneObject_Sphere(Vec3f(-1, 0, -1), -0.45, new Material_Dielectric(1.5));
	Hitable *world = new HitableList(list, 5);

	// test for camera fov and aspect
	// float R = cos(M_PI / 4);
	// list[0] = new SceneObject_Sphere(Vec3f(-R, 0, -1), R, new Material_Lambertian(Vec3f(0, 0, 1)));
	// list[1] = new SceneObject_Sphere(Vec3f(R, 0, -1), R, new Material_Lambertian(Vec3f(1, 0, 0)));
	// Hitable *world = new HitableList(list, 2);

	// camera
	Camera camera(Vec3f(-2, 2, 1), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 90, double(nx) / double(ny));

	// shoot ray
	double x_half = double(nx) / 2;
	double y_half = double(ny) / 2;
	for (int y = ny - 1; y >= 0; y--) {
		for (int x = 0; x < nx; x++) {
			
			// super sampling
			Vec3f col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				double u = double(x - x_half + drand48()) / x_half;
				double v = double(y - y_half + drand48()) / y_half;

				Ray		r	= camera.getRay(u, v);
				Vec3f	p	= r.pointAt(2.0);
				
				col	+= color(r, world, 0);
			}

			col /= float(ns);
			col = Vec3f(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
			
		}
	}
}
