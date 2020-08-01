#include "../inc/RayTracer_Dynamic.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
EXPORT_DLL(void) RayTracer_Test_testDoubleArray(double *array, uint32_t size) {
	// show value
	printf("Double Array: size: %i ", (int)size);

	printf(", array: ");
	for (int i = 0; i < size; i++) printf("%f ", array[i]);
	printf("\n");

	// change value
	for (int i = 0; i < size; i++) array[i] = i / 10;
}


EXPORT_DLL(void) RayTracer_Test_testUint8Array(uint8_t *array, uint32_t size) {
	// show value
	printf("Uint8 Array: size: %i ", (int)size);
	
	printf(", array: ");
	for (int i = 0; i < size; i++) printf("%X ", (int)(array[i]));
	printf("\n");

	// chage value
	for (int i = 0; i < size; i++) array[i] = (uint8_t)(i);
}


// TODO: not yet completed
EXPORT_DLL(int) RayTracer_Test_checkStatus(int index, uint8_t *data, uint32_t size) {
	return -1;
}


// Static Function Implementation
// ...
