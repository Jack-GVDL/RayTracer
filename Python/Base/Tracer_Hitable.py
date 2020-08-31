from .Tracer_Ops import Ops_Tracer
from .Tracer_Vec3f import Vec3f
from .Tracer_ObjectBase import Tracer_ObjectBase
from .Tracer_Scatter import Scatter


class Hitable(Tracer_ObjectBase):

	@ classmethod
	def _getType_(cls, ops: Ops_Tracer, name: str) -> int:
		index: int = ops.SceneObject_Hitable_Type_getIndex(name)
		assert index != -1, "Type not exist"
		return index

	def __init__(self):
		super().__init__()

	# Operation
	def addScatter(self, scatter: Scatter) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.SceneObject_Hitable_addScatter(self._object_index, scatter.object_index)
		return True if result == 0 else False
	
	def rmScatter(self, scatter: Scatter) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.SceneObject_Hitable_rmScatter(self._object_index, scatter.object_index)
		return True if result == 0 else False

	def setTransmissive(self, value: Vec3f) -> None:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.SceneObject_Hitable_setTransmissive(self._object_index, value)

	def setIndex(self, value: float) -> None:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.SceneObject_Hitable_setIndex(self._object_index, value)
