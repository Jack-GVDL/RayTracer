import struct
from .Tracer_Base import Tracer_Base
from .Tracer_Vec3f import Vec3f


class Light(Tracer_Base):

	def __init__(self):
		super().__init__()

		# data
		# ...

	# Operation
	# TODO: in C++, it should be in SceneElement
	def setOrigin(self, origin: Vec3f) -> None:
		result:	int	= self._ops_tracer.SceneObject_Light_setOrigin(self._object_index, origin)

	def setColor(self, color: Vec3f) -> None:
		result:	int	= self._ops_tracer.SceneObject_Light_setColor(self._object_index, color)


class Light_Directional(Light):

	def __init__(self):
		super().__init__()

		# init
		object_index: int = self._ops_tracer.SceneObject_Light_create(0)
		self._object_index = object_index

	# Operation
	def setOrientation(self, orientation: Vec3f) -> None:
		data:	bytes	= orientation.convertToBytes()
		result: int		= self._ops_tracer.SceneObject_Light_config(self._object_index, 0, data, len(data))


class Light_Point(Light):

	def __init__(self):
		super().__init__()

		# init
		object_index: int = self._ops_tracer.SceneObject_Light_create(1)
		self._object_index = object_index

	# Operation
	def setAttenuationCoeff(self, coeff: Vec3f) -> None:
		data: bytes		= coeff.convertToBytes()
		result:	int		= self._ops_tracer.SceneObject_Light_config(self._object_index, 0, data, len(data))
