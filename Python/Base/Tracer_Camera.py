from .Tracer_Base import Tracer_Base
from .Tracer_Vec3f import Vec3f


class Tracer_Camera(Tracer_Base):

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


class Tracer_Camera_Default(Tracer_Camera):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Camera_Type_getIndex("camera_0")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Camera_create(self._type_index)
