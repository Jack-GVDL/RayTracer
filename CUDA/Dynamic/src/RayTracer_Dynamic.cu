#include <stdio.h>
#include <vector>
#include <string>

#include "../inc/RayTracer_DynamicContainer.cuh"
#include "../inc/RayTracer_DynamicSkeleton.cuh"

#include "../inc/RayTracer_Dynamic_Camera.cuh"
#include "../inc/RayTracer_Dynamic_Tracer.cuh"
#include "../inc/RayTracer_Dynamic_Surface.cuh"
#include "../inc/RayTracer_Dynamic_Texture.cuh"
#include "../inc/RayTracer_Dynamic_Scatter.cuh"
#include "../inc/RayTracer_Dynamic_Hitable.cuh"
#include "../inc/RayTracer_Dynamic_AABB.cuh"
#include "../inc/RayTracer_Dynamic_Light.cuh"
#include "../inc/RayTracer_Dynamic_Material.cuh"

#include "../inc/RayTracer_Dynamic.cuh"


// Define
#define BUFFER_MAX_LENGTH	8


#define Dynamic_constructTypeInterface_Type_getIndex(name, type, container_list)												\
																																\
EXPORT_DLL(int) RayTracer_##name##_Type_getIndex(const char *name_) {													\
	return Dynamic_ContainerList_Type_getIndex<type>(container_list, name_);													\
}


#define Dynamic_constructTypeInterface_Object_create(name, type, container_list)												\
																																\
EXPORT_DLL(int) RayTracer_##name##_create(int type_) {																	\
	return Dynamic_ContainerList_Object_create<type>(container_list, type_);													\
}


#define Dynamic_constructTypeInterface_Object_destroy(name, type, container_list)												\
																																\
EXPORT_DLL(int) RayTracer_##name##_destroy(int index) {																\
	return Dynamic_ContainerList_Object_destroy<type>(container_list, index);													\
}


#define Dynamic_constructTypeInterface_Object_config(name, type, container_list)												\
																																\
EXPORT_DLL(int) RayTracer_##name##_config(int index, int type_, uint8_t *data, uint32_t size) {						\
	return Dynamic_ContainerList_Object_config<type>(container_list, index, type_, data, size);									\
}


#define Dynamic_constructTypeInterface_Object_interact(name, type, container_list)												\
																																\
EXPORT_DLL(int) RayTracer_##name##_interact(int index, int type_, int *index_list, int *type_list, uint32_t size) {	\
	return Dynamic_ContainerList_Object_interact<type>(container_list, index, type_, index_list, type_list, size);				\
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
Dynamic_ContainerList<Camera>					camera_list;
Dynamic_ContainerList<Surface>					surface_list;
Dynamic_ContainerList<Texture>					texture_list;
Dynamic_ContainerList<Scatter>					scatter_list;
Dynamic_ContainerList<SceneObject_Hitable>		hitable_list;
Dynamic_ContainerList<SceneObject_Light>		light_list;
// Dynamic_ContainerList<Hitable_AABB>				aabb_list;
Dynamic_ContainerList<Material>					material_list;

Dynamic_ContainerListBase*				container_list[] = {
	&camera_list,
	&surface_list,
	&texture_list,
	&material_list,
	&scatter_list,
	&hitable_list,
	&light_list,
	// &aabb_list
};


