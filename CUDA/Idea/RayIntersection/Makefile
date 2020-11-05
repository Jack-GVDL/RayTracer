CU_FLAG	=
CU_FLAG += -I D:\NvidiaCuda\Toolkit\CUDA_110\include
CU_FLAG += -I D:\NvidiaCuda\Sample\Cuda_110\common\inc


all:
	nvcc RayIntersection.cu $(CU_FLAG) -o RayIntersection
	RayIntersection.exe

run:
	RayIntersection.exe
