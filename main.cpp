#include <iostream>
#include "RayTracer.hpp"


int main() {
	int nx = 200;
	int ny = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	// scene object
    Scene scene;
	scene.addHitable(new SceneObject_Sphere(Vec3f(0, 0, 0), 1, new Material()));
    // scene.addHitable(new SceneObject_Sphere(Vec3f(1, 0, -1), 0.5, new Material()));
	// scene.addHitable(new SceneObject_Sphere(Vec3f(-1, 0, -1), 0.5, new Material()));
	// scene.addHitable(new SceneObject_Sphere(Vec3f(0, -100.5, -1), 100, new Material()));

	SceneObject_Light_Point *light = new SceneObject_Light_Point(Vec3f(0.1, 0.2, 0.4));
	light->origin	= Vec3f(0, 2, -2);
	light->color	= Vec3f(1, 0, 0);
	scene.addLight(light);

	// scatter
	Scatter_Empty		scatter_top			= Scatter_Empty();
	Scatter_Hit			scatter_hit			= Scatter_Hit();
	Scatter_Light		scatter_light		= Scatter_Light();
	Scatter_Reflection	scatter_reflection	= Scatter_Reflection();

	scatter_hit.color = Vec3f(1, 0, 0);
	// scatter_top.addChild(&scatter_hit);
	scatter_top.addChild(&scatter_light);
	// scatter_top.addChild(&scatter_reflection);

	// camera
	Camera camera(Vec3f(-2, 2, 0), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 90, double(nx) / double(ny));

	// ray tracer
	RayTracer tracer = RayTracer(&scene, &scatter_top);

	// shoot ray
	const double x_half = double(nx) / 2;
	const double y_half = double(ny) / 2;

	for (int y = ny - 1; y >= 0; y--) {
		for (int x = 0; x < nx; x++) {

			double u = double(x - x_half) / x_half;
			double v = double(y - y_half) / y_half;
			Vec3f color	= tracer.trace(&camera, u, v, 1);
			
			int ir = int(255.99 * color[0]);
			int ig = int(255.99 * color[1]);
			int ib = int(255.99 * color[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
			
		}
	}
}