// Operation Handling
EXPORT_DLL(void) RayTracer_init() {
	// init
	RayTracer_Dynamic_Tracer_init();

	RayTracer_Dynamic_Camera_init(		&(camera_list.type_list)	);
	RayTracer_Dynamic_Surface_init(		&(surface_list.type_list)	);
	RayTracer_Dynamic_Texture_init(		&(texture_list.type_list)	);
	RayTracer_Dynamic_Material_init(	&(material_list.type_list)	);
	RayTracer_Dynamic_Scatter_init(		&(scatter_list.type_list)	);
	RayTracer_Dynamic_Hitable_init(		&(hitable_list.type_list)	);
	// RayTracer_Dynamic_AABB_init(		&(aabb_list.type_list)		);
	RayTracer_Dynamic_Light_init(		&(light_list.type_list)		);

	// load
	camera_list.Type_load();
	surface_list.Type_load();
	texture_list.Type_load();
	material_list.Type_load();
	scatter_list.Type_load();
	hitable_list.Type_load();
	light_list.Type_load();
	// aabb_list.Type_load();

	// create a deafult camera
	// can / should be used for testing
	RayTracer_Camera_create(0);
	Dynamic_Container<Camera> *container_camera = camera_list.get(1);
	Dynamic_Camera_setLookFrom(		container_camera->getObject(), Vec3f(0, 0, 1));
	Dynamic_Camera_setLookAt(		container_camera->getObject(), Vec3f(0, 0, 0));
	Dynamic_Camera_setUpDirection(	container_camera->getObject(), Vec3f(0, 1, 0));
	Dynamic_Camera_setFOV(			container_camera->getObject(), 90);
	Dynamic_Camera_setAspectRatio(	container_camera->getObject(), 2);
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

	return ERROR_ANY;

}


// camera
Dynamic_constructTypeInterface(Camera, Camera, &camera_list);


