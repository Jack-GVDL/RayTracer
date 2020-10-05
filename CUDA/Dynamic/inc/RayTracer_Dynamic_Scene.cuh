// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/10/05   initial update


#ifndef RAYTRACER_DYNAMIC_SCENE_CUH
#define RAYTRACER_DYNAMIC_SCENE_CUH


#include "../../Tracer/Tracer.cuh"


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
__host__ error_t	Dynamic_Scene_addLight		(SceneObject_Light *light);
__host__ error_t	Dynamic_Scene_addHitable	(SceneObject_Hitable *hitable);
__host__ error_t	Dynamic_Scene_rmLight		(SceneObject_Light *light);
__host__ error_t	Dynamic_Scene_rmHitable		(SceneObject_Hitable *hitable);


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAMIC_SCENE_CUH
