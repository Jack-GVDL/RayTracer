from .Tracer_Ops import Ops_Tracer
from .Tracer_Vec3f import Vec3f
from .Tracer_ObjectBase import Tracer_ObjectBase
from .Tracer_Scatter import Scatter
from .Tracer_Material import Material


class Hitable(Tracer_ObjectBase):

	@ classmethod
	def _getType_(cls, ops: Ops_Tracer, name: str) -> int:
		index: int = ops.Hitable_Type_getIndex(name)
		assert index != -1, "Type not exist"
		return index

	def __init__(self):
		super().__init__()

	# Operation
	def setMaterial(self, material: Material) -> None:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Hitable_setMaterial(self._object_index, material.object_index)
