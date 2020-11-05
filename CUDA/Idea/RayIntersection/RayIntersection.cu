#include <stdio.h>
#include <cuda_runtime.h>
#include <helper_functions.h>
#include <helper_cuda.h>
#include "RayTracer_Vec3f.hpp"


typedef float fp_t;
// typedef float3 Vec3f_Device;


template <class T>
inline __device__ T max(T x, T y) {
	return x > y ? x : y;
}


template <class T>
inline __device__ T min(T x, T y) {
	return  x < y ? x : y;
}


// Data Structure
class Vec3f_Device {
	// Data
	public:
		fp_t n[3];

	// Operation
	public:
		// init
		__device__ Vec3f_Device() { 
			n[0] = 0.0; 
			n[1] = 0.0; 
			n[2] = 0.0;
		}

		__device__ Vec3f_Device(fp_t n0) {
			n[0] = n0;
			n[1] = n0;
			n[2] = n0;
		}

		__device__ Vec3f_Device(fp_t n0, fp_t n1, fp_t n2) {
			n[0] = n0; 
			n[1] = n1; 
			n[2] = n2;
		}

		__device__ Vec3f_Device(const Vec3f_Device &v) {
			n[0] = v.n[0];
			n[1] = v.n[1];
			n[2] = v.n[2];
		}

		// operator
		__device__	fp_t			operator	[]	( int i )			const { return n[i]; }
		__device__	fp_t&			operator	[]	( int i )			{ return n[i]; }

		__device__	const Vec3f_Device&	operator	+	()					const { return *this; }
		__device__	Vec3f_Device			operator	-	()					const { return Vec3f_Device(-n[0], -n[1], -n[2]); }

		__device__	Vec3f_Device&			operator	=	( const Vec3f_Device &v )	{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[2]; return *this; }
		__device__	Vec3f_Device&			operator	+=	( const Vec3f_Device &v )	{ n[0] += v.n[0]; n[1] += v.n[1]; n[2] += v.n[2]; return *this; }
		__device__	Vec3f_Device&			operator	-=	( const Vec3f_Device &v )	{ n[0] -= v.n[0]; n[1] -= v.n[1]; n[2] -= v.n[2]; return *this; }
		__device__	Vec3f_Device&			operator	*=	( const Vec3f_Device &v )	{ n[0] *= v.n[0]; n[1] *= v.n[1]; n[2] *= v.n[2]; return *this; }
		__device__	Vec3f_Device&			operator	/=	( const Vec3f_Device &v )	{ n[0] /= v.n[0]; n[1] /= v.n[1]; n[2] /= v.n[2]; return *this; }

		__device__	Vec3f_Device&			operator	*=	( const fp_t d )	{ n[0] *= d; n[1] *= d; n[2] *= d; return *this; }
		__device__	Vec3f_Device&			operator	/=	( const fp_t d )	{ n[0] /= d; n[1] /= d; n[2] /= d; return *this; }

		// Math Operation
		// TODO: clamp (0.0 <= n[i] <= 1.0)

		Vec3f_Device __device__ clamp(fp_t val_min, fp_t val_max) const {
			return Vec3f_Device(
				max(val_min, min(n[0], val_max)),
				max(val_min, min(n[1], val_max)),
				max(val_min, min(n[2], val_max)));
		}

		bool __device__ isZero() const {
			return n[0] == 0 && n[1] == 0 && n[2] == 0;
		}

		Vec3f_Device __device__ cross(const Vec3f_Device &v) const {
			return Vec3f_Device(
			n[1] * v[2] - n[2] * v[1],
			n[2] * v[0] - n[0] * v[2],
			n[0] * v[1] - n[1] * v[0] );
		}

		fp_t __device__ dot(const Vec3f_Device &v) const {
			return n[0] * v[0] + n[1] * v[1] + n[2] * v[2];
		}

		Vec3f_Device __device__ prod(const Vec3f_Device &v) const {
			return Vec3f_Device(n[0] * v[0], n[1] * v[1], n[2] * v[2]);
		}

		// reference
		// 1. https://en.wikipedia.org/wiki/Vector_projection
		fp_t __device__ projectLength(const Vec3f_Device &v) const {
			fp_t dot_result	= dot(v);
			fp_t length_v2	= v.lengthSquared();
			return dot_result / length_v2;
		}

		// reference
		// 1. https://en.wikipedia.org/wiki/Vector_projection
		// projection of a on b = a.dot(b) / b.lengthSquared() * b
		Vec3f_Device __device__ projectOn(const Vec3f_Device &v) const {
			fp_t length		= projectLength(v);
			return Vec3f_Device(length * v[0], length * v[1], length * v[2]);
		}

