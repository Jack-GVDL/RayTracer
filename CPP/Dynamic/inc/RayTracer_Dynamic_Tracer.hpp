// Created by Jack Tse on 2020/08/25
//
// Log
// 2020/08/25   initial update


#ifndef RAYTRACER_DYNAMIC_TRACER_HPP
#define RAYTRACER_DYNAMIC_TRACER_HPP


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
// ...


// Macro Function
// ...


// Operation Handling
int	RayTracer_Dynamic_Tracer_tracePoint_RGB888(int index_camera, void *data, int w, int h, int depth, int is_reverse_x, int is_reverse_y);
int	RayTracer_Dynamic_Tracer_tracePoint_RGB64F(int index_camera, void *data, int w, int h, int depth, int is_reverse_x, int is_reverse_y);  // 64-bit floating point array, aka double


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAMIC_TRACER_HPP
