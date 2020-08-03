from typing import List
import ctypes
from ctypes import c_int, c_double, c_uint8, c_uint32
from ctypes import CDLL
from .Tracer_Vec3f import Vec3f
from .Tracer_Ops import Tracer_Ops
import os


class Tracer_Ops_DLL(Tracer_Ops):

	def __init__(self):
		super().__init__()

		# data
		# self._is_started:	bool	= False
		# self._file_tracer:	str		= ""

		self._dll_tracer:	CDLL	= None

	# Operation
	# @property
	# def is_started(self) -> bool:
	# 	return self._is_started

	# def setFile_tracer(self, file: str) -> None:
	# 	self._file_tracer = file

	# def start(self) -> bool:
	# 	if self._is_started:
	# 		return False

	# 	# TODO: these code should not be here
	# 	# first to config dll path
	# 	os.add_dll_directory("C:/WINDOWS/system32")
	# 	os.add_dll_directory("D:/Anaconda/Library/mingw-w64/bin")  # TODO: it should not use Anaconda

	# 	# get dll
	# 	self._dll_tracer = ctype_s.CDLL(os.path.join(os.getcwd()), self._file_tracer)

	# 	# check dll
	# 	# if self._dll_tracer is None:
	# 		# return False
	# 	# if self._dll_tracer.RayTracer_Test_checkStatus(c_int(0)) == 0:
	# 		# return False

	# 	self._is_started = True
	# 	return True
	
	# # TODO: not yet completed
	# def end(self) -> bool:
	# 	if not self._is_started:
	# 		return False

	# 	return True

	def setDLL_tracer(self, dll: CDLL) -> None:
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
		self._dll_tracer.RayTracer_Test_testDoubleArray(array_pixel, size)

	def Test_testUint8Array(self, array: List[bytes], size: int) -> None:
		array_pixel = (c_uint8 * size)(*array)
		self._dll_tracer.RayTracer_Test_testUint8Array(array_pixel, size)

	# TODO: not yet completed
	def Test_checkStatus(self, index: int, array: List[bytes], size: int) -> None:
		raise NotImplementedError

	# sample
	def Sample_buildScene(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Sample_buildScene(c_int(index))

	# tracer
	def Tracer_tracePoint(self, index_camera: int, pixel: Vec3f, x: float, y: float, depth: int) -> int:
		array_pixel = (c_double * 3)(*pixel.array)
		result: int = self._dll_tracer.RayTracer_Tracer_tracePoint(index_camera, array_pixel, c_double(x), c_double(y), c_int(depth))
		
		pixel[0] = array_pixel[0]
		pixel[1] = array_pixel[1]
		pixel[2] = array_pixel[2]

		return result

	# TODO: not yet completed
	def Tracer_tracerRect(self, index_camera: int, pixel_list: List[Vec3f], w: float, h: float, pixel_w: float, pixel_h: float, depth: int) -> int:
		raise NotImplementedError

	# camera
	def Camera_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Camera_create(c_int(type_))

	def Camera_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Camera_destroy(c_int(index))

	def Camera_config(self, index: int, type_: int, data: List[bytes], size: int) -> int:
		array_data = (c_uint8 * len(data))(*data)
		return self._dll_tracer.RayTracer_Camera_config(c_int(index), c_int(type_), array_data, c_uint32(size))

	# surface
	def Surface_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Surface_create(c_int(type_))

	def Surface_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Surface_destroy(c_int(index))

	def Surface_config(self, index: int, type_: int, data: List[bytes], size: int) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		array_data = (c_uint8 * len(data))(*data)
		return self._dll_tracer.RayTracer_Surface_config(c_int(index), c_int(type_), array_data, c_uint32(size))

	# texture
	def Texture_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Texture_create(c_int(type_))

	def Texture_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Texture_destroy(c_int(index))

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

	def Texture_config(self, index: int, type_: int, data: List[bytes], size: int) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		array_data = (c_uint8 * len(data))(*data)
		return self._dll_tracer.RayTracer_Texture_config(c_int(index), c_int(type_), array_data, c_int(size))

	# scatter
	def Scatter_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_Scatter_create(c_int(type_))

	def Scatter_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_Scatter_destroy(c_int(index))

	def Scatter_addTexture(self, index_scatter: int, index_texture: int, offset: int) -> int:
		return self._dll_tracer.RayTracer_Scatter_addTexture(c_int(index_scatter), c_int(index_texture), c_int(offset))

	def Scatter_rmTexture(self, index_scatter: int, offset: int) -> int:
		return self._dll_tracer.RayTracer_Scatter_rmTexture(c_int(index_scatter), c_int(offset))

	def Scatter_config(self, index: int, type_: int, data: List[bytes], size: int) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		array_data = (c_uint8 * len(data))(*data)
		return self._dll_tracer.RayTracer_Scatter_config(c_int(index), c_int(type_), array_data, c_int(size))

	# scene object - hitable
	def SceneObject_Hitable_create(self, type_: int) -> int:
		return self._dll_tracer.RayTracer_SceneObject_Hitable_create(c_int(type_))

	def SceneObject_Hitable_destroy(self, index: int) -> int:
		return self._dll_tracer.RayTracer_SceneObject_Hitable_destroy(c_int(index))

	def SceneObject_Hitable_addScatter(self, index_hitable: int, index_scatter: int) -> int:
		return self._dll_tracer.RayTracer_SceneObject_Hitable_addScatter(c_int(index_hitable), c_int(index_scatter))

	def SceneObject_Hitable_rmScatter(self, index_hitable: int, index_scatter: int) -> int:
		return self._dll_tracer.RayTracer_SceneObject_Hitable_rmScatter(c_int(index_hitable), c_int(index_scatter))

	def SceneObject_Hitable_config(self, index: int, type_: int, data: List[bytes], size: int) -> int:
		# TODO: currently data is const uint8_t*, cannot pass out value from dll
		array_data = (c_uint8 * len(data))(*data)
		return self._dll_tracer.RayTracer_SceneObject_Hitable_config(c_int(index), c_int(type_), array_data, c_int(size))
