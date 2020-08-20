from .Tracer_Ops import Ops_Tracer
from .Tracer_Base import Tracer_Base
from .Tracer_Vec3f import Vec3f


class Camera(Tracer_Base):

	@ classmethod
	def _getType_(cls, ops: Ops_Tracer, name: str) -> int:
		index: int = ops.Camera_Type_getIndex(name)
		assert index != -1, "Type not exist"
		return index

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def setLookFrom(self, look_from: Vec3f) -> None:
		self._ops_tracer.Camera_setLookFrom(self._object_index, look_from)

	def setLookAt(self, look_at: Vec3f) -> None:
		self._ops_tracer.Camera_setLookAt(self._object_index, look_at)

	def setUpDirection(self, up_dir: Vec3f) -> None:
		self._ops_tracer.Camera_setUpDirection(self._object_index, up_dir)

	def setFOV(self, value: float) -> None:
		self._ops_tracer.Camera_setFOV(self._object_index, value)

	def setAspectRatio(self, value: float) -> None:
		self._ops_tracer.Camera_setAspectRatio(self._object_index, value)
