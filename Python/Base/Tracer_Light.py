from .Tracer_Ops import Ops_Tracer
from .Tracer_ObjectBase import Tracer_ObjectBase
from .Tracer_Vec3f import Vec3f


class Light(Tracer_ObjectBase):

	@ classmethod
	def _getType_(cls, ops: Ops_Tracer, name: str) -> int:
		index: int = ops.SceneObject_Light_Type_getIndex(name)
		assert index != -1, "Type not exist"
		return index

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	# TODO: in C++, it should be in SceneElement
	def setOrigin(self, origin: Vec3f) -> None:
		assert self._ops_tracer is not None
		result:	int	= self._ops_tracer.SceneObject_Light_setOrigin(self._object_index, origin)

	def setColor(self, color: Vec3f) -> None:
		assert self._ops_tracer is not None
		result:	int	= self._ops_tracer.SceneObject_Light_setColor(self._object_index, color)
