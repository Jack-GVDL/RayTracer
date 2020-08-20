#include <stdio.h>
#include <vector>
#include <string>
#include "../inc/RayTracer_Dynamic.hpp"
#include "../inc/RayTracer_DynamicContainer.hpp"
#include "../inc/RayTracer_Dynamic_Camera.hpp"
#include "../inc/RayTracer_Dynamic_Surface.hpp"
#include "../inc/RayTracer_Dynamic_Texture.hpp"
#include "../inc/RayTracer_Dynamic_Scatter.hpp"
#include "../inc/RayTracer_Dynamic_Hitable.hpp"
#include "../inc/RayTracer_Dynamic_Light.hpp"
#include "../inc/RayTracer_Dynamic_Sample.hpp"


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
	tracer	= RayTracer(&scene);

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
	Camera	*camera	= container_camera->getObject();
	Vec3f	result	= tracer.trace(camera, x, y, depth);

	// set pixel
	pixel[0] = result[0];
	pixel[1] = result[1];
	pixel[2] = result[2];

	return 0;
}


EXPORT_DLL(int) RayTracer_Tracer_traceRect(int index_camera, double *pixel, int w, int h, int depth, int is_reverse_x, int is_reverse_y) {
	
	// get camera
	Dynamic_Container<Camera> *container_camera = camera_list.get(1);
	if (container_camera == nullptr) {
		pixel[0] = 0;
		pixel[1] = 0;
		pixel[2] = 0;
		return -1;
	}

	// based on property of export image
	// order of putting pixel on the linear memory space may be different
	int index_x_start, 		index_y_start;
	int index_x_next, 		index_y_next;

	// reverse x or not
	if (!is_reverse_x) {
		index_x_start	= 0;
		index_x_next	= 1;
	} else {
		index_x_start	= w - 1;
		index_x_next	= -1;
	}

	// reverse y or not
	if (!is_reverse_y) {
		index_y_start	= 0;
		index_y_next	= 1;
	} else {
		index_y_start	= h - 1;
		index_y_next	= -1;
	}

	// first calculate x_half and y_half to save time for later work
	double x_half = double(w) / 2.0;
	double y_half = double(h) / 2.0;

	// loop through all pixel
	int index	= 0;
	int index_x	= index_x_start;
	int index_y	= index_y_start;

	for (int y = 0; y < h; y++) {

		index_x = index_x_start;
		for (int x = 0; x < w; x++) {

			const double u = (double(index_x) - x_half) / x_half;
			const double v = (double(index_y) - y_half) / y_half;

			Vec3f result = tracer.trace(container_camera->getObject(), u, v, depth);
			pixel[index + 0] = result[0];
			pixel[index + 1] = result[1];
			pixel[index + 2] = result[2];

			index_x += index_x_next;
			index	+= 3;
		}

		index_y	+= index_y_next;
	}

	return 0;
}


// camera
Dynamic_constructTypeInterface(Camera, Camera, &camera_list);


// TODO: backup
// EXPORT_DLL(int) RayTracer_Camera_create(int type) {
// 	return Dynamic_Container_create<Camera>(&camera_list, type);
// }


// EXPORT_DLL(int) RayTracer_Camera_destroy(int index) {
// 	return Dynamic_Container_destroy<Camera>(&camera_list, index);
// }


// EXPORT_DLL(int) RayTracer_Camera_config(int index, int type, uint8_t *data, uint32_t size) {
// 	return Dynamic_Container_config<Camera>(&camera_list, index, type, data, size);
// }


// EXPORT_DLL(int) RayTracer_Camera_interact(int index, int type, int *index_list, int *type_list, uint32_t size) {
// 	return Dynamic_Container_interact<Camera>(&camera_list, index, type, index_list, type_list, size);
// }


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


// TODO: backup
// mapper
// EXPORT_DLL(int) RayTracer_Mapper_create(int type) {
// 	return Dynamic_Container_create<Mapper>(&mapper_list, type);
// }


// EXPORT_DLL(int) RayTracer_Mapper_destroy(int index) {
// 	return Dynamic_Container_destroy<Mapper>(&mapper_list, index);
// }


// EXPORT_DLL(int) RayTracer_Mapper_config(int index, int type, uint8_t *data, uint32_t size) {
// 	return Dynamic_Container_config<Mapper>(&mapper_list, index, type, data, size);
// }


// EXPORT_DLL(int) RayTracer_Mapper_interact(int index, int type, int *index_list, int *type_list, uint32_t size) {
// 	return Dynamic_Container_interact<Mapper>(&mapper_list, index, type, index_list, type_list, size);
// }


// surface
Dynamic_constructTypeInterface(Surface, Surface, &surface_list);


// TODO: backup
// EXPORT_DLL(int) RayTracer_Surface_create(int type) {
// 	return Dynamic_Container_create<Surface>(&surface_list, type);
// }


// EXPORT_DLL(int) RayTracer_Surface_destroy(int index) {
// 	return Dynamic_Container_destroy<Surface>(&surface_list, index);
// }


// EXPORT_DLL(int) RayTracer_Surface_config(int index, int type, uint8_t *data, uint32_t size) {
// 	return Dynamic_Container_config<Surface>(&surface_list, index, type, data, size);
// }


// EXPORT_DLL(int) RayTracer_Surface_interact(int index, int type, int *index_list, int *type_list, uint32_t size) {
// 	return Dynamic_Container_interact<Surface>(&surface_list, index, type, index_list, type_list, size);
// }


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


