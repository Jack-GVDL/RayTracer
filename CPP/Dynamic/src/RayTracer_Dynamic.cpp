#include <stdio.h>
#include <vector>
#include "../inc/RayTracer_Dynamic.hpp"
#include "../inc/RayTracer_DynamicContainer.hpp"
#include "../inc/RayTracer_Dynamic_Camera.hpp"
#include "../inc/RayTracer_Dynamic_Surface.hpp"
#include "../inc/RayTracer_Dynamic_Texture.hpp"
#include "../inc/RayTracer_Dynamic_Scatter.hpp"
#include "../inc/RayTracer_Dynamic_Hitable.hpp"
#include "../inc/RayTracer_Dynamic_Light.hpp"
#include "../inc/RayTracer_Dynamic_Mapper.hpp"
#include "../inc/RayTracer_Dynamic_Sample.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
RayTracer									tracer;
Scene										scene;

Dynamic_ContainerList<Camera>				camera_list;
Dynamic_ContainerList<Mapper>				mapper_list;
Dynamic_ContainerList<Surface>				surface_list;
Dynamic_ContainerList<Texture>				texture_list;
Dynamic_ContainerList<Scatter>				scatter_list;
Dynamic_ContainerList<SceneObject_Hitable>	hitable_list;
Dynamic_ContainerList<SceneObject_Light>	light_list;


// Operation Handling
EXPORT_DLL(void) RayTracer_init() {
	// tracer
	tracer	= RayTracer(&scene);

	// init
	RayTracer_Dynamic_Camera_init(	&(camera_list.init_list),	&(camera_list.config_list)	);
	RayTracer_Dynamic_Mapper_init(	&(mapper_list.init_list),	&(mapper_list.config_list)	);
	RayTracer_Dynamic_Surface_init(	&(surface_list.init_list),	&(surface_list.config_list)	);
	RayTracer_Dynamic_Texture_init(	&(texture_list.init_list),	&(texture_list.config_list)	);
	RayTracer_Dynamic_Scatter_init(	&(scatter_list.init_list),	&(scatter_list.config_list)	);
	RayTracer_Dynamic_Hitable_init(	&(hitable_list.init_list),	&(hitable_list.config_list)	);
	RayTracer_Dynamic_Light_init(	&(light_list.init_list),	&(light_list.config_list)	);

	// create a deafult camera
	// can / should be used for testing
	RayTracer_Camera_create(0);
	Dynamic_Container<Camera> *container_camera = camera_list.get(1);
	container_camera->object->setAll(Vec3f(0, 0, 1), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 90, 2);
}


EXPORT_DLL(void) RayTracer_del() {

}


EXPORT_DLL(void) RayTracer_info() {
	// date of build
	printf("Ray Tracer, build on %s %s \n", __DATE__, __TIME__);

	// module info
	RayTracer_Dynamic_Camera_info();
	RayTracer_Dynamic_Surface_info();
	RayTracer_Dynamic_Mapper_info();
	RayTracer_Dynamic_Texture_info();
	RayTracer_Dynamic_Scatter_info();
	RayTracer_Dynamic_Hitable_info();
	RayTracer_Dynamic_Light_info();

	// spacing
	printf("\n");
}


// test
// ...


// sample
EXPORT_DLL(int) RayTracer_Sample_buildScene(int index) {
	// camera 0 is used for testing and is created at init stage
	Dynamic_Container<Camera> *container_camera = camera_list.get(1);
	return RayTracer_Dynamic_Sample_buildScene(index, container_camera->object, &scene);
}


// tracer
EXPORT_DLL(int) RayTracer_Tracer_tracePoint(int index_camera, double *pixel, double x, double y, int depth) {
	// get camera
	Dynamic_Container<Camera> *container_camera = camera_list.get(1);
	if (container_camera == nullptr) {
		pixel[0] = 0;
		pixel[1] = 0;
		pixel[2] = 0;
		return -1;
	}

	// get pixel
	Camera	*camera	= container_camera->object;
	Vec3f	result	= tracer.trace(camera, x, y, depth);

	// set pixel
	pixel[0] = result[0];
	pixel[1] = result[1];
	pixel[2] = result[2];

	return 0;
}


