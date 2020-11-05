#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>


__host__ int main(void) {
	int				dev		= 0;
	cudaDeviceProp 	dev_prop;

	cudaGetDeviceProperties(&dev_prop, dev);

	printf("GPU Device              %s \n",		dev_prop.name);
	printf("SM                      %i \n",		dev_prop.multiProcessorCount);
	printf("Shared Memory per Block %i KB \n",	dev_prop.sharedMemPerBlock / 1024);
	printf("Max Thread per Block    %i \n",		dev_prop.maxThreadsPerBlock);
	printf("Max Thread per SM       %i \n",		dev_prop.maxThreadsPerMultiProcessor);
	printf("Max WARP per SM         %i \n",		dev_prop.maxThreadsPerMultiProcessor / 32);

	return 0;
}