// EXPORT_DLL(int) RayTracer_Surface_convertToTexture(int index_surface, int index_texture) {
// 	Dynamic_Container<Surface> *container_surface = surface_list.get(index_surface);
// 	if (container_surface == nullptr) return -1;

// 	Dynamic_Container<Texture> *container_texture = texture_list.get(index_texture);
// 	if (container_texture == nullptr) return -1;

// 	// need to check type of texture
// 	// which need to be Texture_Image
// 	if (container_texture->type != TypeTexture::TEXTURE_IMAGE) return -1;

// 	if (!container_surface->getObject()->convertToTexture((Texture_Image*)(container_texture->object))) return -1;
// 	return 0;
// }


// texture
Dynamic_constructTypeInterface(Texture, Texture, &texture_list);

// TODO: backup
// EXPORT_DLL(int) RayTracer_Texture_create(int type) {
// 	return Dynamic_Container_create<Texture>(&texture_list, type);
// }


// EXPORT_DLL(int) RayTracer_Texture_destroy(int index) {
// 	return Dynamic_Container_destroy<Texture>(&texture_list, index);
// }


// EXPORT_DLL(int) RayTracer_Texture_interact(int index, int type, int *index_list, int *type_list, uint32_t size) {
// 	return Dynamic_Container_interact<Texture>(&texture_list, index, type, index_list, type_list, size);
// }


// EXPORT_DLL(int) RayTracer_Texture_config(int index, int type, uint8_t *data, uint32_t size) {
// 	return Dynamic_Container_config<Texture>(&texture_list, index, type, data, size);
// }


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


// TODO: backup
// EXPORT_DLL(int) RayTracer_Texture_addMapper(int index_texture, int index_mapper) {
// 	Dynamic_Container<Texture>	*container_texture	= texture_list.get(index_texture);
// 	if (container_texture == nullptr) return -1;

// 	Dynamic_Container<Mapper>	*container_mapper	= mapper_list.get(index_mapper);
// 	if (container_mapper == nullptr) return -1;

// 	if (!container_texture->getObject()->addMapper(container_mapper->getObject())) return -1;
// 	return 0;
// }	


// TODO: backup
// EXPORT_DLL(int) RayTracer_Texture_rmMapper(int index_texture, int index_mapper) {
// 	Dynamic_Container<Texture>	*container_texture	= texture_list.get(index_texture);
// 	if (container_texture == nullptr) return -1;

// 	Dynamic_Container<Mapper>	*container_mapper	= mapper_list.get(index_mapper);
// 	if (container_mapper == nullptr) return -1;

// 	if (!container_texture->getObject()->rmMapper(container_mapper->getObject())) return -1;
// 	return 0;
// }


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


// TODO: backup
// EXPORT_DLL(int) RayTracer_Scatter_create(int type) {
// 	return Dynamic_Container_create<Scatter>(&scatter_list, type);
// }


// EXPORT_DLL(int) RayTracer_Scatter_destroy(int index) {
// 	return Dynamic_Container_destroy<Scatter>(&scatter_list, index);
// }


// EXPORT_DLL(int) RayTracer_Scatter_interact(int index, int type, int *index_list, int *type_list, uint32_t size) {
// 	return Dynamic_Container_interact<Scatter>(&scatter_list, index, type, index_list, type_list, size);
// }


// EXPORT_DLL(int) RayTracer_Scatter_config(int index, int type, uint8_t *data, uint32_t size) {
// 	return Dynamic_Container_config<Scatter>(&scatter_list, index, type, data, size);
// }


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


// TODO: backup
// EXPORT_DLL(int) RayTracer_SceneObject_Hitable_create(int type) {
// 	return Dynamic_Container_create<SceneObject_Hitable>(&hitable_list, type);
// }


// EXPORT_DLL(int) RayTracer_SceneObject_Hitable_destroy(int index) {
// 	return Dynamic_Container_destroy<SceneObject_Hitable>(&hitable_list, index);
// }


// EXPORT_DLL(int) RayTracer_SceneObject_Hitable_interact(int index, int type, int *index_list, int *type_list, uint32_t size) {
// 	return Dynamic_Container_interact<SceneObject_Hitable>(&hitable_list, index, type, index_list, type_list, size);
// }


// EXPORT_DLL(int) RayTracer_SceneObject_Hitable_config(int index, int type, uint8_t *data, uint32_t size) {
// 	return Dynamic_Container_config<SceneObject_Hitable>(&hitable_list, index, type, data, size);
// }


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


// light
Dynamic_constructTypeInterface(SceneObject_Light, SceneObject_Light, &light_list);


// TODO: backup
// EXPORT_DLL(int) RayTracer_SceneObject_Light_create(int type) {
// 	return Dynamic_Container_create<SceneObject_Light>(&light_list, type);
// }


// EXPORT_DLL(int) RayTracer_SceneObject_Light_destroy(int index) {
// 	return Dynamic_Container_destroy<SceneObject_Light>(&light_list, index);
// }


// EXPORT_DLL(int) RayTracer_SceneObject_Light_interact(int index, int type, int *index_list, int *type_list, uint32_t size) {
// 	return Dynamic_Container_interact<SceneObject_Light>(&light_list, index, type, index_list, type_list, size);
// }


// EXPORT_DLL(int) RayTracer_SceneObject_Light_config(int index, int type, uint8_t *data, uint32_t size) {
// 	return Dynamic_Container_config<SceneObject_Light>(&light_list, index, type, data, size);
// }


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
