#include "../inc/RayTracer_RIAS_AABB.cuh"


// Define
// ...


// Typedef
// ...


// Static Data
static Hitable_AABB*	*buffer_hitable	= nullptr;
static AABB*			*buffer_aabb	= nullptr;

static compare_func_t	compare_func_list[] = {
	compare_x_axis,
	compare_y_axis,
	compare_z_axis
};


// Static Function Prototype
// host
__host__ static void			host_createHitable			(Hitable_AABB* *dst);
__host__ static void			host_createAABB				(AABB* *dst, AABB *aabb_left, AABB *aabb_right, SceneObject_Hitable *hitable_left, SceneObject_Hitable *hitable_right);
__host__ static inline void		host_getBounding			(RecordBounding *record_list, SceneObject_Hitable* *hitable_list, int32_t size);
__host__ static void			host_buildTree				(AABB* *dst, RecordBounding *record_list, int32_t size);

// global
__global__ static void			global_createHitable		(Hitable_AABB* *dst);
__global__ static void			global_createAABB			(AABB* *dst, AABB *aabb_left, AABB *aabb_right, SceneObject_Hitable *hitable_left, SceneObject_Hitable *hitable_right);
__global__ static void			global_getBounding			(RecordBounding *record_list, SceneObject_Hitable* *hitable_list, int32_t size, int32_t offset);
__global__ static void			global_setRoot				(Hitable_AABB *hitable_aabb, AABB *aabb);

// compare function
__host__ static inline int32_t	select_compare_func			(RecordBounding *record_list, int32_t size);
__host__ static fp_t			get_diff					(RecordBounding *record_list, int32_t size, int32_t axis);
__host__ static int32_t			compare_x_axis				(const void *a, const void *b);
__host__ static int32_t			compare_y_axis				(const void *a, const void *b);
__host__ static int32_t			compare_z_axis				(const void *a, const void *b);

// device
// ...


// Operation Handling
__host__ RIAS_AABB() {
}


__host__ ~RIAS_AABB() {
}


// TODO: not yet corrected
__host__ virtual error_t RIAS_AABB::load(SceneObject_Hitable* *hitable_list, int32_t size) {
	// create hitable
	host_createHitable(&hitable);

	// TODO: not yet corrected
	// get bounding
	RecordBounding *record_list;
	record_list = (RecordBounding*)malloc(size * sizeof(RecordBounding));

	host_getBounding(record_list, hitable_list, size);

	// build tree
	// TODO: should global_aabb_setRoot be inside host_aabb_buildTree ?
	AABB *aabb_device;
	host_buildTree(&aabb_device, record_list, size);
	global_setRoot <<< 1, 1 >>> (hitable, aabb_device);

	// free space
	free(record_list);

	return ERROR_NO;
}


// Static Function Implementation
// host
__host__ static void host_createHitable(Hitable_AABB* *dst) {
	// check if need to allocate buffer
	if (buffer_hitable == nullptr) cudaMalloc(&buffer_hitable, sizeof(Hitable_AABB*));

	// create hitable
	global_createHitable <<< 1, 1 >>> (buffer_hitable);

	// transfer this pointer from device to host
	cudaMemcpy(dst, buffer_hitable, sizeof(Hitable_AABB*), cudaMemcpyDeviceToHost);
}


__host__ static void host_createAABB(
	AABB* *dst, 
	AABB *aabb_left, AABB *aabb_right, SceneObject_Hitable *hitable_left, SceneObject_Hitable *hitable_right) {

	// check if need to allocate buffer
	if (buffer_aabb == nullptr) cudaMalloc(&buffer_aabb, sizeof(AABB*));

	// create aabb
	global_createAABB <<< 1, 1 >>> (buffer_aabb, aabb_left, aabb_right, hitable_left, hitable_right);

	// transfer this pointer from device to host
	cudaMemcpy(dst, buffer_aabb, sizeof(AABB*), cudaMemcpyDeviceToHost);
}


__host__ static inline void host_getBounding(RecordBounding *record_list, SceneObject_Hitable* *hitable_list, int32_t size) {
	RecordBounding			*record_list_device;
	SceneObject_Hitable*	*hitable_list_device;

	// allocate device space
	cudaMalloc(&record_list_device, size * sizeof(RecordBounding));
	cudaMalloc(&hitable_list_device, size * sizeof(SceneObject_Hitable*));
	
	// transfer hitable_list from host to device
	cudaMemcpy(hitable_list_device, hitable_list, size * sizeof(SceneObject_Hitable*), cudaMemcpyHostToDevice);

	// TODO: the number of thread should be dynamic
	global_getBounding <<< 1, 10 >>> (record_list_device, hitable_list_device, size, 10);

	// transfer record_list from device to host
	cudaMemcpy(record_list, record_list_device, size * sizeof(RecordBounding), cudaMemcpyDeviceToHost);

	// free device space
	cudaFree(record_list_device);
	cudaFree(hitable_list_device);
}