EXPORT_DLL(int) RayTracer_Tracer_tracerRect(int index_camera, double *pixel, double w, double h, double pixel_w, double pixel_h, int depth) {
	// get camera
	Dynamic_Container<Camera> *container_camera = camera_list.get(1);
	if (container_camera == nullptr) {
		pixel[0] = 0;
		pixel[1] = 0;
		pixel[2] = 0;
		return -1;
	}

	// TODO: not yet completed
	// ...

	return 0;
}


// camera
// TODO: currently type is useless
EXPORT_DLL(int) RayTracer_Camera_create(int type) {
	Dynamic_Container<Camera> *container_camera = camera_list.create(type);
	if (container_camera == nullptr) return -1;
	return container_camera->getIndex();
}


EXPORT_DLL(int) RayTracer_Camera_destroy(int index) {
	return camera_list.destroy(index);
}


EXPORT_DLL(int) RayTracer_Camera_setLookFrom(int index, double *look_from) {
	Dynamic_Container<Camera> *container_camera = camera_list.get(index);
	if (container_camera == nullptr) return -1;

	container_camera->object->setLookFrom(Vec3f(look_from[0], look_from[1], look_from[2]));
	return 0;
}


EXPORT_DLL(int) RayTracer_Camera_setLookAt(int index, double *look_at) {
	Dynamic_Container<Camera> *container_camera = camera_list.get(index);
	if (container_camera == nullptr) return -1;

	container_camera->object->setLookAt(Vec3f(look_at[0], look_at[1], look_at[2]));
	return 0;
}


EXPORT_DLL(int) RayTracer_Camera_setUpDirection(int index, double *up_dir) {
	Dynamic_Container<Camera> *container_camera = camera_list.get(index);
	if (container_camera == nullptr) return -1;

	container_camera->object->setUpDirection(Vec3f(up_dir[0], up_dir[1], up_dir[2]));
	return 0;
}


EXPORT_DLL(int) RayTracer_Camera_setFOV(int index, double value) {
	Dynamic_Container<Camera> *container_camera = camera_list.get(index);
	if (container_camera == nullptr) return -1;

	container_camera->object->setFOV(value);
	return 0;
}


EXPORT_DLL(int) RayTracer_Camera_setAspectRatio(int index, double value) {
	Dynamic_Container<Camera> *container_camera = camera_list.get(index);
	if (container_camera == nullptr) return -1;

	container_camera->object->setAspectRatio(value);
	return 0;
}


EXPORT_DLL(int) RayTracer_Camera_config(int index, int type, uint8_t *data, uint32_t size) {
	return camera_list.config(index, type, data, size);
}


// mapper
EXPORT_DLL(int) RayTracer_Mapper_create(int type) {
	Dynamic_Container<Mapper> *container_mapper = mapper_list.create(type);
	if (container_mapper == nullptr) return -1;
	return container_mapper->getIndex();
}


EXPORT_DLL(int) RayTracer_Mapper_destroy(int index) {
	return mapper_list.destroy(index);
}


EXPORT_DLL(int) RayTracer_Mapper_config(int index, int type, uint8_t *data, uint32_t size) {
	return mapper_list.config(index, type, data, size);
}


// surface
EXPORT_DLL(int) RayTracer_Surface_create(int type) {
	Dynamic_Container<Surface> *surface = surface_list.create(type);
	if (surface == nullptr) return -1;
	return surface->getIndex();
}


EXPORT_DLL(int) RayTracer_Surface_destroy(int index) {
	return surface_list.destroy(index);
}


