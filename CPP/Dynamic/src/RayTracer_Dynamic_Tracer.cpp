#include <stdint.h>
#include "../../Tracer/Tracer.hpp"
#include "../inc/RayTracer_DynamicContainer.hpp"
#include "../inc/RayTracer_Dynamic_Tracer.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// static function so function name isn't that serious
static void	fix_index	(int *index_x_start, int *index_y_start, int *index_x_next, int *index_y_next, int w, int h, int is_reverse_x, int is_reverse_y);


// Static Data
extern	RayTracer						tracer;
extern	Dynamic_ContainerList<Camera>	camera_list;


// Operation Handling
int	RayTracer_Dynamic_Tracer_tracePoint_RGB888(int index_camera, void *data, int w, int h, int depth, int is_reverse_x, int is_reverse_y) {
	// pointer casting
	uint8_t *pixel = (uint8_t*)data;
	
	// get camera
	Dynamic_Container<Camera> *container_camera = camera_list.get(index_camera);
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
	fix_index(&index_x_start, &index_y_start, &index_x_next, &index_y_next, w, h, is_reverse_x, is_reverse_y);

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
			pixel[index + 0] = (result[0] * 255);
			pixel[index + 1] = (result[1] * 255);
			pixel[index + 2] = (result[2] * 255);

			index_x += index_x_next;
			index	+= 3;
		}

		index_y	+= index_y_next;
	}

	return 0;
}


int	RayTracer_Dynamic_Tracer_tracePoint_RGB64F(int index_camera, void *data, int w, int h, int depth, int is_reverse_x, int is_reverse_y) {
	// pointer casting
	double *pixel = (double*)data;
	
	// get camera
	Dynamic_Container<Camera> *container_camera = camera_list.get(index_camera);
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
	fix_index(&index_x_start, &index_y_start, &index_x_next, &index_y_next, w, h, is_reverse_x, is_reverse_y);

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


// Static Function Implementation
static void fix_index(
	int *index_x_start, int *index_y_start, int *index_x_next, int *index_y_next, 
	int w, int h, int is_reverse_x, int is_reverse_y) {

	// reverse x or not
	if (!is_reverse_x) {
		*index_x_start	= 0;
		*index_x_next	= 1;
	} else {
		*index_x_start	= w - 1;
		*index_x_next	= -1;
	}

	// reverse y or not
	if (!is_reverse_y) {
		*index_y_start	= 0;
		*index_y_next	= 1;
	} else {
		*index_y_start	= h - 1;
		*index_y_next	= -1;
	}
}