		Vec3f_Device __device__ normalize() const {
			Vec3f_Device ret (*this);
			ret /= length();
			return ret;
		}

		fp_t __device__ length() const {
			return sqrt(lengthSquared());
		}

		fp_t __device__ lengthSquared() const {
			return n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
		}
};


inline __device__ Vec3f_Device operator+(const Vec3f_Device &v1, const Vec3f_Device &v2) {
	return Vec3f_Device(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}


inline __device__ Vec3f_Device operator-(const Vec3f_Device &v1, const Vec3f_Device &v2) {
	return Vec3f_Device(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}


inline __device__ Vec3f_Device operator*(const Vec3f_Device &v1, const Vec3f_Device &v2) {
	return Vec3f_Device(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}


inline __device__ Vec3f_Device operator/(const Vec3f_Device &v1, const Vec3f_Device &v2) {
	return Vec3f_Device(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}


inline __device__ Vec3f_Device operator*(fp_t t, const Vec3f_Device &v) {
	return Vec3f_Device(t * v[0], t * v[1], t * v[2]);
}


inline __device__ Vec3f_Device operator/(Vec3f_Device v, fp_t t) {
	return Vec3f_Device(v[0] / t, v[1] /  t, v[2] / t);
}


inline __device__ Vec3f_Device operator*(const Vec3f_Device &v, fp_t t) {
	return Vec3f_Device(t * v[0], t * v[1], t * v[2]);
}


inline __device__ bool operator==(const Vec3f_Device &v1, const Vec3f_Device &v2) {
	return v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2];
}


struct Ray_Device {
	Vec3f_Device	pos;
	Vec3f_Device	dir;

	__device__ Vec3f_Device getPosition() const {
		return pos;
	}

	__device__ Vec3f_Device getDirection() const {
		return dir;
	}
};


class Hitable_Sphere_Device {
	// Data
	public:
		fp_t	radius;
		Vec3f_Device	center;

	// Operation
	public:
		__device__ bool intersect(Vec3f_Device &normal, fp_t *distance, const Ray_Device *ray, fp_t t_min, fp_t t_max) const {
			Vec3f_Device	oc	= ray->pos - center;

			fp_t	a	= ray->dir.dot(ray->dir);
			fp_t	b	= oc.dot(ray->dir);
			fp_t	c	= oc.dot(oc) - radius * radius;

			fp_t	discriminant	= b * b - a * c;

			// no intersection
			if (discriminant <= 0) return false;

			// find the length of the ray
			// check if the ray is hit within the range
			fp_t	ray_length;

			ray_length = (-b - sqrt(b * b - a * c)) / a;
			if (ray_length < t_max && ray_length > t_min) goto RAY_HIT;

			ray_length = (-b + sqrt(b * b - a * c)) / a;
			if (ray_length < t_max && ray_length > t_min) goto RAY_HIT;

			return false;

			// ray hit the object within the range
			// need to set the content of hit record
			RAY_HIT:
			*distance	= ray_length;
			normal		= (ray->pos + ray_length * ray->dir).normalize();

			return true;
 		}
};


class Hitable_Sphere {
	// Data
	public:
		fp_t			radius;
		Vec3f			center;
};


struct RecordRender {
	int		size_hitable;
	int		width;
	int		height;
};


// CUDA Function
__device__ float get_random(unsigned int *seed0, unsigned int *seed1) {
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);  // hash the seeds using bitwise AND and bitshifts
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);
   
	unsigned int ires = ((*seed0) << 16) + (*seed1);
   
	// convert to float
	union {
		float			f;
		unsigned int	ui;
	} res;
   
	res.ui = (ires & 0x007fffff) | 0x40000000;  // bitwise AND, bitwise OR
   
	return (res.f - 2.f) / 2.f;
}


__device__ bool intersect_scene(const Ray_Device *ray, Hitable_Sphere_Device *scene, int size_hitable) {
	for (int i = 0; i < size_hitable; ++i) {
		
		Vec3f_Device	normal;
		fp_t	distance;
		
		// TODO: select a better t_max
		if (!scene[i].intersect(normal, &distance, ray, 0, 8192.0f)) continue;
		return true;
	}

	return false;
}


// __global__: executed on the device (GPU) and callable onbly from host (CPU)
// this kernel runs in parallel on all the CUDA threads
__global__ void render_kernel(Vec3f_Device *output, Hitable_Sphere_Device *scene, RecordRender *record_render) {

	// assign a CUDA thread to every pixel (x, y)
	// blockIdx, blockDim, threadIdex are CUDA specific keywords
	// replaces nested outer loops in CPU code looping over image rows and image columns
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	// int i = (record_render->height - y - 1) * record_render->width + x;  // index of current pixel (calculated using thread index)
	int i = y * record_render->width + x;

	// unsigned int s1 = x;  // seeds for random number generator
	// unsigned int s2 = y;

	// generate ray directed at lower left corner of the screen
	// compute direction of all other rays by adding cx and cy increments in x and y direction
	Ray_Device ray;
	ray.pos = Vec3f_Device(0.0f, 0.0f, 0.0f);
	// ray.dir	= Vec3f_Device(
	// 	0.0f + ((float)x - (record_render->width / 2)) / (record_render->width), 
	// 	0.0f + ((float)y - (record_render->height / 2)) / (record_render->height), 
	// 	1.0f);

	Vec3f_Device result;

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			ray.dir	= Vec3f_Device(
				0.0f + ((float)x - (record_render->width / 2) + ((float)i - 4.0) / 8) / (record_render->width), 
				0.0f + ((float)y - (record_render->height / 2) + ((float)j - 4.0) / 8) / (record_render->height), 
				1.0f);

			result += intersect_scene(&ray, scene, record_render->size_hitable) ? Vec3f_Device(1.0 / 64.0, 1.0 / 64.0, 1.0 / 64.0) : Vec3f_Device();
		}
	}

	output[i] = result;
}


