// This test file is to test if Vec3f can be function properly


#include <stdio.h>
#include "../Utility.cuh"


// device
__global__ void increment_1(Vec3f *list, int size) {
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < size) list[i] += 1;
}


// host
int main() {
	// data
	printf("Stage: Data \n");
	const int size = 1000;

	Vec3f *vec_list_host;
	Vec3f *vec_list_device;

	vec_list_host = (Vec3f*)malloc(size * sizeof(Vec3f));
	cudaMalloc(&vec_list_device, size * sizeof(Vec3f));

	for (int i = 0; i < size; ++i) vec_list_host[i] = Vec3f(i, i + 1, i + 2);
	cudaMemcpy(vec_list_device, vec_list_host, size * sizeof(Vec3f), cudaMemcpyHostToDevice);

	// kernel
	printf("Stage: Kernel \n");
	increment_1<<< (size + 255) / 256, 256 >>>(vec_list_device, size);

	// copy back
	printf("Stage: Copy back \n");
	cudaMemcpy(vec_list_host, vec_list_device, size * sizeof(Vec3f), cudaMemcpyDeviceToHost);

	// result
	printf("Stage: Result \n");
	for (int i = 0; i < size; ++i) {
		if (vec_list_host[i][0] == i + 0 + 1 &&
			vec_list_host[i][1] == i + 1 + 1 &&
			vec_list_host[i][2] == i + 2 + 1) continue;

		printf("Error \n");
		break;
	}
	
	return 0;
}
