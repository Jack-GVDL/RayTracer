#include <iostream>
#include "RayTracer.hpp"


// Data Structure
struct TraceData {
	RayTracer	*tracer;
	Camera		*camera;
	int			depth;
};


// Static Function Prototype
static Vec3f Linker_getColor(double x, double y, void *info);


// Operation
int main() {
	int nx = 200;
	int ny = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	// scene object
	Material	*material_1	= new Material();
	Material	*material_2	= new Material();
	Material	*material_3 = new Material();

	// material_1->emissive	= Vec3f(0.5, 0.5, 0);
	material_1->diffuse			= Vec3f(0.5, 0.5, 0);
	material_1->specular		= Vec3f(0.5, 0.5, 0.5);
	material_1->reflective		= Vec3f(0);
	material_1->index			= 1.5;
	material_1->transmissive	= Vec3f(0.9);
	material_1->shininess		= 0.2;

	// material_2->emissive		= Vec3f(0.5, 0.5, 0.5);
	material_2->reflective 		= Vec3f(0.1, 0.3, 0.8);

	material_3->reflective		= Vec3f(0.8, 0.3, 0.1);

    Scene scene;
	scene.addHitable(new SceneObject_Sphere(Vec3f(0, 0.5, 0), 1, material_1));
    scene.addHitable(new SceneObject_Sphere(Vec3f(1, 0, -1), 0.5, material_2));
	scene.addHitable(new SceneObject_Sphere(Vec3f(-1, 0, -1), 0.5, material_2));
	scene.addHitable(new SceneObject_Sphere(Vec3f(0, -100.5, -1), 100, material_2));

	SceneObject_Light_Point *light_point = new SceneObject_Light_Point(Vec3f(0.1, 0.1, 0.4));
	light_point->origin	= Vec3f(0, 2, -2);
	light_point->color	= Vec3f(1);
	// scene.addLight(light_point);

	SceneObject_Light_Directional *light_directional = new SceneObject_Light_Directional(Vec3f(-1, 1, -1));
	light_directional->color = Vec3f(0.8);
	scene.addLight(light_directional);

	// scatter
	Scatter				scatter_top			= Scatter();
	Scatter_RandomGrid	scatter_random		= Scatter_RandomGrid();
	Scatter_Hit			scatter_hit			= Scatter_Hit();
	Scatter_Light		scatter_light		= Scatter_Light();
	Scatter_Reflection	scatter_reflection	= Scatter_Reflection();
	Scatter_Refraction	scatter_refraction	= Scatter_Refraction();
	Scatter_Emitter		scatter_emitter		= Scatter_Emitter();

	scatter_emitter.color		= Vec3f(0.1, 0.3, 0.8);
	scatter_hit.color			= Vec3f(1, 0, 0);
	scatter_random.loop_count 	= 20;
	scatter_random.radius		= 0.01;
	scatter_random.is_parallel	= true;

	scatter_top.addChild(&scatter_random);
	scatter_random.addChild(&scatter_reflection);
	scatter_random.addChild(&scatter_refraction);
	scatter_random.addChild(&scatter_light);
	// scatter_random.addChild(&scatter_hit);

	scatter_reflection.addChild(&scatter_reflection);
	scatter_reflection.addChild(&scatter_refraction);
	scatter_reflection.addChild(&scatter_light);
	// scatter_reflection.addChild(&scatter_emitter);

	scatter_refraction.addChild(&scatter_reflection);
	scatter_refraction.addChild(&scatter_refraction);
	scatter_refraction.addChild(&scatter_light);
	// scatter_refraction.addChild(&scatter_hit);
	// scatter_refraction.addChild(&scatter_emitter);

	// camera
	Camera camera(Vec3f(-2, 0, 2), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 90, double(nx) / double(ny));

	// ray tracer
	RayTracer tracer = RayTracer(&scene, &scatter_top);

	// super sampler
	// SuperSampler_Grid		super_sampler;
	// SuperSampler_Random		super_sampler;
	SuperSampler_Jittered	super_sampler;
	super_sampler.setGridSize(3, 3);

	// shoot ray
	const double x_half = double(nx) / 2;
	const double y_half = double(ny) / 2;

	for (int y = ny - 1; y >= 0; y--) {
		for (int x = 0; x < nx; x++) {

			double u = double(x - x_half) / x_half;
			double v = double(y - y_half) / y_half;

			TraceData data;
			data.tracer	= &tracer;
			data.camera	= &camera;
			data.depth	= 5;
			Vec3f color = super_sampler.sample(Vec3f(u, v, 0), Vec3f(0.01, 0.01, 0), 0, Linker_getColor, &data);
			// Vec3f color	= tracer.trace(&camera, u, v, 5);
			
			int ir = int(255.99 * color[0]);
			int ig = int(255.99 * color[1]);
			int ib = int(255.99 * color[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
			
		}
	}
}


// Static Function Implementation
static Vec3f Linker_getColor(double x, double y, void *info) {
	const TraceData	*data	= (TraceData*)info;
	const RayTracer	*tracer	= data->tracer;
	return tracer->trace(data->camera, x, y, data->depth);
}
