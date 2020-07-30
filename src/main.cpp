#include <iostream>
#include "../Tracer/Tracer.hpp"


// Data Structure
struct TraceData {
	RayTracer	*tracer;
	Camera		*camera;
	int			depth;
};


// Static Function Prototype
// static void		buildScene				(Scene *scene);
static void		buildScene_imageTexture	(Scene *scene);
static Vec3f	Linker_getColor			(double x, double y, void *info);


// Operation
int main() {
	int nx = 200;
	int ny = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	// scene object
    Scene scene;
	// buildScene(&scene);
	buildScene_imageTexture(&scene);

	SceneObject_Light_Point *light_point_1 = new SceneObject_Light_Point(Vec3f(0, 0.05, 0.1));
	light_point_1->origin	= Vec3f(0, 0.5, 1);
	light_point_1->color	= Vec3f(1);
	scene.addLight(light_point_1);

	SceneObject_Light_Point *light_point_2 = new SceneObject_Light_Point(Vec3f(0, 0.05, 0.4));
	light_point_2->origin	= Vec3f(-2, 2, 0);
	light_point_2->color	= Vec3f(1);
	// scene.addLight(light_point_2);

	SceneObject_Light_Directional *light_directional = new SceneObject_Light_Directional(Vec3f(0, 0, -1));
	light_directional->color = Vec3f(1);
	// scene.addLight(light_directional);

	SceneObject_Light_Ambient *light_ambient = new SceneObject_Light_Ambient();
	light_ambient->color = Vec3f(1);
	// scene.addAmbientLight(light_ambient);

	// camera
	Camera camera(Vec3f(0, 0.5, 2), Vec3f(0, 0.5, 0), Vec3f(0, 1, 0), 90, double(nx) / double(ny));

	// ray tracer
	RayTracer tracer = RayTracer(&scene);

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
// static void buildScene(Scene *scene) {
// 	Shader_Diffuse *shader_diffuse_1 = new Shader_Diffuse();
// 	shader_diffuse_1->scatter_reflection.reflective->setPixel	(Vec3f(0),		Vec3f(0.5));
// 	shader_diffuse_1->scatter_light.ambient->setPixel			(Vec3f(0), 		Vec3f(0));
// 	shader_diffuse_1->scatter_light.diffuse->setPixel			(Vec3f(0), 		Vec3f(1));
// 	shader_diffuse_1->scatter_light.specular->setPixel			(Vec3f(0), 		Vec3f(1));
// 	shader_diffuse_1->scatter_light.shininess->setPixel			(Vec3f(0),		Vec3f(1));

// 	Shader_Diffuse *shader_diffuse_2 = new Shader_Diffuse();
// 	shader_diffuse_2->scatter_reflection.reflective->setPixel	(Vec3f(0),		Vec3f(0));
// 	shader_diffuse_2->scatter_light.ambient->setPixel			(Vec3f(0), 		Vec3f(0));
// 	shader_diffuse_2->scatter_light.diffuse->setPixel			(Vec3f(0), 		Vec3f(1));
// 	shader_diffuse_2->scatter_light.specular->setPixel			(Vec3f(0), 		Vec3f(0));
// 	shader_diffuse_2->scatter_light.shininess->setPixel			(Vec3f(0),		Vec3f(0));

// 	Shader_Diffuse *shader_diffuse_3 = new Shader_Diffuse();
// 	shader_diffuse_3->scatter_reflection.reflective->setPixel	(Vec3f(0),		Vec3f(0));
// 	shader_diffuse_3->scatter_light.emissive->setPixel			(Vec3f(0),		Vec3f(1));
// 	shader_diffuse_3->scatter_light.ambient->setPixel			(Vec3f(0), 		Vec3f(0));
// 	shader_diffuse_3->scatter_light.diffuse->setPixel			(Vec3f(0), 		Vec3f(0));
// 	shader_diffuse_3->scatter_light.specular->setPixel			(Vec3f(0), 		Vec3f(0));
// 	shader_diffuse_3->scatter_light.shininess->setPixel			(Vec3f(0),		Vec3f(0));

// 	Shader_Glass *shader_glass_1 = new Shader_Glass();
// 	shader_glass_1->scatter_reflection.reflective->setPixel		(Vec3f(0), 		Vec3f(0.5));

// 	Shader *shader_custom_1 = new Shader();

// 	Scatter_Gradient *scatter_gradient_1 = new Scatter_Gradient();
// 	scatter_gradient_1->source		= Scatter_Gradient::GradientSource::POSITION;
// 	scatter_gradient_1->additor		= Vec3f(4);
// 	scatter_gradient_1->multiplier	= Vec3f(0.25);
// 	shader_custom_1->addScatter(scatter_gradient_1);

// 	Texture_CheckerBoard *texture_checkerboard_1 = new Texture_CheckerBoard();
// 	texture_checkerboard_1->setBoardSize(Vec3f(5));
// 	shader_diffuse_2->scatter_light.diffuse = texture_checkerboard_1;

// 	Texture_Gradient *texture_gradient_1 = new Texture_Gradient();
// 	texture_gradient_1->additor		= Vec3f(5, 5, 0);
// 	texture_gradient_1->multiplier	= Vec3f(0.1);
// 	shader_diffuse_3->scatter_light.emissive = texture_gradient_1;

// 	SceneObject_Sphere *scene_sphere_1 = new SceneObject_Sphere(Vec3f(0, 0.5, 0), 0.49);
// 	scene_sphere_1->shader = shader_diffuse_1;
// 	// scene->addHitable(scene_sphere_1);

// 	SceneObject_Sphere *scene_sphere_2 = new SceneObject_Sphere(Vec3f(0, -51, 0), 50);
// 	scene_sphere_2->shader = shader_diffuse_2;
// 	scene->addHitable(scene_sphere_2);

// 	SceneObject_Sphere *scene_sphere_3 = new SceneObject_Sphere(Vec3f(0.5, 0.5, 1), 0.49);
// 	scene_sphere_3->shader = shader_glass_1;
// 	scene_sphere_3->material.index = 1.5;
// 	scene_sphere_3->material.transmissive->setPixel(Vec3f(0), Vec3f(0.9));
// 	scene->addHitable(scene_sphere_3);
// }


static void buildScene_imageTexture(Scene *scene) {
	// image texture
	File_BMP file_bmp = File_BMP();
	// file_bmp.read("../img/checkerboard.bmp");
	file_bmp.read("../img/IWS2000.bmp");

	Surface_BMP surface_bmp = Surface_BMP();
	surface_bmp.setBMP(&file_bmp);
	surface_bmp.load();

	Texture_Image *texture_image = new Texture_Image();
	surface_bmp.convertToTexture(texture_image);

	Mapper_Additor *mapper_add_1 = new Mapper_Additor();
	mapper_add_1->additor = Vec3f(2, 1, 0);
	texture_image->addMapper(mapper_add_1);
	
	Mapper_Multiplier *mapper_multi_1 = new Mapper_Multiplier();
	mapper_multi_1->multiplier = Vec3f(500);
	texture_image->addMapper(mapper_multi_1);

	// contant texture
	Texture_Constant *texture_reflective	= new Texture_Constant();
	Texture_Constant *texture_emissive		= new Texture_Constant();
	Texture_Constant *texture_ambient		= new Texture_Constant();
	Texture_Constant *texture_diffuse		= new Texture_Constant();
	Texture_Constant *texture_specular		= new Texture_Constant();
	Texture_Constant *texture_shininess		= new Texture_Constant();

	texture_reflective->setPixel	(Vec3f(),		Vec3f(0.1));
	texture_emissive->setPixel		(Vec3f(),		Vec3f(0));
	texture_ambient->setPixel		(Vec3f(), 		Vec3f(0));
	texture_diffuse->setPixel		(Vec3f(), 		Vec3f(0));
	texture_specular->setPixel		(Vec3f(), 		Vec3f(0));
	texture_shininess->setPixel		(Vec3f(),		Vec3f(0));

	// set scatter
	Scatter_Reflection *scatter_reflection_1 = new Scatter_Reflection();
	scatter_reflection_1->setTexture(texture_reflective, Scatter_Reflection::REFLECTIVE);

	Scatter_Light *scatter_light_1 = new Scatter_Light();
	scatter_light_1->setTexture(texture_emissive,	Scatter_Light::EMISSIVE);
	scatter_light_1->setTexture(texture_ambient,	Scatter_Light::AMBIENT);
	scatter_light_1->setTexture(texture_image,		Scatter_Light::DIFFUSE);
	scatter_light_1->setTexture(texture_specular,	Scatter_Light::SPECULAR);
	scatter_light_1->setTexture(texture_shininess,	Scatter_Light::SHININESS);

	// set scene object
	const double x = -2;
	const double y = -1.1;
	const double w = 4;
	const double h = 6;
	const double z = 0;

	SceneObject_Trimesh *scene_trimesh_1 = new SceneObject_Trimesh(Vec3f(x, y, z), Vec3f(x, y + h, z), Vec3f(x + w, y, z));
	scene_trimesh_1->shader.addScatter(scatter_reflection_1);
	scene_trimesh_1->shader.addScatter(scatter_light_1);
	scene_trimesh_1->material.transmissive->setPixel(Vec3f(), Vec3f(0));
	scene->addHitable(scene_trimesh_1);

	SceneObject_Trimesh *scene_trimesh_2 = new SceneObject_Trimesh(Vec3f(x + w, y, z), Vec3f(x, y + h, z), Vec3f(x + w, y + h, z));
	scene_trimesh_2->shader.addScatter(scatter_reflection_1);
	scene_trimesh_2->shader.addScatter(scatter_light_1);
	scene->addHitable(scene_trimesh_2);
}


static Vec3f Linker_getColor(double x, double y, void *info) {
	const TraceData	*data	= (TraceData*)info;
	const RayTracer	*tracer	= data->tracer;
	return tracer->trace(data->camera, x, y, data->depth);
}