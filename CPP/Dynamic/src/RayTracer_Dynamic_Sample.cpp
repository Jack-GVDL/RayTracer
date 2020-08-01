#include "../../Scatter/Scatter.hpp"
#include "../inc/RayTracer_Dynamic_Sample.hpp"


// Define
// ...


// Typedef
typedef int(*build_scene_func_t)(Camera*, Scene*);


// Static Function Prototype
static int	build_scene_1	(Camera *camera, Scene *scene);


// Static Data
static int					build_scene_size	= 1;
static build_scene_func_t	build_scene_table[]	= {
	build_scene_1
};


// Operation Handling
int RayTracer_Dynamic_Sample_buildScene(int index, Camera *camera, Scene *scene) {
	if (index < 0 || index >= build_scene_size) return -1;
	return build_scene_table[index](camera, scene);
}


// Static Function Implementation
static int build_scene_1(Camera *camera, Scene *scene) {
	// shader
	Texture_Constant *texture_emissive		= new Texture_Constant();
	Texture_Constant *texture_ambient		= new Texture_Constant();
	Texture_Constant *texture_diffuse		= new Texture_Constant();
	Texture_Constant *texture_specular		= new Texture_Constant();
	Texture_Constant *texture_shininess		= new Texture_Constant();
	// Texture_Constant *texture_reflective	= new Texture_Constant();

	texture_emissive->setPixel		(Vec3f(),		Vec3f(0));
	texture_ambient->setPixel		(Vec3f(), 		Vec3f(0));
	texture_diffuse->setPixel		(Vec3f(), 		Vec3f(0.5));
	texture_specular->setPixel		(Vec3f(), 		Vec3f(0.5));
	texture_shininess->setPixel		(Vec3f(),		Vec3f(0));
	// texture_reflective->setPixel	(Vec3f(),		Vec3f(0));

	// scatter
	Scatter_Light *scatter_light_1 = new Scatter_Light();
	scatter_light_1->setTexture(texture_emissive,	Scatter_Light::EMISSIVE);
	scatter_light_1->setTexture(texture_ambient,	Scatter_Light::AMBIENT);
	scatter_light_1->setTexture(texture_diffuse,	Scatter_Light::DIFFUSE);
	scatter_light_1->setTexture(texture_specular,	Scatter_Light::SPECULAR);
	scatter_light_1->setTexture(texture_shininess,	Scatter_Light::SHININESS);

	// Scatter_Reflection *scatter_reflection_1 = new Scatter_Reflection();
	// scatter_reflection_1->setTexture(texture_reflective, Scatter_Reflection::REFLECTIVE);
	
	// scene
	SceneObject_Sphere *scene_sphere_1 = new SceneObject_Sphere(Vec3f(0), 0.5);
	scene->addHitable(scene_sphere_1);

	// light
	SceneObject_Light_Point *light_point_1 = new SceneObject_Light_Point(Vec3f(1, 1, 1));
	light_point_1->color	= Vec3f(1);
	scene->addLight(light_point_1);

	// camera
	camera->setAll(Vec3f(0, 0, 1), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 90, 0.2);

	return 0;
}
