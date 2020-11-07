from typing import *
from .Tracer_Ops import Ops_Tracer
from .Tracer_ObjectBase import Tracer_ObjectBase


class Sampler(Tracer_ObjectBase):

	@ classmethod
	def _getType_(cls, ops: Ops_Tracer, name: str) -> int:
		index: int = ops.Sampler_Type_getIndex(name)
		assert index != -1, "Type not exist"
		return index

	# Operation
	def setSizeImage(self, w: int, h: int) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Sampler_setSizeImage(self.object_index, w, h)
		return True if result == 0 else False
