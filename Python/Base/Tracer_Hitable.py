from .Tracer_Ops import Ops_Tracer
from .Tracer_Base import Tracer_Base
from .Tracer_Scatter import Scatter


class Hitable(Tracer_Base):

	@ classmethod
	def _getType_(cls, ops: Ops_Tracer, name: str) -> int:
		index: int = ops.SceneObject_Hitable_Type_getIndex(name)
		assert index != -1, "Type not exist"
		return index

	def __init__(self):
		super().__init__()

	# Operation
	def addScatter(self, scatter: Scatter) -> bool:
		result: int = self._ops_tracer.SceneObject_Hitable_addScatter(self._object_index, scatter.object_index)
		if result != 0:
			return False
		return True
	
	def rmScatter(self, scatter: Scatter) -> bool:
		result: int = self._ops_tracer.SceneObject_Hitable_rmScatter(self._object_index, scatter.object_index)
		if result != 0:
			return False
		return True
