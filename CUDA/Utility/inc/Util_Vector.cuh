// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/13   initial update


#ifndef UTIL_VECTOR_CUH
#define UTIL_VECTOR_CUH


#include <stdint.h>


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
class Vector {
// Data
public:
	uint8_t		*list	= nullptr;
	int32_t		size	= 16;
	int32_t		index	= 0;
	int32_t		base	= 16;

// Operation
public:
	// __init__
	__device__			Vector		();
	__device__			Vector		(int32_t size);
	__device__			~Vector		();

	// operation
	__device__ void		push_back	(void *data, int32_t size);
	
	// TODO: not yet completed
	/*
	__device__ void	pop_back	(int32_t size);

	__device__ void	front		();
	__device__ void	back		();
	*/
};


// Macro Function
// ...


// Operation Handling
// ...


// Inline Function Implementation
// ...


#endif  // UTIL_VECTOR_CUH