EXPORT_DLL(int) RayTracer_Surface_load(int index) {
	Dynamic_Container<Surface> *container_surface = surface_list.get(index);
	if (container_surface == nullptr) return -1;

	if (!container_surface->object->load()) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Surface_dump(int index) {
	Dynamic_Container<Surface> *container_surface = surface_list.get(index);
	if (container_surface == nullptr) return -1;

	if (!container_surface->object->dump()) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Surface_convertToTexture(int index_surface, int index_texture) {
	Dynamic_Container<Surface> *container_surface = surface_list.get(index_surface);
	if (container_surface == nullptr) return -1;

	Dynamic_Container<Texture> *container_texture = texture_list.get(index_texture);
	if (container_texture == nullptr) return -1;

	// need to check type of texture
	// which need to be Texture_Image
	if (container_texture->type != TypeTexture::TEXTURE_IMAGE) return -1;

	if (!container_surface->object->convertToTexture((Texture_Image*)(container_texture->object))) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Surface_config(int index, int type, uint8_t *data, uint32_t size) {
	return surface_list.config(index, type, data, size);
}


// texture
EXPORT_DLL(int) RayTracer_Texture_create(int type) {
	Dynamic_Container<Texture> *texture = texture_list.create(type);
	if (texture == nullptr) return -1;
	return texture->getIndex();
}


EXPORT_DLL(int) RayTracer_Texture_destroy(int index) {
	return texture_list.destroy(index);	
}


EXPORT_DLL(int) RayTracer_Texture_addMapper(int index_texture, int index_mapper) {
	Dynamic_Container<Texture>	*container_texture	= texture_list.get(index_texture);
	if (container_texture == nullptr) return -1;

	Dynamic_Container<Mapper>	*container_mapper	= mapper_list.get(index_mapper);
	if (container_mapper == nullptr) return -1;

	if (!container_texture->object->addMapper(container_mapper->object)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Texture_rmMapper(int index_texture, int index_mapper) {
	Dynamic_Container<Texture>	*container_texture	= texture_list.get(index_texture);
	if (container_texture == nullptr) return -1;

	Dynamic_Container<Mapper>	*container_mapper	= mapper_list.get(index_mapper);
	if (container_mapper == nullptr) return -1;

	if (!container_texture->object->rmMapper(container_mapper->object)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Texture_setPixel(int index, const double *pixel, const double *point) {
	Dynamic_Container<Texture> *texture = texture_list.get(index);
	if (texture == nullptr) return -1;

	texture->object->setPixel(
		Vec3f(point[0], point[1], point[2]),
		Vec3f(pixel[0], pixel[1], pixel[2]));

	return 0;
}


EXPORT_DLL(int) RayTracer_Texture_getPixel(int index, double *pixel, const double *point) {
	Dynamic_Container<Texture> *texture = texture_list.get(index);
	if (texture == nullptr) return -1;

	Vec3f vec_pixel = texture->object->getPixel(Vec3f(point[0], point[1], point[2]));
	pixel[0] = vec_pixel[0];
	pixel[1] = vec_pixel[1];
	pixel[2] = vec_pixel[2];

	return 0;
}


EXPORT_DLL(int) RayTracer_Texture_config(int index, int type, uint8_t *data, uint32_t size) {
	return texture_list.config(index, type, data, size);
}


// scatter
EXPORT_DLL(int) RayTracer_Scatter_create(int type) {
	Dynamic_Container<Scatter> *scatter = scatter_list.create(type);
	if (scatter == nullptr) return -1;
	return scatter->getIndex();
}


EXPORT_DLL(int) RayTracer_Scatter_destroy(int index) {
	return scatter_list.destroy(index);
}


EXPORT_DLL(int) RayTracer_Scatter_setTexture(int index_scatter, int index_texture, int offset) {
	// get container
	Dynamic_Container<Scatter>	*container_scatter	= scatter_list.get(index_scatter);
	if (container_scatter == nullptr) return -1;

	Dynamic_Container<Texture>	*container_texture	= texture_list.get(index_texture);
	if (container_texture == nullptr) return -1;

	// set texture
	Scatter	*scatter = container_scatter->object;
	Texture	*texture = container_texture->object;

	if (!scatter->setTexture(texture, offset)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Scatter_config(int index, int type, uint8_t *data, uint32_t size) {
	return scatter_list.config(index, type, data, size);
}


// hitable
EXPORT_DLL(int) RayTracer_SceneObject_Hitable_create(int type) {
	Dynamic_Container<SceneObject_Hitable> *hitable = hitable_list.create(type);
	if (hitable == nullptr) return -1;
	return hitable->getIndex();
}


EXPORT_DLL(int) RayTracer_SceneObject_Hitable_destroy(int index) {
	return hitable_list.destroy(index);
}


EXPORT_DLL(int) RayTracer_SceneObject_Hitable_addScatter(int index_hitable, int index_scatter) {
	// get container
	Dynamic_Container<SceneObject_Hitable>	*container_hitable = hitable_list.get(index_hitable);
	if (container_hitable == nullptr) return -1;

	Dynamic_Container<Scatter> *container_scatter = scatter_list.get(index_scatter);
	if (container_scatter == nullptr) return -1;

	// add scatter
	SceneObject_Hitable	*hitable	= container_hitable->object;
	Scatter				*scatter	= container_scatter->object;

	if (!hitable->shader.addScatter(scatter)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_SceneObject_Hitable_rmScatter(int index_hitable, int index_scatter) {
	// get container
	Dynamic_Container<SceneObject_Hitable>	*container_hitable = hitable_list.get(index_hitable);
	if (container_hitable == nullptr) return -1;

	Dynamic_Container<Scatter> *container_scatter = scatter_list.get(index_scatter);
	if (container_scatter == nullptr) return -1;

	// remove scatter
	SceneObject_Hitable	*hitable	= container_hitable->object;
	Scatter				*scatter	= container_scatter->object;

	if (!hitable->shader.rmScatter(scatter)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_SceneObject_Hitable_config(int index, int type, uint8_t *data, uint32_t size) {
	return hitable_list.config(index, type, data, size);
}


// light
EXPORT_DLL(int) RayTracer_SceneObject_Light_create(int type) {
	Dynamic_Container<SceneObject_Light> *light = light_list.create(type);
	if (light == nullptr) return -1;
	return light->getIndex();
}


EXPORT_DLL(int) RayTracer_SceneObject_Light_destroy(int index) {
	return light_list.destroy(index);
}


EXPORT_DLL(int) RayTracer_SceneObject_Light_setOrigin(int index, double *origin) {
	Dynamic_Container<SceneObject_Light> *container_light = light_list.get(index);
	if (container_light == nullptr) return -1;

	container_light->object->setOrigin(Vec3f(origin[0], origin[1], origin[2]));
	return 0;
}


EXPORT_DLL(int) RayTracer_SceneObject_Light_setColor(int index, double *color) {
	Dynamic_Container<SceneObject_Light> *container_light = light_list.get(index);
	if (container_light == nullptr) return -1;

	container_light->object->setColor(Vec3f(color[0], color[1], color[2]));
	return 0;
}


EXPORT_DLL(int) RayTracer_SceneObject_Light_config(int index, int type, uint8_t *data, uint32_t size) {
	return light_list.config(index, type, data, size);
}


// scene
EXPORT_DLL(int) RayTracer_Scene_addLight(int index_light) {
	Dynamic_Container<SceneObject_Light> *container_light = light_list.get(index_light);
	if (container_light == nullptr) return -1;

	SceneObject_Light *light = container_light->object;
	if (!scene.addLight(light)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Scene_addHitable(int index_hitable) {
	Dynamic_Container<SceneObject_Hitable> *container_hitable = hitable_list.get(index_hitable);
	if (container_hitable == nullptr) return -1;

	SceneObject_Hitable *hitable = container_hitable->object;
	if (!scene.addHitable(hitable)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Scene_rmLight(int index_light) {
	Dynamic_Container<SceneObject_Light> *container_light = light_list.get(index_light);
	if (container_light == nullptr) return -1;

	SceneObject_Light *light = container_light->object;
	if (!scene.rmLight(light)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Scene_rmHitable(int index_hitable) {
	Dynamic_Container<SceneObject_Hitable> *container_hitable = hitable_list.get(index_hitable);
	if (container_hitable == nullptr) return -1;

	SceneObject_Hitable *hitable = container_hitable->object;
	if (!scene.rmHitable(hitable)) return -1;
	return 0;
}


// Static Function Implementation
// ...
