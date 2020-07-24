#include <iostream>
#include "../inc/RayTracer.hpp"


// Data Structure
struct TraceData {
	RayTracer	*tracer;
	Camera		*camera;
	int			depth;
};


// Static Function Prototype
static void		buildScene		(Scene *scene);
static Vec3f	Linker_getColor	(double x, double y, void *info);


// Operation
int main() {
	int nx = 200;
	int ny = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	// scene object
    Scene scene;
	buildScene(&scene);

	SceneObject_Light_Point *light_point_1 = new SceneObject_Light_Point(Vec3f(0, 0.05, 0.4));
	light_point_1->origin	= Vec3f(0, 2, 2);
	light_point_1->color	= Vec3f(1);
	scene.addLight(light_point_1);

	SceneObject_Light_Point *light_point_2 = new SceneObject_Light_Point(Vec3f(0, 0.05, 0.4));
	light_point_2->origin	= Vec3f(-2, 2, 0);
	light_point_2->color	= Vec3f(1);
	scene.addLight(light_point_2);

	SceneObject_Light_Directional *light_directional = new SceneObject_Light_Directional(Vec3f(-1, 1, -1));
	light_directional->color = Vec3f(0.8);
	scene.addLight(light_directional);

	SceneObject_Light_Ambient *light_ambient = new SceneObject_Light_Ambient();
	light_ambient->color = Vec3f(1);
	scene.addAmbientLight(light_ambient);

	// camera
	Camera camera(Vec3f(0, 0.5, 2), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 90, double(nx) / double(ny));

	// ray tracer
	RayTracer tracer = RayTracer(&scene);

	Scatter_Hit *scatter_hit = new Scatter_Hit();
	scatter_hit->multiplier = Vec3f(1, 0, 0);
	tracer.shader_hit.addScatter(scatter_hit);

	// super sampler
	// SuperSampler_Grid		super_sampler;
	// SuperSampler_Random		super_sampler;
	SuperSampler_Jittered	super_sampler;
	super_sampler.setGridSize(5, 5);

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
			Vec3f color = super_sampler.sample(Vec3f(u, v, 0), Vec3f(0.0025, 0.005, 0), 0, Linker_getColor, &data);
			// Vec3f color	= tracer.trace(&camera, u, v, 5);
			
			int ir = int(255.99 * color[0]);
			int ig = int(255.99 * color[1]);
			int ib = int(255.99 * color[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
			
		}
	}
}


// Static Function Implementation
static void buildScene(Scene *scene) {
	Shader_Diffuse *shader_diffuse_1 = new Shader_Diffuse();
	shader_diffuse_1->scatter_reflection.reflective->setPixel	(Vec3f(0.5),	Vec3f());
	shader_diffuse_1->scatter_light.ambient->setPixel			(Vec3f(0), 		Vec3f());
	shader_diffuse_1->scatter_light.diffuse->setPixel			(Vec3f(1), 		Vec3f());
	shader_diffuse_1->scatter_light.specular->setPixel			(Vec3f(1), 		Vec3f());
	shader_diffuse_1->scatter_light.shininess->setPixel			(Vec3f(1),		Vec3f());

	Shader_Diffuse *shader_diffuse_2 = new Shader_Diffuse();
	shader_diffuse_2->scatter_reflection.reflective->setPixel	(Vec3f(0),	Vec3f());
	shader_diffuse_2->scatter_light.ambient->setPixel			(Vec3f(0), 		Vec3f());
	shader_diffuse_2->scatter_light.diffuse->setPixel			(Vec3f(1), 		Vec3f());
	shader_diffuse_2->scatter_light.specular->setPixel			(Vec3f(0), 		Vec3f());
	shader_diffuse_2->scatter_light.shininess->setPixel			(Vec3f(0),		Vec3f());

	Shader_Glass *shader_glass_1 = new Shader_Glass();
	shader_glass_1->scatter_reflection.reflective->setPixel		(Vec3f(0.5), Vec3f());

	Texture_CheckerBoard *texture_checkerboard_1 = new Texture_CheckerBoard();
	texture_checkerboard_1->setBoardSize(Vec3f(10));
	shader_diffuse_2->scatter_light.diffuse = texture_checkerboard_1;

	SceneObject_Sphere *scene_sphere_1 = new SceneObject_Sphere(Vec3f(0, 0.5, 0), 0.49);
	scene_sphere_1->shader = shader_diffuse_1;
	scene->addHitable(scene_sphere_1);

	SceneObject_Sphere *scene_sphere_2 = new SceneObject_Sphere(Vec3f(0, -50.5, 0), 50);
	scene_sphere_2->shader = shader_diffuse_2;
	scene->addHitable(scene_sphere_2);

	SceneObject_Sphere *scene_sphere_3 = new SceneObject_Sphere(Vec3f(1, 0.5, 1), 0.49);
	scene_sphere_3->shader = shader_glass_1;
	scene_sphere_3->material.index = 1.5;
	scene_sphere_3->material.transmissive->setPixel(Vec3f(0.9), Vec3f());
	scene->addHitable(scene_sphere_3);

	SceneObject_Trimesh *scene_trimesh_1 = new SceneObject_Trimesh(Vec3f(0, 0, 100), Vec3f(-100, 0, -100), Vec3f(100, 0, -100));
	scene_trimesh_1->shader = shader_diffuse_2;
	// scene->addHitable(scene_trimesh_1);
}


static Vec3f Linker_getColor(double x, double y, void *info) {
	const TraceData	*data	= (TraceData*)info;
	const RayTracer	*tracer	= data->tracer;
	return tracer->trace(data->camera, x, y, data->depth);
}