int main(void) {
	// MARK: message
	printf("Main started \n");

	const int width		= 128;
	const int height	= 128;

	// data - output
	printf("Data: Output \n");

	Vec3f			*output_host;
	Vec3f_Device	*output_device;

	output_host	= new Vec3f[width * height];
	cudaMalloc(&output_device, width * height * sizeof(Vec3f_Device));

	// data - scene
	printf("Data: Scene \n");
	
	Hitable_Sphere 			*hitable_host;
	Hitable_Sphere_Device	*hitable_device;

	hitable_host = new Hitable_Sphere[1];
	hitable_host[0].radius = 0.5;
	hitable_host[0].center = Vec3f(0, 0, 2);

	cudaMalloc(&hitable_device, 1 * sizeof(Hitable_Sphere_Device));
	cudaMemcpy(hitable_device, hitable_host, 1 * sizeof(Hitable_Sphere_Device), cudaMemcpyHostToDevice);

	// data - render
	printf("Data: Render \n");

	RecordRender record_render_host;
	RecordRender *record_render_device;

	record_render_host.size_hitable	= 1;
	record_render_host.width		= width;
	record_render_host.height		= height;
	
	cudaMalloc(&record_render_device, sizeof(RecordRender));
	cudaMemcpy(record_render_device, &record_render_host, sizeof(RecordRender), cudaMemcpyHostToDevice);

	// dim3 is CUDA specific type, block and grid are required to schedule CUDA threads over streaming multiprocessors
	dim3	threads	= dim3(8, 8);
	dim3	blocks	= dim3(width / threads.x, height / threads.y);
	
	// MARK: messaging
	printf("CUDA initiaized \n");
	printf("Start rendering... \n");

	// record time
	float gpu_time = 0.0f;

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	// StopWatchInterface *timer = NULL;
	// sdkCreateTimer(&timer);
	// sdkResetTimer(&timer);
	// checkCudaErrors(cudaDeviceSynchronize());

	// schedule threads on device and launch CUDA kernel from host
	// then copy result of computation from device back to host
	// sdkStartTimer(&timer);
	cudaEventRecord(start);

	render_kernel<<<blocks, threads>>>(output_device, hitable_device, record_render_device);
	checkCudaErrors(cudaMemcpy(output_host, output_device, width * height * sizeof(Vec3f_Device), cudaMemcpyDeviceToHost));
	
	// sdkStopTimer(&timer);
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);

	// show time
	checkCudaErrors(cudaEventElapsedTime(&gpu_time, start, stop));
	printf("Time elapsed: %f \n", gpu_time);

	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	
	// free CUDA memory
	checkCudaErrors(cudaFree(output_device));
	checkCudaErrors(cudaFree(hitable_device));
	checkCudaErrors(cudaFree(record_render_device));

	// MARK: messaging
	printf("Done\n");

	// write image to PPM file
	FILE *f = fopen("result.ppm", "w");
	fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);

	// loop over pixels, write RGB
	for (int i = 0; i < width * height; ++i) {
		fprintf(f, "%d %d %d \n", 
			(int)(output_host[i][0] * 255),
			(int)(output_host[i][1] * 255),
			(int)(output_host[i][2] * 255));
	}

	printf("Saved image to 'result.ppm'\n");

	delete[] output_host;
	delete[] hitable_host;
	printf("Done \n");
	
	return 0;
}
