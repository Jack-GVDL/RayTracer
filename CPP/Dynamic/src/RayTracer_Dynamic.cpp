#include <stdio.h>
#include <vector>
#include <string>

#include "../inc/RayTracer_DynamicContainer.hpp"
#include "../inc/RayTracer_DynamicSkeleton.hpp"

#include "../inc/RayTracer_Dynamic_Camera.hpp"
#include "../inc/RayTracer_Dynamic_Tracer.hpp"
#include "../inc/RayTracer_Dynamic_Surface.hpp"
#include "../inc/RayTracer_Dynamic_Texture.hpp"
#include "../inc/RayTracer_Dynamic_Scatter.hpp"
#include "../inc/RayTracer_Dynamic_Hitable.hpp"
#include "../inc/RayTracer_Dynamic_Light.hpp"
#include "../inc/RayTracer_Dynamic_Sample.hpp"

#include "../inc/RayTracer_Dynamic.hpp"


// Define
#define BUFFER_MAX_LENGTH	8


#define Dynamic_constructTypeInterface_Type_getIndex(name, type, container_list)	\
																					\
EXPORT_DLL(int) RayTracer_##name##_Type_getIndex(const char *name_) {				\
	return Dynamic_ContainerList_Type_getIndex<type>(container_list, name_);		\
}


#define Dynamic_constructTypeInterface_Object_create(name, type, container_list)	\
																					\
EXPORT_DLL(int) RayTracer_##name##_create(int type_) {								\
	return Dynamic_ContainerList_Object_create<type>(container_list, type_);		\
}


#define Dynamic_constructTypeInterface_Object_destroy(name, type, container_list)	\
																					\
EXPORT_DLL(int) RayTracer_##name##_destroy(int index) {								\
	return Dynamic_ContainerList_Object_destroy<type>(container_list, index);		\
}


#define Dynamic_constructTypeInterface_Object_config(name, type, container_list)				\
																								\
EXPORT_DLL(int)	RayTracer_##name##_config(int index, int type_, uint8_t *data, uint32_t size) {	\
	return Dynamic_ContainerList_Object_config<type>(container_list, index, type_, data, size);	\
}


#define Dynamic_constructTypeInterface_Object_interact(name, type, container_list)									\
																													\
EXPORT_DLL(int) RayTracer_##name##_interact(int index, int type_, int *index_list, int *type_list, uint32_t size) {	\
	return Dynamic_ContainerList_Object_interact<type>(container_list, index, type_, index_list, type_list, size);	\
}


#define Dynamic_constructTypeInterface(name, type, container_list)					\
																					\
Dynamic_constructTypeInterface_Type_getIndex(name, type, container_list)			\
Dynamic_constructTypeInterface_Object_create(name, type, container_list)			\
Dynamic_constructTypeInterface_Object_destroy(name, type, container_list)			\
Dynamic_constructTypeInterface_Object_config(name, type, container_list)			\
Dynamic_constructTypeInterface_Object_interact(name, type, container_list)


// Typedef
// ...


// Static Function Prototype
template <class T>
static inline int	Dynamic_ContainerList_Type_getIndex		(Dynamic_ContainerList<T> *list, const char *name);

template <class T>
static inline int	Dynamic_ContainerList_Object_create		(Dynamic_ContainerList<T> *list, int type);

template <class T>
static inline int	Dynamic_ContainerList_Object_destroy	(Dynamic_ContainerList<T> *list, int index);

template <class T>
static inline int	Dynamic_ContainerList_Object_config		(Dynamic_ContainerList<T> *list, int index, int type, uint8_t *data, uint32_t size);

template <class T>
static inline int	Dynamic_ContainerList_Object_interact	(Dynamic_ContainerList<T> *list, int index, int type, int *index_list, int *type_list, uint32_t size);


// Static Data
RayTracer									tracer;
Scene										scene;

Dynamic_ContainerList<Camera>				camera_list;
Dynamic_ContainerList<Surface>				surface_list;
Dynamic_ContainerList<Texture>				texture_list;
Dynamic_ContainerList<Scatter>				scatter_list;
Dynamic_ContainerList<SceneObject_Hitable>	hitable_list;
Dynamic_ContainerList<SceneObject_Light>	light_list;

Dynamic_ContainerListBase*					container_list[] = {
	&camera_list,
	&surface_list,
	&texture_list,
	&scatter_list,
	&hitable_list,
	&light_list
};


