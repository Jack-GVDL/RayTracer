from .Tracer_Ops import Ops_Tracer
from .Tracer_ObjectBase import Tracer_ObjectBase
from .Tracer_Vec3f import Vec3f
from typing import List, Any


class Texture(Tracer_ObjectBase):

	@ classmethod
	def _getType_(cls, ops: Ops_Tracer, name: str) -> int:
		index: int = ops.Texture_Type_getIndex(name)
		assert index != -1, "Type not exist"
		return index

	def __init__(self):
		super().__init__()

	# Operation
	def addInput(self, texture: Any, offset: int) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Texture_addInput(self._object_index, texture.object_index, offset)
		return True if result == 0 else False

	def rmInput(self, offset: int) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Texture_rmInput(self._object_index, offset)
		return True if result == 0 else False

	def setPixel(self, point: Vec3f, pixel: Vec3f) -> None:
		assert self._ops_tracer is not None
		# be careful order of point and pixel in Texture_setPixel(pixel, point)
		result: int = self._ops_tracer.Texture_setPixel(self._object_index, pixel, point)

	def getPixel(self, point: Vec3f, pixel: Vec3f) -> None:
		assert self._ops_tracer is not None
		# be careful order of point and pixel in Texture_getPixel(pixel, point)
		result:	int	= self._ops_tracer.Texture_getPixel(self._object_index, pixel, point)
