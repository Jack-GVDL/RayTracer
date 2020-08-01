from enum import IntEnum
from typing import List
from Tracer_Vec3f import Vec3f


# backup
# class DataSize(IntEnum):
# 	SIZE_0:		int = 0
# 	SIZE_8:		int = 8
# 	SIZE_16:	int = 16
# 	SIZE_32:	int	= 32
# 	SIZE_64:	int = 64
# 	SIZE_128:	int = 128


# backup
# class DataContainer:
#
# 	def __init__(self):
# 		super().__init__()
#
# 		# data
# 		self.data:	Any			= 0
# 		self.size:	DataSize	= DataSize.SIZE_0


class Tracer_Ops:

	def __init__(self):
		super().__init__()

	# Operation
	# test
	def Test_testDoubleArray(self, array: List[float], size: int) -> None:
		raise NotImplementedError

	def Test_testUint8Array(self, array: List[bytes], size: int) -> None:
		raise NotImplementedError

	def Test_checkStatus(self, index: int, array: List[bytes], size: int) -> None:
		raise NotImplementedError

	# sample
	def Sample_buildScene(self, index: int) -> int:
		raise NotImplementedError

	# tracer
	def Tracer_trace(self, pixel: Vec3f, x: float, y: float, depth: int):
		raise NotImplementedError
	
	# surface
	def Surface_create(self, type: int) -> int:
		raise NotImplementedError

	def Surface_destroy(self, index: int) -> int:
		raise NotImplementedError

	def Surface_config(self, index: int, type: int, data: List[bytes], size: int) -> int:
		raise NotImplementedError

	# texture
	def Texture_create(self, type: int) -> int:
		raise NotImplementedError

	def Texture_destroy(self, index: int) -> int:
		raise NotImplementedError

	def Texture_setPixel(self, index: int, pixel: Vec3f, point: Vec3f) -> int:
		raise NotImplementedError

	def Texture_getPixel(self, index: int, pixel: Vec3f, point: Vec3f) -> int:
		raise NotImplementedError

	def Texture_config(self, index: int, type: int, data: List[bytes], size: int) -> int:
		raise NotImplementedError

	# scatter
	def Scatter_create(self, type: int) -> int:
		raise NotImplementedError

	def Scatter_destroy(self, index: int) -> int:
		raise NotImplementedError

	def Scatter_addTexture(self, index_scatter: int, index_texture: int, offset: int) -> int:
		raise NotImplementedError

	def Scatter_rmTexture(self, index_scatter: int, offset: int) -> int:
		raise NotImplementedError

	def Scatter_config(self, index: int, type: int, data: List[bytes], size: int) -> int:
		raise NotImplementedError

	# hitable
	def SceneObject_Hitable_create(self, type: int) -> int:
		raise NotImplementedError

	def SceneObject_Hitable_destroy(self, index: int) -> int:
		raise NotImplementedError

	def SceneObject_Hitable_addScatter(self, index_hitable: int, index_scatter: int) -> int:
		raise NotImplementedError

	def SceneObject_Hitable_rmScatter(self, index_hitable: int, index_scatter: int) -> int:
		raise NotImplementedError

	def SceneObject_Hitable_config(self, index: int, type: int, data: List[bytes], size: int) -> int:
		raise NotImplementedError
