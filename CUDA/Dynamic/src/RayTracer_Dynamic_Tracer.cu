#include <stdint.h>
#include "../../Tracer/Tracer.cuh"
#include "../inc/RayTracer_DynamicContainer.cuh"
#include "../inc/RayTracer_Dynamic_Tracer.cuh"


// Define
#define SIZE_SCHEDULER	128
#define SIZE_BLOCK		2
#define SIZE_THREAD		64


// Typedef
// ...


// Static Function Prototype
__host__ static void			fix_index						(int *index_x_start, int *index_y_start, int *index_x_next, int *index_y_next, 
																 int w, int h, int is_reverse_x, int is_reverse_y);

__host__ static inline void		host_init						();
__host__ static inline void		host_Tracer_trace				(Camera *camera, fp_t *buffer_list, fp_t *position_list, int32_t size, int32_t depth);
__host__ static inline void		host_Tracer_getPosition			(fp_t *position_list, int32_t w, int32_t h, 
																 int32_t index_x_start, int32_t index_y_start, int32_t index_x_next, int32_t index_y_next);

__global__ static void			global_init						();
__global__ static void			global_Tracer_addScheduler		(int32_t memory_size);
__global__ static void			global_Tracer_trace				(void *camera, fp_t *dst, fp_t *position_list, int32_t offset, int32_t depth);
__global__ static void			global_Tracer_getPosition		(fp_t *position_list, int32_t w, int32_t h,
																 int32_t index_x_start, int32_t index_y_start, int32_t index_x_next, int32_t index_y_next,
																 int32_t offset);
// backup
// __global__ static void			global_Tracer_resetScheduler	();


// Static Data
__device__	Tracer						*tracer;
__device__	Scene						*scene;
extern Dynamic_ContainerList<Camera>	camera_list;


// Operation Handling
__host__ void RayTracer_Dynamic_Tracer_init() {
	host_init();
}


__host__ int RayTracer_Dynamic_Tracer_tracePoint_RGB888(
	int index_camera, void *data, int w, int h, int depth, int is_reverse_x, int is_reverse_y) {

	// get camera
	Dynamic_Container<Camera> *container_camera = camera_list.get(index_camera);
	if (container_camera == nullptr) return ERROR_ANY;

	// allocate for buffer and position
	fp_t *position_device;
	fp_t *buffer_host;
	fp_t *buffer_device;

	buffer_host = (fp_t*)malloc(w * h * 3 * sizeof(fp_t));

	cudaMalloc(&position_device,	w * h * 2 * sizeof(fp_t));
	cudaMalloc(&buffer_device,		w * h * 3 * sizeof(fp_t));

	// based on property of export image
	// order of putting pixel on the linear memory space may be different
	int index_x_start, 		index_y_start;
	int index_x_next, 		index_y_next;
	fix_index(&index_x_start, &index_y_start, &index_x_next, &index_y_next, w, h, is_reverse_x, is_reverse_y);

	// get position list
	host_Tracer_getPosition(position_device, w, h, index_x_start, index_y_start, index_x_next, index_y_next);

	// get trace result
	host_Tracer_trace(container_camera->getObject(), buffer_device, position_device, w * h, depth);
	cudaMemcpy(buffer_host, buffer_device, w * h * 3 * sizeof(fp_t), cudaMemcpyDeviceToHost);

	// convert it from fp_t [0, 1] to RGB888 [0, 255]
	uint8_t *pixel = (uint8_t*)data;
	for (int32_t i = 0; i < w * h * 3; ++i) {
		pixel[i] = (uint8_t)(buffer_host[i] * 255);
	}

	// free space
	free(buffer_host);
	cudaFree(position_device);
	cudaFree(buffer_device);

	return ERROR_NO;
}


// TODO: not yet completed, wait for above code to be finalized
__host__ int RayTracer_Dynamic_Tracer_tracePoint_RGB64F(
	int index_camera, void *data, int w, int h, int depth, int is_reverse_x, int is_reverse_y) {
	
	// get camera
	Dynamic_Container<Camera> *container_camera = camera_list.get(index_camera);
	if (container_camera == nullptr) return ERROR_ANY;

	// allocate for buffer and position
	fp_t *position_device;
	fp_t *buffer_host;
	fp_t *buffer_device;

	buffer_host = (fp_t*)malloc(w * h * 3 * sizeof(fp_t));

	cudaMalloc(&position_device,	w * h * 2 * sizeof(fp_t));
	cudaMalloc(&buffer_device,		w * h * 3 * sizeof(fp_t));

	// based on property of export image
	// order of putting pixel on the linear memory space may be different
	int index_x_start, 		index_y_start;
	int index_x_next, 		index_y_next;
	fix_index(&index_x_start, &index_y_start, &index_x_next, &index_y_next, w, h, is_reverse_x, is_reverse_y);

	// get position list
	host_Tracer_getPosition(position_device, w, h, index_x_start, index_y_start, index_x_next, index_y_next);

	// get trace result
	host_Tracer_trace(container_camera->getObject(), buffer_device, position_device, w * h, depth);
	cudaMemcpy(buffer_host, buffer_device, w * h * 3 * sizeof(fp_t), cudaMemcpyDeviceToHost);

	// convert it from fp_t to double
	double *pixel = (double*)data;
	for (int32_t i = 0; i < w * h * 3; ++i) {
		pixel[i] = (double)(buffer_host[i]);
	}

	// free space
	free(buffer_host);
	cudaFree(position_device);
	cudaFree(buffer_device);

	return ERROR_NO;
}



