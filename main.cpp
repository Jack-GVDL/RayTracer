#include <iostream>
#include "RayTracer.hpp"


int main() {
	int nx = 200;
	int ny = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	// scene object
    Scene scene;
    scene.addHitable(new SceneObject_Sphere(Vec3f(0, 0, -1), 0.5, new Material()));
	scene.addHitable(new SceneObject_Sphere(Vec3f(0, 0, -1), 0.5, new Material()));

	// scatter
	Scatter_Hit			scatter_hit			= Scatter_Hit();
	Scatter_Reflection	scatter_reflection	= Scatter_Reflection();

	// camera
	Camera camera(Vec3f(-2, 2, 1), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 90, double(nx) / double(ny));

	// ray tracer
	RayTracer tracer = RayTracer(&scene, &scatter_hit);

	// shoot ray
	for (int y = ny - 1; y >= 0; y--) {
		for (int x = 0; x < nx; x++) {
			Vec3f color	= tracer.trace(&camera, x, y, 1);
			
			int ir = int(255.99 * color[0]);
			int ig = int(255.99 * color[1]);
			int ib = int(255.99 * color[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
			
		}
	}
}
