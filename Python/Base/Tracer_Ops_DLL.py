from typing import List, Tuple
import ctypes
from ctypes import c_int, c_int32, c_double, c_uint8, c_uint32, c_char, c_char_p, c_void_p
from ctypes import CDLL
from .Tracer_Vec3f import Vec3f
from .Tracer_Ops import Ops_Tracer
import os
import time
import numpy as np


class Ops_Tracer_DLL(Ops_Tracer):

	def __init__(self):
		super().__init__()

		# data
		# self._is_started:	bool	= False
		# self._file_tracer:	str		= ""

		self._dll_tracer:	CDLL	= None

	# Operation
	# TODO: future: previous dll handling
	def setDLL_tracer(self, dll: CDLL) -> None:
		self._dll_tracer = dll

	# TODO: future: previous dll handling
	def setDLLPath_tracer(self, path: str) -> None:
		dll: CDLL = CDLL(path)
		self._dll_tracer = dll

	# main
	def RayTracer_init(self) -> None:
		self._dll_tracer.RayTracer_init()

	def RayTracer_del(self) -> None:
		self._dll_tracer.RayTracer_del()

	def RayTracer_info(self) -> None:
		self._dll_tracer.RayTracer_info()

	# test
	def Test_testDoubleArray(self, array: List[float], size: int) -> None:
		array_pixel = (c_double * size)(*array)
		self._dll_tracer.RayTracer_Test_testDoubleArray(array_pixel, c_uint32(size))

	def Test_testUint8Array(self, array: bytes, size: int) -> None:
		array_pixel = (c_uint8 * size)(*array)
		self._dll_tracer.RayTracer_Test_testUint8Array(array_pixel, c_uint32(size))

	def Test_checkStatus(self, index: int, array: bytes, size: int) -> None:
		array_pixel	= (c_uint8 * size)(*array)
		self._dll_tracer.RayTracer_Test_checkStatus(c_int(index), array_pixel, c_uint32(size))

	# sample
	def Sample_buildScene(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Sample_buildScene(c_int(index))

	# tracer
	def Tracer_tracePoint(self, index_camera: int, pixel: Vec3f, x: float, y: float, depth: int) -> int:
		array_pixel = (c_double * 3)(*pixel.array)
		result: int = self._dll_tracer.RayTracer_Tracer_tracePoint(c_int(index_camera), array_pixel, c_double(x), c_double(y), c_int(depth))

		pixel[0] = array_pixel[0]
		pixel[1] = array_pixel[1]
		pixel[2] = array_pixel[2]

		return result

	def Tracer_traceRect(
			self, index_camera: int, pixel_list: np.ndarray, w: int, h: int, depth: int,
			is_reverse_x: bool, is_reverse_y: bool, format_: int) -> int:

		# TODO: test
		time_start = time.time()

		result: int = self._dll_tracer.RayTracer_Tracer_traceRect(
			c_int(index_camera), pixel_list.ctypes.data_as(ctypes.c_void_p), c_int(w), c_int(h), c_int(depth),
			c_int(1 if is_reverse_x else 0), c_int(1 if is_reverse_y else 0),
			c_int(0))

		# TODO: test
		print("Trace time: ", time.time() - time_start)

		return result

	# camera
	def Camera_Type_getIndex(self, name: str) -> int:
		byte_str: bytes = name.encode('utf-8')
		return self._dll_tracer.RayTracer_Camera_Type_getIndex(c_char_p(byte_str))

	def Camera_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Camera_create(c_int(type_))

	def Camera_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Camera_destroy(c_int(index))

	def Camera_config(self, index: int, type_: int, data: bytes) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		size		= len(data)
		array_data	= (c_uint8 * size)(*data)
		return self._dll_tracer.RayTracer_Camera_config(c_int(index), c_int(type_), array_data, c_uint32(size))

	def Camera_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		size		= len(index_list)
		array_index = (c_int * size)(*index_list)
		array_type	= (c_int * size)(*type_list)
		return self._dll_tracer.RayTracer_Camera_interact(c_int(index), c_int(type_), array_index, array_type, c_int(size))

	def Camera_setLookFrom(self, index: int, look_from: Vec3f) -> int:
		array_data = (c_double * 3)(*look_from)
		return self._dll_tracer.RayTracer_Camera_setLookFrom(c_int(index), array_data)

	def Camera_setLookAt(self, index: int, look_at: Vec3f) -> int:
		array_data = (c_double * 3)(*look_at)
		return self._dll_tracer.RayTracer_Camera_setLookAt(c_int(index), array_data)

	def Camera_setUpDirection(self, index: int, up_dir: Vec3f) -> int:
		array_data = (c_double * 3)(*up_dir)
		return self._dll_tracer.RayTracer_Camera_setUpDirection(c_int(index), array_data)

	def Camera_setFOV(self, index: int, value: float) -> int:
		return self._dll_tracer.RayTracer_Camera_setFOV(c_int(index), c_double(value))

	def Camera_setAspectRatio(self, index: int, value: float) -> int:
		return self._dll_tracer.RayTracer_Camera_setAspectRatio(c_int(index), c_double(value))

	# surface
	def Surface_Type_getIndex(self, name: str) -> int:
		byte_str: bytes = name.encode('utf-8')
		return self._dll_tracer.RayTracer_Surface_Type_getIndex(c_char_p(byte_str))

	def Surface_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Surface_create(c_int(type_))

	def Surface_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Surface_destroy(c_int(index))

	def Surface_config(self, index: int, type_: int, data: bytes) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		size		= len(data)
		array_data	= (c_uint8 * size)(*data)
		return self._dll_tracer.RayTracer_Surface_config(c_int(index), c_int(type_), array_data, c_uint32(size))

	def Surface_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		size		= len(index_list)
		array_index = (c_int * size)(*index_list)
		array_type	= (c_int * size)(*type_list)
		return self._dll_tracer.RayTracer_Surface_interact(c_int(index), c_int(type_), array_index, array_type, c_int(size))

	def Surface_load(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Surface_load(c_int(index))

	def Surface_dump(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Surface_dump(c_int(index))

	# texture
	def Texture_Type_getIndex(self, name: str) -> int:
		byte_str: bytes = name.encode('utf-8')
		return self._dll_tracer.RayTracer_Texture_Type_getIndex(c_char_p(byte_str))

	def Texture_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Texture_create(c_int(type_))

	def Texture_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Texture_destroy(c_int(index))

	def Texture_config(self, index: int, type_: int, data: bytes) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		size		= len(data)
		array_data	= (c_uint8 * size)(*data)
		return self._dll_tracer.RayTracer_Texture_config(c_int(index), c_int(type_), array_data, c_int(size))

	def Texture_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		size		= len(index_list)
		array_index = (c_int * size)(*index_list)
		array_type	= (c_int * size)(*type_list)
		return self._dll_tracer.RayTracer_Texture_interact(c_int(index), c_int(type_), array_index, array_type, c_int(size))

	def Texture_addInput(self, index_texture: int, index_input: int, offset: int) -> int:
		return self._dll_tracer.RayTracer_Texture_addInput(c_int(index_texture), c_int(index_input), c_int(offset))

	def Texture_rmInput(self, index: int, offset: int) -> int:
		return self._dll_tracer.RayTracer_Texture_rmInput(c_int(index), c_int(offset))

	def Texture_setPixel(self, index: int, pixel: Vec3f, point: Vec3f) -> int:
		array_point = (c_double * 3)(*point.array)
		array_pixel	= (c_double * 3)(*pixel.array)

		result: int = self._dll_tracer.RayTracer_Texture_setPixel(c_int(index), array_pixel, array_point)
		return result

	def Texture_getPixel(self, index: int, pixel: Vec3f, point: Vec3f) -> int:
		array_point = (c_double * 3)(*point.array)
		array_pixel = (c_double * 3)(*pixel.array)

		result: int = self._dll_tracer.RayTracer_Texture_getPixel(c_int(index), array_pixel, array_point)

		pixel[0] = array_pixel[0]
		pixel[1] = array_pixel[1]
		pixel[2] = array_pixel[2]

		return result

	# material
	def Material_Type_getIndex(self, name: str) -> int:
		byte_str: bytes = name.encode('utf-8')
		return self._dll_tracer.RayTracer_Material_Type_getIndex(c_char_p(byte_str))

	def Material_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Material_create(c_int(type_))

	def Material_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Material_destroy(c_int(index))

	def Material_config(self, index: int, type_: int, data: bytes) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		size		= len(data)
		array_data	= (c_uint8 * size)(*data)
		return self._dll_tracer.RayTracer_Material_config(c_int(index), c_int(type_), array_data, c_int(size))

	def Material_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		size		= len(index_list)
		array_index = (c_int * size)(*index_list)
		array_type	= (c_int * size)(*type_list)
		return self._dll_tracer.RayTracer_Material_interact(c_int(index), c_int(type_), array_index, array_type, c_int(size))

	def Material_addScatter(self, index_material: int, index_scatter: int) -> int:
		return self._dll_tracer.RayTracer_Material_addScatter(c_int(index_material), c_int(index_scatter))

	def Material_rmScatter(self, index_material: int, index_scatter: int) -> int:
		return self._dll_tracer.RayTracer_Material_rmScatter(c_int(index_material), c_int(index_scatter))

	def Material_setTransmissive(self, index: int, transmissive: Vec3f) -> int:
		array = (c_double * 3)(*transmissive.array)
		return self._dll_tracer.RayTracer_Material_setTransmissive(c_int(index), array)

	def Material_setIndex(self, index: int, value: float) -> int:
		return self._dll_tracer.RayTracer_Material_setIndex(c_int(index), c_double(value))

	# scatter
	def Scatter_Type_getIndex(self, name: str) -> int:
		byte_str: bytes = name.encode('utf-8')
		return self._dll_tracer.RayTracer_Scatter_Type_getIndex(c_char_p(byte_str))

	def Scatter_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Scatter_create(c_int(type_))

	def Scatter_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Scatter_destroy(c_int(index))

	def Scatter_config(self, index: int, type_: int, data: bytes) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		size		= len(data)
		array_data	= (c_uint8 * size)(*data)
		return self._dll_tracer.RayTracer_Scatter_config(c_int(index), c_int(type_), array_data, c_int(size))

	def Scatter_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		size		= len(index_list)
		array_index = (c_int * size)(*index_list)
		array_type	= (c_int * size)(*type_list)
		return self._dll_tracer.RayTracer_Scatter_interact(c_int(index), c_int(type_), array_index, array_type, c_int(size))

	def Scatter_setTexture(self, index_scatter: int, index_texture: int, offset: int) -> int:
		return self._dll_tracer.RayTracer_Scatter_setTexture(c_int(index_scatter), c_int(index_texture), c_int(offset))

	def Scatter_addScatter(self, index_scatter: int, index_target: int) -> int:
		return self._dll_tracer.RayTracer_Scatter_addScatter(c_int(index_scatter), c_int(index_target))

	def Scatter_rmScatter(self, index_scatter: int, index_target: int) -> int:
		return self._dll_tracer.RayTracer_Scatter_rmScatter(c_int(index_scatter), c_int(index_target))

	# hitable
	def Hitable_Type_getIndex(self, name: str) -> int:
		byte_str: bytes = name.encode('utf-8')
		return self._dll_tracer.RayTracer_Hitable_Type_getIndex(c_char_p(byte_str))

	def Hitable_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Hitable_create(c_int(type_))

	def Hitable_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Hitable_destroy(c_int(index))

	def Hitable_config(self, index: int, type_: int, data: bytes) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		size		= len(data)
		array_data	= (c_uint8 * size)(*data)
		return self._dll_tracer.RayTracer_Hitable_config(c_int(index), c_int(type_), array_data, c_int(size))

	def Hitable_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		size		= len(index_list)
		array_index = (c_int * size)(*index_list)
		array_type	= (c_int * size)(*type_list)
		return self._dll_tracer.RayTracer_Hitable_interact(c_int(index), c_int(type_), array_index, array_type, c_int(size))

	def Hitable_setMaterial(self, index_hitable: int, index_material: int) -> int:
		return self._dll_tracer.RayTracer_Hitable_setMaterial(c_int(index_hitable), c_int(index_material))

	# aabb
	def RIAS_Type_getIndex(self, name: str) -> int:
		byte_str: bytes = name.encode('utf-8')
		return self._dll_tracer.RayTracer_RIAS_Type_getIndex(c_char_p(byte_str))

	def RIAS_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_RIAS_create(c_int(type_))

	def RIAS_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_RIAS_destroy(c_int(index))

	def RIAS_config(self, index: int, type_: int, data: bytes) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		size		= len(data)
		array_data	= (c_uint8 * size)(*data)
		return self._dll_tracer.RayTracer_RIAS_config(c_int(index), c_int(type_), array_data, c_int(size))

	def RIAS_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		size		= len(index_list)
		array_index = (c_int * size)(*index_list)
		array_type	= (c_int * size)(*type_list)
		return self._dll_tracer.RayTracer_RIAS_interact(c_int(index), c_int(type_), array_index, array_type, c_int(size))

	def RIAS_load(self, index: int) -> int:
		return self._dll_tracer.RayTracer_RIAS_load(c_int(index))

	# light
	def Light_Type_getIndex(self, name: str) -> int:
		byte_str: bytes = name.encode('utf-8')
		return self._dll_tracer.RayTracer_Light_Type_getIndex(c_char_p(byte_str))

	def Light_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Light_create(c_int(type_))

	def Light_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Light_destroy(c_int(index))

	def Light_config(self, index: int, type_: int, data: bytes) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		size		= len(data)
		array_data	= (c_uint8 * size)(*data)
		return self._dll_tracer.RayTracer_Light_config(c_int(index), c_int(type_), array_data, c_int(size))

	def Light_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		size		= len(index_list)
		array_index = (c_int * size)(*index_list)
		array_type	= (c_int * size)(*type_list)
		return self._dll_tracer.RayTracer_Light_interact(c_int(index), c_int(type_), array_index, array_type, c_int(size))

	def Light_setOrigin(self, index: int, origin: Vec3f) -> int:
		array_origin = (c_double * 3)(*origin.array)

		result: int = self._dll_tracer.RayTracer_Light_setOrigin(c_int(index), array_origin)
		return result

	def Light_setColor(self, index: int, color: Vec3f) -> int:
		array_color = (c_double * 3)(*color.array)

		result: int = self._dll_tracer.RayTracer_Light_setColor(c_int(index), array_color)
		return result

	# scene
	def Scene_addLight(self, index_light: int) -> int:
		return self._dll_tracer.RayTracer_Scene_addLight(c_int(index_light))

	def Scene_addHitable(self, index_hitable: int) -> int:
		return self._dll_tracer.RayTracer_Scene_addHitable(c_int(index_hitable))

	def Scene_addRIAS(self, index_rias: int) -> int:
		return self._dll_tracer.RayTracer_Scene_addRIAS(c_int(index_rias))

	def Scene_rmLight(self, index_light: int) -> int:
		return self._dll_tracer.RayTracer_Scene_rmLight(c_int(index_light))

	def Scene_rmHitable(self, index_hitable: int) -> int:
		return self._dll_tracer.RayTracer_Scene_rmHitable(c_int(index_hitable))

	def Scene_rmRIAS(self, index_rias: int) -> int:
		return self._dll_tracer.RayTracer_Scene_rmRIAS(c_int(index_rias))

	# sampler
	def Sampler_Type_getIndex(self, name: str) -> int:
		byte_str: bytes = name.encode('utf-8')
		return self._dll_tracer.RayTracer_Light_Type_getIndex(c_char_p(byte_str))

	def Sampler_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Sampler_create(c_int(type_))

	def Sampler_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Sampler_destroy(c_int(index))

	def Sampler_config(self, index: int, type_: int, data: bytes) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		size		= len(data)
		array_data	= (c_uint8 * size)(*data)
		return self._dll_tracer.RayTracer_Sampler_config(c_int(index), c_int(type_), array_data, c_int(size))

	def Sampler_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		size		= len(index_list)
		array_index = (c_int * size)(*index_list)
		array_type	= (c_int * size)(*type_list)
		return self._dll_tracer.RayTracer_Sampler_interact(c_int(index), c_int(type_), array_index, array_type, c_int(size))

	def Sampler_setSizeImage(self, index: int, w: int, h: int) -> int:
		array_dimension = (c_int32 * 2)()
		array_dimension[0] = w
		array_dimension[1] = h
		return self._dll_tracer.RayTracer_Sampler_setSizeImage(c_int(index), array_dimension)

