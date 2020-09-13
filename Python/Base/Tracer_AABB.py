from .Tracer_Ops import Ops_Tracer
from .Tracer_ObjectBase import Tracer_ObjectBase
from typing import List, Any


class AABB(Tracer_ObjectBase):

	@ classmethod
	def _getType_(cls, ops: Ops_Tracer, name: str) -> int:
		index: int = ops.AABB_Type_getIndex(name)
		assert index != -1, "Type not exist"
		return index

	# Operation
	def load(self) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.AABB_load(self.object_index)
		return True if result == 0 else False
