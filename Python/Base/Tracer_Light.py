import struct
from .Tracer_Base import Tracer_Base
from .Tracer_Vec3f import Vec3f


class Light(Tracer_Base):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	# TODO: in C++, it should be in SceneElement
	def setOrigin(self, origin: Vec3f) -> None:
		result:	int	= self._ops_tracer.SceneObject_Light_setOrigin(self._object_index, origin)

	def setColor(self, color: Vec3f) -> None:
		result:	int	= self._ops_tracer.SceneObject_Light_setColor(self._object_index, color)


class Light_Directional(Light):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.SceneObject_Light_Type_getIndex("directional")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.SceneObject_Light_create(self._type_index)

	# Operation
	def setOrientation(self, orientation: Vec3f) -> None:
		data:	bytes	= orientation.convertToBytes()
		result: int		= self._ops_tracer.SceneObject_Light_config(self._object_index, 0, data, len(data))


class Light_Point(Light):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.SceneObject_Light_Type_getIndex("point")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.SceneObject_Light_create(self._type_index)

	# Operation
	def setAttenuationCoeff(self, coeff: Vec3f) -> None:
		data: bytes		= coeff.convertToBytes()
		result:	int		= self._ops_tracer.SceneObject_Light_config(self._object_index, 0, data, len(data))
