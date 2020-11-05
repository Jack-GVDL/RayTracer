FLAG	=
FLAG	+= -I D:\NvidiaCuda\Toolkit\CUDA_110\include
FLAG	+= -I D:\NvidiaCuda\Sample\Cuda_110\common\inc

LIB		=
LIB		+= -lcudart

all:
	nvcc CudaInfo.cu $(FLAG) $(LIB) -o CudaInfo.exe
	./CudaInfo.exe
