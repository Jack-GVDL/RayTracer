#include "../inc/Util_Vector.cuh"


// Define
// TODO: this value should not be in define region
#define FACTOR_EXTEND	2


// Typedef
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// __init__
__device__ Vector::Vector() {
	cudaMalloc(&list, size);
}


__device__ Vector::Vector(int32_t size) {
	this->base	= size;
	this->size	= base;
	cudaMalloc(&list, size);
}


__device__ Vector::~Vector() {
}


// operation
__device__ void Vector::push_back(void *data, int32_t s) {
	// check if need to push
	if (index + s > size) {

		// find the size need to extend
		int size_new = size;
		while (size_new < index + s) size_new *= FACTOR_EXTEND;

		// allocate new space
		uint8_t *list_new;
		cudaMalloc(&list_new, size_new);

		// copy to new space
		// cudaMemcpyAsync(list_new, list, index, cudaMemcpyDeviceToDevice);
		memcpy(list_new, list, index);

		// update list info
		size = size_new;
		list = list_new;
	}

	// add data to the list
	// copy to the list
	// cudaMemcpyAsync(list + index, data, s, cudaMemcpyDeviceToDevice);
	memcpy(list + index, data, s);
	index += s;
}


// TODO: not yet completed
/*
__device__ void Vector::pop_back(int32_t s) {
}


__device__ void Vector::front() {
}


__device__ void Vector::back() {
}
*/


// Static Function Implementation
// ...