__host__ static void host_buildTree(AABB* *dst, RecordBounding *record_list, int32_t size) {	
	// base case
	// when size <= 2, then this aabb node is a leaf
	if (size == 0) {
		host_createAABB(dst, nullptr, nullptr, nullptr, nullptr);
		return;
	}

	if (size == 1) {
		host_createAABB(dst, nullptr, nullptr, record_list[0].hitable, nullptr);
		return;
	}

	if (size == 2) {
		host_createAABB(dst, nullptr, nullptr, record_list[0].hitable, record_list[1].hitable);
		return;
	}

	// recursive case
	// sort the list
	int32_t index_compare = select_compare_func(record_list, size);
	qsort(record_list, size, sizeof(RecordBounding), compare_func_list[index_compare]);

	// build the tree recursively
	AABB *left, *right;
	host_buildTree(&left, record_list, size / 2);
	host_buildTree(&right, record_list + size / 2, size - size / 2);
	
	// build this level of aabb
	host_createAABB(dst, left, right, nullptr, nullptr);
}


// global
__global__ static void global_createHitable(Hitable_AABB* *dst) {
	*dst = new Hitable_AABB();
}


__global__ static void global_createAABB(AABB* *dst, AABB *aabb_left, AABB *aabb_right, SceneObject_Hitable *hitable_left, SceneObject_Hitable *hitable_right) {
	*dst = new AABB(aabb_left, aabb_right, hitable_left, hitable_right);
}


__global__ static void global_getBounding(RecordBounding *record_list, SceneObject_Hitable* *hitable_list, int32_t size, int32_t offset) {
	// parallle processing
	int32_t global_index = blockIdx.x * blockDim.x + threadIdx.x; 

	// just copying (copy constructor)
	for (int32_t i = 0; i < size; i += offset) {
		if (i + global_index >= size) continue;

		record_list[i + global_index].bounding		= hitable_list[i + global_index]->bounding;
		record_list[i + global_index].hitable		= hitable_list[i + global_index];
	}
}


__global__ static void global_setRoot(Hitable_AABB *hitable_aabb, AABB *aabb) {
	hitable_aabb->setAABB(aabb);
}


// device
// ...


// compare function
__host__ static inline int32_t select_compare_func(RecordBounding *record_list, int32_t size) {
	/* The purpose of this function is to find out in which axis
	   the sorting will result the best / better for tree building

	   Currently, it is achieved by find the diff between min and max of the value of
	   midpoint of bounding box in each axis
	   The larger the differences for the axis
	   the larger the possibility that the sort in this axis will be better
	 */

	 // find the difference of min and max
	 fp_t diff_x = get_diff(record_list, size, 0);
	 fp_t diff_y = get_diff(record_list, size, 1);
	 fp_t diff_z = get_diff(record_list, size, 2);

	 // return the axis index
	 return diff_x > diff_y && diff_x > diff_z ? 0 : diff_y > diff_z ? 1 : 2;
}


__host__ static fp_t get_diff(RecordBounding *record_list, int32_t size, int32_t axis) {
	if (size == 0) return 0;

	fp_t min_, max_, mid;
	mid = 
		record_list[0].bounding.min_[axis] + 
		(record_list[0].bounding.max_[axis] - record_list[0].bounding.min_[axis]) / 2;
	
	min_ = mid;
	max_ = mid;

	for (int32_t i = 1; i < size; ++i) {
		mid = 
			record_list[i].bounding.min_[axis] + 
			(record_list[i].bounding.max_[axis] - record_list[i].bounding.min_[axis]) / 2;

		min_ = std::min<fp_t>(mid, min_);
		max_ = std::max<fp_t>(mid, max_);
	}

	// return std::abs<int32_t>(max_ - min_);
	return max_ - min_;
}


__host__ static int32_t compare_x_axis(const void *a, const void *b) {
	RecordBounding *bounding_1 = (RecordBounding*)a;
	RecordBounding *bounding_2 = (RecordBounding*)b;

	int32_t	mid_1	= bounding_1->bounding.min_[0] + bounding_1->bounding.max_[0];
	int32_t	mid_2	= bounding_2->bounding.min_[0] + bounding_2->bounding.max_[0];

	// compare by mid-point32_t of hitable
	if (mid_1 < mid_2)	return -1;
	if (mid_1 == mid_2)	return 0;
	return 1;
}


__host__ static int32_t compare_y_axis(const void *a, const void *b) {
	RecordBounding *bounding_1 = (RecordBounding*)a;
	RecordBounding *bounding_2 = (RecordBounding*)b;

	int32_t	mid_1	= bounding_1->bounding.min_[1] + bounding_1->bounding.max_[1];
	int32_t	mid_2	= bounding_2->bounding.min_[1] + bounding_2->bounding.max_[1];

	// compare by mid-point32_t of hitable
	if (mid_1 < mid_2)	return -1;
	if (mid_1 == mid_2)	return 0;
	return 1;
}


__host__ static int32_t compare_z_axis(const void *a, const void *b) {
	RecordBounding *bounding_1 = (RecordBounding*)a;
	RecordBounding *bounding_2 = (RecordBounding*)b;

	int32_t	mid_1	= bounding_1->bounding.min_[2] + bounding_1->bounding.max_[2];
	int32_t	mid_2	= bounding_2->bounding.min_[2] + bounding_2->bounding.max_[2];

	// compare by mid-point32_t of hitable
	if (mid_1 < mid_2)	return -1;
	if (mid_1 == mid_2)	return 0;
	return 1;
}
