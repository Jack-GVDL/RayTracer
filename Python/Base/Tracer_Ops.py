from typing import List, Tuple
from enum import IntEnum
from .Tracer_Vec3f import Vec3f
import numpy as np


class TracerType(IntEnum):
	CAMERA:		int = 0,
	SURFACE:	int = 1,
	TEXTURE:	int = 2,
	MATERIAL:	int = 3,
	SCATTER:	int = 4,
	HITABLE:	int = 5,
	LIGHT:		int = 6,
	AABB:		int = 7


class Ops_Tracer:

	def __init__(self):
		super().__init__()

	# Operation
	# main
	def RayTracer_init(self) -> None:
		raise NotImplementedError

	def RayTracer_del(self) -> None:
		raise NotImplementedError

	def RayTracer_info(self) -> None:
		raise NotImplementedError

	# test
	def Test_testDoubleArray(self, array: List[float], size: int) -> None:
		raise NotImplementedError

	def Test_testUint8Array(self, array: bytes, size: int) -> None:
		raise NotImplementedError

	def Test_checkStatus(self, index: int, array: bytes, size: int) -> None:
		raise NotImplementedError

	# tracer
	def Tracer_tracePoint(self, index_camera: int, pixel: Vec3f, x: float, y: float, depth: int) -> int:
		raise NotImplementedError

	def Tracer_traceRect(self, index_camera: int, pixel_list: np.ndarray, w: int, h: int, depth: int, is_reverse_x: bool, is_reverse_y: bool, format_: bool) -> int:
		raise NotImplementedError

	# camera
	def Camera_Type_getIndex(self, name: str) -> int:
		raise NotImplementedError

	def Camera_create(self, type_: int) -> int:
		raise NotImplementedError

	def Camera_destroy(self, index: int) -> int:
		raise NotImplementedError

	def Camera_config(self, index: int, type_: int, data: bytes) -> int:
		raise NotImplementedError

	def Camera_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		raise NotImplementedError

	def Camera_setLookFrom(self, index: int, look_from: Vec3f) -> int:
		raise NotImplementedError

	def Camera_setLookAt(self, index: int, look_at: Vec3f) -> int:
		raise NotImplementedError

	def Camera_setUpDirection(self, index: int, up_dir: Vec3f) -> int:
		raise NotImplementedError

	def Camera_setFOV(self, index: int, value: float) -> int:
		raise NotImplementedError

	def Camera_setAspectRatio(self, index: int, value: float) -> int:
		raise NotImplementedError

	# surface
	def Surface_Type_getIndex(self, name: str) -> int:
		raise NotImplementedError

	def Surface_create(self, type_: int) -> int:
		raise NotImplementedError

	def Surface_destroy(self, index: int) -> int:
		raise NotImplementedError

	def Surface_config(self, index: int, type_: int, data: bytes) -> int:
		raise NotImplementedError

	def Surface_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		raise NotImplementedError

	def Surface_load(self, index: int) -> int:
		raise NotImplementedError

	def Surface_dump(self, index: int) -> int:
		raise NotImplementedError

	# texture
	def Texture_Type_getIndex(self, name: str) -> int:
		raise NotImplementedError

	def Texture_create(self, type_: int) -> int:
		raise NotImplementedError

	def Texture_destroy(self, index: int) -> int:
		raise NotImplementedError

	def Texture_config(self, index: int, type_: int, data: bytes) -> int:
		raise NotImplementedError

	def Texture_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		raise NotImplementedError

	def Texture_addInput(self, index_texture: int, index_input: int, offset: int) -> int:
		raise NotImplementedError

	def Texture_rmInput(self, index: int, offset: int) -> int:
		raise NotImplementedError

	def Texture_setPixel(self, index: int, pixel: Vec3f, point: Vec3f) -> int:
		raise NotImplementedError

	def Texture_getPixel(self, index: int, pixel: Vec3f, point: Vec3f) -> int:
		raise NotImplementedError

	# material
	def Material_Type_getIndex(self, name: str) -> int:
		raise NotImplementedError

	def Material_create(self, type_: int) -> int:
		raise NotImplementedError

	def Material_destroy(self, index: int) -> int:
		raise NotImplementedError

	def Material_config(self, index: int, type_: int, data: bytes) -> int:
		raise NotImplementedError

	def Material_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		raise NotImplementedError

	def Material_addScatter(self, index_material: int, index_scatter: int) -> int:
		raise NotImplementedError

	def Material_rmScatter(self, index_material: int, index_scatter: int) -> int:
		raise NotImplementedError

	def Material_setTransmissive(self, index: int, transmissive: Vec3f) -> int:
		raise NotImplementedError

	def Material_setIndex(self, index: int, value: float) -> int:
		raise NotImplementedError

	# scatter
	def Scatter_Type_getIndex(self, name: str) -> int:
		raise NotImplementedError

	def Scatter_create(self, type_: int) -> int:
		raise NotImplementedError

	def Scatter_destroy(self, index: int) -> int:
		raise NotImplementedError

	def Scatter_config(self, index: int, type_: int, data: bytes) -> int:
		raise NotImplementedError

	def Scatter_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		raise NotImplementedError

	def Scatter_addScatter(self, index_scatter: int, index_target: int) -> int:
		raise NotImplementedError

	def Scatter_rmScatter(self, index_scatter: int, index_target: int) -> int:
		raise NotImplementedError

	def Scatter_setTexture(self, index_scatter: int, index_texture: int, offset: int) -> int:
		raise NotImplementedError

	# hitable
	def Hitable_Type_getIndex(self, name: str) -> int:
		raise NotImplementedError

	def Hitable_create(self, type_: int) -> int:
		raise NotImplementedError

	def Hitable_destroy(self, index: int) -> int:
		raise NotImplementedError

	def Hitable_config(self, index: int, type_: int, data: bytes) -> int:
		raise NotImplementedError

	def Hitable_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		raise NotImplementedError

	def Hitable_setMaterial(self, index_hitable: int, index_material: int) -> int:
		raise NotImplementedError

	# aabb
	def AABB_Type_getIndex(self, name: str) -> int:
		raise NotImplementedError

	def AABB_create(self, type_: int) -> int:
		raise NotImplementedError

	def AABB_destroy(self, index: int) -> int:
		raise NotImplementedError

	def AABB_config(self, index: int, type_: int, data: bytes) -> int:
		raise NotImplementedError

	def AABB_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		raise NotImplementedError

	def AABB_load(self, index: int) -> int:
		raise NotImplementedError

	# light
	def Light_Type_getIndex(self, name: str) -> int:
		raise NotImplementedError

	def Light_create(self, type_: int) -> int:
		raise NotImplementedError

	def Light_destroy(self, index: int) -> int:
		raise NotImplementedError

	def Light_config(self, index: int, type_: int, data: bytes) -> int:
		raise NotImplementedError

	def Light_interact(self, index: int, type_: int, index_list: Tuple[int], type_list: Tuple[int]) -> int:
		raise NotImplementedError

	def Light_setOrigin(self, index: int, origin: Vec3f) -> int:
		raise NotImplementedError

	def Light_setColor(self, index: int, color: Vec3f) -> int:
		raise NotImplementedError

	# scene
	def Scene_addLight(self, index_light: int) -> int:
		raise NotImplementedError

	def Scene_addHitable(self, index_hitable: int) -> int:
		raise NotImplementedError

	def Scene_addAABB(self, index_aabb: int) -> int:
		raise NotImplementedError

	def Scene_rmLight(self, index_light: int) -> int:
		raise NotImplementedError

	def Scene_rmHitable(self, index_hitable: int) -> int:
		raise NotImplementedError

	def Scene_rmAABB(self, index_aabb: int) -> int:
		raise NotImplementedError