// Operation Handling
EXPORT_DLL(void) RayTracer_init() {
	// tracer
	tracer = RayTracer();
	tracer.setScene(&scene);

	// init
	RayTracer_Dynamic_Camera_init(	&(camera_list.type_list)	);
	RayTracer_Dynamic_Surface_init(	&(surface_list.type_list)	);
	RayTracer_Dynamic_Texture_init(	&(texture_list.type_list)	);
	RayTracer_Dynamic_Scatter_init(	&(scatter_list.type_list)	);
	RayTracer_Dynamic_Hitable_init(	&(hitable_list.type_list)	);
	RayTracer_Dynamic_Light_init(	&(light_list.type_list)		);

	// load
	camera_list.Type_load();
	surface_list.Type_load();
	texture_list.Type_load();
	scatter_list.Type_load();
	hitable_list.Type_load();
	light_list.Type_load();

	// create a deafult camera
	// can / should be used for testing
	RayTracer_Camera_create(0);
	Dynamic_Container<Camera> *container_camera = camera_list.get(1);
	container_camera->getObject()->setAll(Vec3f(0, 0, 1), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 90, 2);
}


EXPORT_DLL(void) RayTracer_del() {

}


EXPORT_DLL(void) RayTracer_info() {
	// date of build
	printf("Ray Tracer, build on %s %s \n", __DATE__, __TIME__);

	// spacing
	printf("\n");
}


// test
// ...


// sample
EXPORT_DLL(int) RayTracer_Sample_buildScene(int index) {
	// camera 0 is used for testing and is created at init stage
	Dynamic_Container<Camera> *container_camera = camera_list.get(1);
	return RayTracer_Dynamic_Sample_buildScene(index, container_camera->getObject(), &scene);
}


// tracer
// TODO: move to Dynamic_Tracer
// EXPORT_DLL(int) RayTracer_Tracer_tracePoint(int index_camera, void *pixel, double x, double y, int depth, int format) {
// 	// get camera
// 	Dynamic_Container<Camera> *container_camera = camera_list.get(1);
// 	if (container_camera == nullptr) {
// 		pixel[0] = 0;
// 		pixel[1] = 0;
// 		pixel[2] = 0;
// 		return -1;
// 	}

// 	// get pixel
// 	Camera	*camera	= container_camera->getObject();
// 	Vec3f	result	= tracer.trace(camera, x, y, depth);

// 	// set pixel
// 	pixel[0] = result[0];
// 	pixel[1] = result[1];
// 	pixel[2] = result[2];

// 	return 0;
// }


EXPORT_DLL(int) RayTracer_Tracer_traceRect(
	int index_camera, void *data, int w, int h, int depth, 
	int is_reverse_x, int is_reverse_y, int format) {

	switch (format) {
		case 0:
			return RayTracer_Dynamic_Tracer_tracePoint_RGB888(
				index_camera, data, w, h, depth, is_reverse_x, is_reverse_y);
		
		case 1:
			return RayTracer_Dynamic_Tracer_tracePoint_RGB64F(
				index_camera, data, w, h, depth, is_reverse_x, is_reverse_y);

	}

	return -1;

}


// camera
Dynamic_constructTypeInterface(Camera, Camera, &camera_list);


EXPORT_DLL(int) RayTracer_Camera_setLookFrom(int index, double *look_from) {
	Dynamic_Container<Camera> *container_camera = camera_list.get(index);
	if (container_camera == nullptr) return -1;

	container_camera->getObject()->setLookFrom(Vec3f(look_from[0], look_from[1], look_from[2]));
	return 0;
}


EXPORT_DLL(int) RayTracer_Camera_setLookAt(int index, double *look_at) {
	Dynamic_Container<Camera> *container_camera = camera_list.get(index);
	if (container_camera == nullptr) return -1;

	container_camera->getObject()->setLookAt(Vec3f(look_at[0], look_at[1], look_at[2]));
	return 0;
}


EXPORT_DLL(int) RayTracer_Camera_setUpDirection(int index, double *up_dir) {
	Dynamic_Container<Camera> *container_camera = camera_list.get(index);
	if (container_camera == nullptr) return -1;

	container_camera->getObject()->setUpDirection(Vec3f(up_dir[0], up_dir[1], up_dir[2]));
	return 0;
}


EXPORT_DLL(int) RayTracer_Camera_setFOV(int index, double value) {
	Dynamic_Container<Camera> *container_camera = camera_list.get(index);
	if (container_camera == nullptr) return -1;

	container_camera->getObject()->setFOV(value);
	return 0;
}


EXPORT_DLL(int) RayTracer_Camera_setAspectRatio(int index, double value) {
	Dynamic_Container<Camera> *container_camera = camera_list.get(index);
	if (container_camera == nullptr) return -1;

	container_camera->getObject()->setAspectRatio(value);
	return 0;
}


