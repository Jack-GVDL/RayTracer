from .Tracer_Ops import Ops_Tracer
from .Tracer_ObjectBase import Tracer_ObjectBase
from .Tracer_Scatter import Scatter
from .Tracer_Vec3f import Vec3f


class Material(Tracer_ObjectBase):

	@ classmethod
	def _getType_(cls, ops: Ops_Tracer, name: str) -> int:
		index: int = ops.Material_Type_getIndex(name)
		assert index != -1, "Type not exist"
		return index

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ..

	# Operation
	def addScatter(self, scatter: Scatter) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Material_addScatter(self._object_index, scatter.object_index)
		return True if result == 0 else False

	def rmScatter(self, scatter: Scatter) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Material_rmScatter(self._object_index, scatter.object_index)
		return True if result == 0 else False

	def setTransmissive(self, value: Vec3f) -> None:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Material_setTransmissive(self._object_index, value)

	def setIndex(self, value: float) -> None:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Material_setIndex(self._object_index, value)
