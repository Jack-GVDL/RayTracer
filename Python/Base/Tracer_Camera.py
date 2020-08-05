from .Tracer_Base import Tracer_Base
from .Tracer_Vec3f import Vec3f


class Tracer_Camera(Tracer_Base):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		self._object_index = self._ops_tracer.Camera_create(0)

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