EXPORT_DLL(int) RayTracer_Camera_setLookFrom(int index, double *look_from) {
	Dynamic_Container<Camera> *camera = camera_list.get(index);
	if (camera == nullptr) return ERROR_ANY;

	// TODO: remove
	// container_camera->getObject()->setLookFrom(Vec3f(look_from[0], look_from[1], look_from[2]));
	
	Dynamic_Camera_setLookFrom(camera->getObject(), Vec3f(look_from[0], look_from[1], look_from[2]));
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Camera_setLookAt(int index, double *look_at) {
	Dynamic_Container<Camera> *camera = camera_list.get(index);
	if (camera == nullptr) return ERROR_ANY;

	// TODO: remove
	// container_camera->getObject()->setLookAt(Vec3f(look_at[0], look_at[1], look_at[2]));
	
	Dynamic_Camera_setLookAt(camera->getObject(), Vec3f(look_at[0], look_at[1], look_at[2]));
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Camera_setUpDirection(int index, double *up_dir) {
	Dynamic_Container<Camera> *camera = camera_list.get(index);
	if (camera == nullptr) return -1;

	// TODO: remove
	// container_camera->getObject()->setUpDirection(Vec3f(up_dir[0], up_dir[1], up_dir[2]));

	Dynamic_Camera_setUpDirection(camera->getObject(), Vec3f(up_dir[0], up_dir[1], up_dir[2]));
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Camera_setFOV(int index, double value) {
	Dynamic_Container<Camera> *camera = camera_list.get(index);
	if (camera == nullptr) return -1;

	// TODO: remove
	// container_camera->getObject()->setFOV(value);
	
	Dynamic_Camera_setFOV(camera->getObject(), value);
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Camera_setAspectRatio(int index, double value) {
	Dynamic_Container<Camera> *camera = camera_list.get(index);
	if (camera == nullptr) return -1;

	// TODO: remove
	// container_camera->getObject()->setAspectRatio(value);

	Dynamic_Camera_setAspectRatio(camera->getObject(), value);
	return ERROR_NO;
}


// surface
Dynamic_constructTypeInterface(Surface, Surface, &surface_list);


EXPORT_DLL(int) RayTracer_Surface_load(int index) {
	Dynamic_Container<Surface> *surface = surface_list.get(index);
	if (surface == nullptr) return -1;

	// TODO: remove
	// if (!container_surface->getObject()->load()) return -1;
	
	if (!Dynamic_Surface_load(surface->getObject()) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Surface_dump(int index) {
	Dynamic_Container<Surface> *surface = surface_list.get(index);
	if (surface == nullptr) return -1;

	// TODO: remove
	// if (!container_surface->getObject()->dump()) return -1;
	
	if (!Dynamic_Surface_dump(surface->getObject()) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


// texture
Dynamic_constructTypeInterface(Texture, Texture, &texture_list);


EXPORT_DLL(int) RayTracer_Texture_addInput(int index_output, int index_input, int offset) {
	Dynamic_Container<Texture> *texture = texture_list.get(index_output);
	if (texture == nullptr) return -1;

	Dynamic_Container<Texture> *input = texture_list.get(index_input);
	if (input == nullptr) return -1;

	// TODO: remove
	// if (!texture->getObject()->addInput(container_input->getObject(), offset)) return -1;
	
	if (!Dynamic_Texture_addInput(texture->getObject(), input->getObject(), offset) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Texture_rmInput(int index_output, int offset) {
	Dynamic_Container<Texture> *texture = texture_list.get(index_output);
	if (texture == nullptr) return ERROR_ANY;

	// TODO: remove
	// if (!texture->getObject()->rmInput(offset)) return ERROR_ANY;
	
	if (!Dynamic_Texture_rmInput(texture->getObject(), offset) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Texture_setPixel(int index, const double *pixel, const double *point) {
	Dynamic_Container<Texture> *texture = texture_list.get(index);
	if (texture == nullptr) return ERROR_ANY;

	// TODO: remove
	// texture->getObject()->setPixel(
	// 	Vec3f(point[0], point[1], point[2]),
	// 	Vec3f(pixel[0], pixel[1], pixel[2]));

	Dynamic_Texture_setPixel(
		texture->getObject(),
		Vec3f(point[0], point[1], point[2]),
		Vec3f(pixel[0], pixel[1], pixel[2]));
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Texture_getPixel(int index, double *pixel, const double *point) {
	Dynamic_Container<Texture> *texture = texture_list.get(index);
	if (texture == nullptr) return ERROR_ANY;

	Vec3f vec_pixel;
	
	// TODO: remove
	// texture->getObject()->getPixel(vec_pixel, Vec3f(point[0], point[1], point[2]));
	
	Dynamic_Texture_getPixel(texture->getObject(), vec_pixel, Vec3f(point[0], point[1], point[2]));

	pixel[0] = vec_pixel[0];
	pixel[1] = vec_pixel[1];
	pixel[2] = vec_pixel[2];

	return ERROR_NO;
}


// material
Dynamic_constructTypeInterface(Material, Material, &material_list);


EXPORT_DLL(int) RayTracer_Material_addScatter(int index, int index_scatter) {
	// get container
	Dynamic_Container<Material>	*material = material_list.get(index);
	if (material == nullptr) return ERROR_ANY;

	Dynamic_Container<Scatter> *scatter = scatter_list.get(index_scatter);
	if (scatter == nullptr) return ERROR_ANY;

	// add scatter

	// TODO: remove
	// if (!material->getObject()->addScatter(scatter->getObject())) return ERROR_ANY;
	
	if (!Dynamic_Material_addScatter(material->getObject(), scatter->getObject()) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Material_rmScatter(int index, int index_scatter) {
	// get container
	Dynamic_Container<Material>	*material = material_list.get(index);
	if (material == nullptr) return ERROR_ANY;

	Dynamic_Container<Scatter> *scatter = scatter_list.get(index_scatter);
	if (scatter == nullptr) return ERROR_ANY;

	// remove scatter
	
	// TODO: remove
	// if (!material->getObject()->rmScatter(scatter->getObject())) return ERROR_ANY;
	
	if (!Dynamic_Material_rmScatter(material->getObject(), scatter->getObject()) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Material_setTransmissive(int index, double *transmissive) {
	Dynamic_Container<Material>	*material = material_list.get(index);
	if (material == nullptr) return ERROR_ANY;

	// TODO: remove
	// material->getObject()->transmissive->setPixel(
	// 	Vec3f(),
	// 	Vec3f(transmissive[0], transmissive[1], transmissive[2]));
	
	Dynamic_Material_setTransmissive(
		material->getObject(), 
		Vec3f(transmissive[0], transmissive[1], transmissive[2]));
	
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Material_setIndex(int index, double value) {
	Dynamic_Container<Material>	*material = material_list.get(index);
	if (material == nullptr) return ERROR_ANY;

	// TODO: remove
	// material->getObject()->index = value;
	
	Dynamic_Material_setIndex(material->getObject(), value);
	return ERROR_NO;
}


// scatter
Dynamic_constructTypeInterface(Scatter, Scatter, &scatter_list);


EXPORT_DLL(int)RayTracer_Scatter_addScatter(int index_scatter, int index_target) {
	// get container
	Dynamic_Container<Scatter> *scatter = scatter_list.get(index_scatter);
	if (scatter == nullptr) return ERROR_ANY;

	Dynamic_Container<Scatter> *target = scatter_list.get(index_target);
	if (target == nullptr) return ERROR_ANY;

	// add scatter

	// TODO: remove
	// Scatter *scatter	= scatter->getObject();
	// Scatter *target		= target->getObject();
	// if (scatter->addScatter(target) != ERROR_NO) return ERROR_ANY;
	
	if (Dynamic_Scatter_addScatter(scatter->getObject(), target->getObject()) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


EXPORT_DLL(int)RayTracer_Scatter_rmScatter(int index_scatter, int index_target) {
	// get container
	Dynamic_Container<Scatter> *scatter = scatter_list.get(index_scatter);
	if (scatter == nullptr) return ERROR_ANY;

	Dynamic_Container<Scatter> *target = scatter_list.get(index_target);
	if (target == nullptr) return ERROR_ANY;

	// rm scatter

	// TODO: remove
	// Scatter *scatter	= scatter->getObject();
	// Scatter *target		= target->getObject();
	// if (scatter->rmScatter(target) != ERROR_NO) return ERROR_ANY;

	if (Dynamic_Scatter_rmScatter(scatter->getObject(), target->getObject()) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Scatter_setTexture(int index_scatter, int index_texture, int offset) {
	// get container
	Dynamic_Container<Scatter> *scatter = scatter_list.get(index_scatter);
	if (scatter == nullptr) return ERROR_ANY;

	Dynamic_Container<Texture> *texture = texture_list.get(index_texture);
	if (texture == nullptr) return ERROR_ANY;

	// set texture

	// TODO: remove
	// Scatter	*scatter = scatter->getObject();
	// Texture	*texture = texture->getObject();
	// if (!scatter->setTexture(texture, offset)) return ERROR_ANY;

	if (Dynamic_Scatter_setTexture(scatter->getObject(), texture->getObject(), offset) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


// hitable
Dynamic_constructTypeInterface(Hitable, SceneObject_Hitable, &hitable_list);


EXPORT_DLL(int) RayTracer_Hitable_setMaterial(int index_hitable, int index_material) {
	Dynamic_Container<SceneObject_Hitable> *hitable = hitable_list.get(index_hitable);
	if (hitable == nullptr) return ERROR_ANY;

	Dynamic_Container<Material> *material = material_list.get(index_material);
	if (material == nullptr) return ERROR_ANY;

	// TODO: remove
	// hitable->getObject()->setMaterial(material->getObject());
	
	Dynamic_Hitable_setMaterial(hitable->getObject(), material->getObject());
	return ERROR_NO;
}


// aabb
/*
Dynamic_constructTypeInterface(AABB, Hitable_AABB, &aabb_list);


// TODO: should actual aabb load operation be written here ?
EXPORT_DLL(int) RayTracer_AABB_load (int index) {
	Dynamic_Container<Hitable_AABB> *container_aabb = aabb_list.get(index);
	if (container_aabb == nullptr) return ERROR_ANY;

	// get object list
	// TODO: need copy the entire list, may be too slow
	std::vector<SceneObject_Hitable*> hitables;
	for (auto hitable : hitable_list.container_list) {
		hitables.push_back((SceneObject_Hitable*)(hitable->object));
	}

	// aabb loading
	Hitable_AABB *aabb = Hitable_AABB::create(hitables.data(), hitables.size(), 1);
	if (aabb == nullptr) return ERROR_ANY;

	if (container_aabb->getObject()->addHitable(aabb) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}
*/


// light
Dynamic_constructTypeInterface(Light, SceneObject_Light, &light_list);


EXPORT_DLL(int) RayTracer_Light_setOrigin(int index, double *origin) {
	Dynamic_Container<SceneObject_Light> *light = light_list.get(index);
	if (light == nullptr) return ERROR_ANY;

	// TODO: remove
	// light->getObject()->setOrigin(Vec3f(origin[0], origin[1], origin[2]));
	
	Dynamic_Light_setOrigin(light->getObject(), Vec3f(origin[0], origin[1], origin[2]));
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Light_setColor(int index, double *color) {
	Dynamic_Container<SceneObject_Light> *light = light_list.get(index);
	if (light == nullptr) return ERROR_ANY;

	// TODO: remove
	// light->getObject()->setColor(Vec3f(color[0], color[1], color[2]));
	
	Dynamic_Light_setColor(light->getObject(), Vec3f(color[0], color[1], color[2]));
	return ERROR_NO;
}


// scene
EXPORT_DLL(int) RayTracer_Scene_addLight(int index_light) {
	Dynamic_Container<SceneObject_Light> *light = light_list.get(index_light);
	if (light == nullptr) return ERROR_ANY;

	// TODO: remove
	// SceneObject_Light *light = light->getObject();
	// if (!RayTracer_Dynamic_Scene_addLight(light)) return -1;

	if (Dynamic_Scene_addLight(light->getObject()) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Scene_addHitable(int index_hitable) {
	Dynamic_Container<SceneObject_Hitable> *hitable = hitable_list.get(index_hitable);
	if (hitable == nullptr) return ERROR_ANY;

	// TODO: remove
	// SceneObject_Hitable *hitable = hitable->getObject();
	// if (!RayTracer_Dynamic_Scene_addHitable(hitable)) return ERROR_ANY;
	
	if (Dynamic_Scene_addHitable(hitable->getObject()) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


// EXPORT_DLL(int) RayTracer_Scene_addAABB(int index_aabb) {
// 	Dynamic_Container<Hitable_AABB> *container_aabb = aabb_list.get(index_aabb);
// 	if (container_aabb == nullptr) return ERROR_ANY;

// 	Hitable_AABB *aabb = container_aabb->getObject();
// 	if (!scene.addHitable(aabb)) return ERROR_ANY;
// 	return ERROR_NO;
// }


EXPORT_DLL(int) RayTracer_Scene_rmLight(int index_light) {
	Dynamic_Container<SceneObject_Light> *light = light_list.get(index_light);
	if (light == nullptr) return ERROR_ANY;

	// TODO: remove
	// SceneObject_Light *light = light->getObject();
	// if (!RayTracer_Dynamic_Scene_rmLight(light)) return ERROR_ANY;
	
	if (Dynamic_Scene_rmLight(light->getObject()) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


EXPORT_DLL(int) RayTracer_Scene_rmHitable(int index_hitable) {
	Dynamic_Container<SceneObject_Hitable> *hitable = hitable_list.get(index_hitable);
	if (hitable == nullptr) return ERROR_ANY;

	// TODO: remove
	// SceneObject_Hitable *hitable = hitable->getObject();
	// if (!RayTracer_Dynamic_Scene_rmHitable(hitable)) return ERROR_ANY;
	
	if (Dynamic_Scene_rmHitable(hitable->getObject()) != ERROR_NO) return ERROR_ANY;
	return ERROR_NO;
}


// EXPORT_DLL(int) RayTracer_Scene_rmAABB(int index_aabb) {
// 	Dynamic_Container<Hitable_AABB> *container_aabb = aabb_list.get(index_aabb);
// 	if (container_aabb == nullptr) return ERROR_ANY;

// 	Hitable_AABB *aabb = container_aabb->getObject();
// 	if (!scene.rmHitable(aabb)) return ERROR_ANY;
// 	return ERROR_NO;
// }


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
