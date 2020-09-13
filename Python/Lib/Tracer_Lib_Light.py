from Base import Vec3f
from Base import Light


class Light_Directional(Light):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def setOrientation(self, orientation: Vec3f) -> None:
		assert self._ops_tracer is not None
		data:	bytes	= orientation.convertToBytes()
		result: int		= self._ops_tracer.Light_config(self.object_index, 0, data)

	# Interface
	def start(self) -> None:
		type_index: int		= self._getType_(self._ops_tracer, "directional")
		self._object_index	= self._ops_tracer.Light_create(type_index)


class Light_Point(Light):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def setAttenuation(self, coeff: Vec3f) -> None:
		assert self._ops_tracer is not None
		data: bytes		= coeff.convertToBytes()
		result:	int		= self._ops_tracer.Light_config(self.object_index, 0, data)

	# Interface
	def start(self) -> None:
		type_index: int		= self._getType_(self._ops_tracer, "point")
		self._object_index	= self._ops_tracer.Light_create(type_index)