// TODO: should it be exposed or not ?
__host__ error_t Dynamic_Tracer_addScheduler(int32_t size_memory) {
	global_Tracer_addScheduler <<< 1, 1 >>> (size_memory);
	return ERROR_NO;
}


// backup
/*
__host__ error_t Dynamic_Tracer_resetScheduler() {
	global_Tracer_resetScheduler <<< 1, 1 >>> ();
	return ERROR_NO;
}
*/


// Static Function Implementation
__host__ static void fix_index(
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


// host
__host__ static inline void host_init() {
	// device side
	global_init <<< 1, 1 >>> ();

	// TODO: currently number of scheduler is fixed
	for (int32_t i = 0; i < SIZE_SCHEDULER; ++i) Dynamic_Tracer_addScheduler(1024 * 5 * sizeof(uint8_t));
}


__host__ static inline void host_Tracer_getPosition(
	fp_t *position_list, int32_t w, int32_t h, 
	int32_t index_x_start, int32_t index_y_start, int32_t index_x_next, int32_t index_y_next) {

	global_Tracer_getPosition <<< 1, 100 >>> (
		position_list, w, h, index_x_start, index_y_start, index_x_next, index_y_next, 100);
}


__host__ static inline void host_Tracer_trace(
	Camera *camera, fp_t *buffer_list, fp_t *position_list, int32_t size, int32_t depth) {

	// TODO: currently number of scheduler is fixed
	const int32_t	offset	= SIZE_SCHEDULER;
	int32_t			index	= 0;

	for (int32_t i = 0; i < (size / offset); ++i) {
		global_Tracer_trace <<< 1, SIZE_SCHEDULER >>> (camera, buffer_list, position_list, index, depth);
		index += offset;
	}
}


// global
__global__ static void global_init() {
	tracer	= new Tracer();
	scene	= new Scene();

	// tracer
	tracer->setScene(scene);

	// scene
	// allocate space
	int32_t size_hitable	= 1000;
	int32_t size_light		= 100;

	void	*hitable_list;
	void	*light_list;

	cudaMalloc(&hitable_list,	size_hitable * sizeof(SceneObject_Hitable));
	cudaMalloc(&light_list,		size_light * sizeof(SceneObject_Light));

	scene->allocateHitable(hitable_list, size_hitable);
	scene->allocateLight(light_list, size_light);
}


__global__ static void global_Tracer_addScheduler(int32_t memory_size) {
	// allocate space
	void *memory = nullptr;
	cudaMalloc(&memory, memory_size);

	Scheduler_Scatter *scheduler = new Scheduler_Scatter();
	// cudaMalloc(&scheduler, sizeof(Scheduler_Scatter*));

	// config scheduler
	scheduler->memory_control.setMemory(memory, memory_size);

	// add to tracer
	tracer->addScheduler(scheduler);
}


// backup
/*
__global__ static void global_Tracer_resetScheduler() {
	tracer->resetScheduler();
}
*/


__global__ static void global_Tracer_trace(void *camera, fp_t *dst, fp_t *position_list, int32_t offset, int32_t depth) {
	// get thread-block index (global index)
	// just use int type
	int global_index = blockIdx.x * blockDim.x + threadIdx.x;

	// get pixel intensity
	Vec3f result = tracer->trace(
		(Camera*)camera,
		position_list[(offset + global_index) * 2 + 0],
		position_list[(offset + global_index) * 2 + 1],
		depth, global_index);
	
	// set to dst
	dst[(offset + global_index) * 3 + 0] = result[0];
	dst[(offset + global_index) * 3 + 1] = result[1];
	dst[(offset + global_index) * 3 + 2] = result[2];
}


__global__ static void global_Tracer_getPosition(
	fp_t *position_list, int32_t w, int32_t h, 
	int32_t index_x_start, int32_t index_y_start, int32_t index_x_next, int32_t index_y_next,
	int32_t offset) {

	int global_index = blockIdx.x * blockDim.x + threadIdx.x;

	// first calculate x_half and y_half to save time for later work
	fp_t x_half = fp_t(w) / 2.0;
	fp_t y_half = fp_t(h) / 2.0;

	// loop through all pixel
	// find the corresponding x and y on camera for each output image pixel
	int32_t	index_y	= index_y_start;

	for (int y = 0; y < h; y++) {
		
		for (int x = 0; x < w; x += offset) {
			if (x + global_index >= w) continue;

			const fp_t u = ((fp_t)(index_x_start + index_x_next * (x + global_index)) - x_half) / x_half;
			const fp_t v = ((fp_t)(index_y) - y_half) / y_half;
			
			position_list[(y * w + x + global_index) * 2 + 0] = u;
			position_list[(y * w + x + global_index) * 2 + 1] = v;
		}

		index_y += index_y_next;
	}
}
