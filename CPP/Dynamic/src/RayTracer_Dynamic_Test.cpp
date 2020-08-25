#include <stdio.h>
#include "../inc/RayTracer_DynamicContainer.hpp"
#include "../inc/RayTracer_Dynamic.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
static void	print_status_container_list	();
static void	print_status_object_list	();
static void	print_status_scene_tree		();


// Static Data
extern RayTracer									tracer;
extern Scene										scene;

extern Dynamic_ContainerList<Camera>				camera_list;
extern Dynamic_ContainerList<Surface>				surface_list;
extern Dynamic_ContainerList<Texture>				texture_list;
extern Dynamic_ContainerList<Scatter>				scatter_list;
extern Dynamic_ContainerList<SceneObject_Hitable>	hitable_list;
extern Dynamic_ContainerList<SceneObject_Light>		light_list;


// Operation Handling
EXPORT_DLL(void) RayTracer_Test_testDoubleArray(double *array, uint32_t size) {
	// show value
	printf("Double Array: size: %i ", (int)size);

	printf(", array: ");
	for (int i = 0; i < size; i++) printf("%f ", array[i]);
	printf("\n");

	// change value
	for (int i = 0; i < size; i++) array[i] = i / 10;
}


EXPORT_DLL(void) RayTracer_Test_testUint8Array(uint8_t *array, uint32_t size) {
	// show value
	printf("Uint8 Array: size: %i ", (int)size);
	
	printf(", array: ");
	for (int i = 0; i < size; i++) printf("%X ", (int)(array[i]));
	printf("\n");

	// chage value
	for (int i = 0; i < size; i++) array[i] = (uint8_t)(i);
}


EXPORT_DLL(int) RayTracer_Test_checkStatus(int index, uint8_t *data, uint32_t size) {
	switch (index) {
		case 0:
			print_status_container_list();
			return 0;

		case 1:
			print_status_object_list();
			return 0;

		case 2:
			print_status_scene_tree();
			return 0;

		default:
			return -1;
	}
}


// TODO: not yet completed
EXPORT_DLL(int) RayTracer_Test_setPrintInfo(int is_enabled) {
	return -1;
}


// Static Function Implementation
static void print_status_container_list() {
	printf("Camera:              size: %i \n",	camera_list.size()	);
	printf("Surface:             size: %i \n",	surface_list.size()	);
	printf("Texture:             size: %i \n",	texture_list.size()	);
	printf("Scatter:             size: %i \n",	scatter_list.size()	);
	printf("SceneObject Hitable: size: %i \n",	hitable_list.size()	);
	printf("SceneObject Light:   size: %i \n",	light_list.size()	);
}


static void print_status_object_list() {
	// scene
	// ...

	// hitable
	// printf("Hitable \n");
	// for (auto *hitable : hitable_list.container_list) {
	// }

	// light
	// ...
}


static void print_status_scene_tree() {

}