// surface
Dynamic_constructTypeInterface(Surface, Surface, &surface_list);


EXPORT_DLL(int) RayTracer_Surface_load(int index) {
	Dynamic_Container<Surface> *container_surface = surface_list.get(index);
	if (container_surface == nullptr) return -1;

	if (!container_surface->getObject()->load()) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Surface_dump(int index) {
	Dynamic_Container<Surface> *container_surface = surface_list.get(index);
	if (container_surface == nullptr) return -1;

	if (!container_surface->getObject()->dump()) return -1;
	return 0;
}


// texture
Dynamic_constructTypeInterface(Texture, Texture, &texture_list);


EXPORT_DLL(int) RayTracer_Texture_addInput(int index_output, int index_input, int offset) {
	Dynamic_Container<Texture> *container_texture = texture_list.get(index_output);
	if (container_texture == nullptr) return -1;

	Dynamic_Container<Texture> *container_input = texture_list.get(index_input);
	if (container_input == nullptr) return -1;

	if (!container_texture->getObject()->addInput(container_input->getObject(), offset)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Texture_rmInput(int index_output, int offset) {
	Dynamic_Container<Texture> *container_texture = texture_list.get(index_output);
	if (container_texture == nullptr) return -1;

	if (!container_texture->getObject()->rmInput(offset)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Texture_setPixel(int index, const double *pixel, const double *point) {
	Dynamic_Container<Texture> *texture = texture_list.get(index);
	if (texture == nullptr) return -1;

	texture->getObject()->setPixel(
		Vec3f(point[0], point[1], point[2]),
		Vec3f(pixel[0], pixel[1], pixel[2]));

	return 0;
}


EXPORT_DLL(int) RayTracer_Texture_getPixel(int index, double *pixel, const double *point) {
	Dynamic_Container<Texture> *texture = texture_list.get(index);
	if (texture == nullptr) return -1;

	Vec3f vec_pixel;
	texture->getObject()->getPixel(vec_pixel, Vec3f(point[0], point[1], point[2]));
	
	pixel[0] = vec_pixel[0];
	pixel[1] = vec_pixel[1];
	pixel[2] = vec_pixel[2];

	return 0;
}


// scatter
Dynamic_constructTypeInterface(Scatter, Scatter, &scatter_list);


EXPORT_DLL(int)RayTracer_Scatter_addScatter(int index_scatter, int index_target) {
	// get container
	Dynamic_Container<Scatter>	*container_scatter	= scatter_list.get(index_scatter);
	if (container_scatter == nullptr) return -1;

	Dynamic_Container<Scatter>	*container_target	= scatter_list.get(index_target);
	if (container_target == nullptr) return -1;

	// add scatter
	Scatter *scatter	= container_scatter->getObject();
	Scatter *target		= container_target->getObject();

	if (scatter->addScatter(target) != ERROR_NO) return -1;
	return 0;
}


EXPORT_DLL(int)RayTracer_Scatter_rmScatter(int index_scatter, int index_target) {
	// get container
	Dynamic_Container<Scatter>	*container_scatter	= scatter_list.get(index_scatter);
	if (container_scatter == nullptr) return -1;

	Dynamic_Container<Scatter>	*container_target	= scatter_list.get(index_target);
	if (container_target == nullptr) return -1;

	// rm scatter
	Scatter *scatter	= container_scatter->getObject();
	Scatter *target		= container_target->getObject();

	if (scatter->rmScatter(target) != ERROR_NO) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Scatter_setTexture(int index_scatter, int index_texture, int offset) {
	// get container
	Dynamic_Container<Scatter>	*container_scatter	= scatter_list.get(index_scatter);
	if (container_scatter == nullptr) return -1;

	Dynamic_Container<Texture>	*container_texture	= texture_list.get(index_texture);
	if (container_texture == nullptr) return -1;

	// set texture
	Scatter	*scatter = container_scatter->getObject();
	Texture	*texture = container_texture->getObject();

	if (!scatter->setTexture(texture, offset)) return -1;
	return 0;
}


// hitable
Dynamic_constructTypeInterface(SceneObject_Hitable, SceneObject_Hitable, &hitable_list);


EXPORT_DLL(int) RayTracer_SceneObject_Hitable_addScatter(int index_hitable, int index_scatter) {
	// get container
	Dynamic_Container<SceneObject_Hitable>	*container_hitable = hitable_list.get(index_hitable);
	if (container_hitable == nullptr) return -1;

	Dynamic_Container<Scatter> *container_scatter = scatter_list.get(index_scatter);
	if (container_scatter == nullptr) return -1;

	// add scatter
	SceneObject_Hitable	*hitable	= container_hitable->getObject();
	Scatter				*scatter	= container_scatter->getObject();

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
	SceneObject_Hitable	*hitable	= container_hitable->getObject();
	Scatter				*scatter	= container_scatter->getObject();

	if (!hitable->shader.rmScatter(scatter)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_SceneObject_Hitable_setTransmissive(int index, double *transmissive) {
	Dynamic_Container<SceneObject_Hitable> *container_hitable = hitable_list.get(index);
	if (container_hitable == nullptr) return -1;

	SceneObject_Hitable *hitable = container_hitable->getObject();
	hitable->material.transmissive->setPixel(
		Vec3f(), 
		Vec3f(transmissive[0], transmissive[1], transmissive[2]));
	
	return 0;
}


EXPORT_DLL(int) RayTracer_SceneObject_Hitable_setIndex(int index, double value) {
	Dynamic_Container<SceneObject_Hitable> *container_hitable = hitable_list.get(index);
	if (container_hitable == nullptr) return -1;

	SceneObject_Hitable *hitable = container_hitable->getObject();
	hitable->material.index = value;
	return 0;
}


// light
Dynamic_constructTypeInterface(SceneObject_Light, SceneObject_Light, &light_list);


EXPORT_DLL(int) RayTracer_SceneObject_Light_setOrigin(int index, double *origin) {
	Dynamic_Container<SceneObject_Light> *container_light = light_list.get(index);
	if (container_light == nullptr) return -1;

	container_light->getObject()->setOrigin(Vec3f(origin[0], origin[1], origin[2]));
	return 0;
}


EXPORT_DLL(int) RayTracer_SceneObject_Light_setColor(int index, double *color) {
	Dynamic_Container<SceneObject_Light> *container_light = light_list.get(index);
	if (container_light == nullptr) return -1;

	container_light->getObject()->setColor(Vec3f(color[0], color[1], color[2]));
	return 0;
}


// scene
EXPORT_DLL(int) RayTracer_Scene_addLight(int index_light) {
	Dynamic_Container<SceneObject_Light> *container_light = light_list.get(index_light);
	if (container_light == nullptr) return -1;

	SceneObject_Light *light = container_light->getObject();
	if (!scene.addLight(light)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Scene_addHitable(int index_hitable) {
	Dynamic_Container<SceneObject_Hitable> *container_hitable = hitable_list.get(index_hitable);
	if (container_hitable == nullptr) return -1;

	SceneObject_Hitable *hitable = container_hitable->getObject();
	if (!scene.addHitable(hitable)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Scene_rmLight(int index_light) {
	Dynamic_Container<SceneObject_Light> *container_light = light_list.get(index_light);
	if (container_light == nullptr) return -1;

	SceneObject_Light *light = container_light->getObject();
	if (!scene.rmLight(light)) return -1;
	return 0;
}


EXPORT_DLL(int) RayTracer_Scene_rmHitable(int index_hitable) {
	Dynamic_Container<SceneObject_Hitable> *container_hitable = hitable_list.get(index_hitable);
	if (container_hitable == nullptr) return -1;

	SceneObject_Hitable *hitable = container_hitable->getObject();
	if (!scene.rmHitable(hitable)) return -1;
	return 0;
}


// Static Function Implementation
template <class T>
static inline int Dynamic_ContainerList_Type_getIndex(Dynamic_ContainerList<T> *list, const char *name) {
	return list->Type_indexOf(std::string(name));
}


template <class T>
static inline int Dynamic_ContainerList_Object_create(Dynamic_ContainerList<T> *list, int type) {
	Dynamic_Container<T> *container = list->create(type);
	if (container == nullptr) return -1;
	return container->getIndex();
}


template <class T>
static inline int Dynamic_ContainerList_Object_destroy(Dynamic_ContainerList<T> *list, int index) {
	return list->destroy(index);
}


template <class T>
static inline int Dynamic_ContainerList_Object_config(Dynamic_ContainerList<T> *list, int index, int type, uint8_t *data, uint32_t size) {
	return list->config(index, type, data, size);
}


template <class T>
static inline int Dynamic_ContainerList_Object_interact(Dynamic_ContainerList<T> *list, int index, int type, int *index_list, int *type_list, uint32_t size) {
	// get interaction object list
	Dynamic_ContainerBase* interact_list[BUFFER_MAX_LENGTH] = {0};
	for (int i = 0; i < size; i++) {
		const int target_index	= index_list[i];
		const int target_type	= type_list[i];
		interact_list[i] = container_list[target_type]->_get_(target_index);

		if (interact_list[i] == nullptr) return -1;
	}

	// interact
	return list->interact(index, type, interact_list, size);
}
