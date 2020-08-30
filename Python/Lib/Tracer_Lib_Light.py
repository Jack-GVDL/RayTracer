from Base import Vec3f
from Base import Light


class Light_Directional(Light):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "directional")
		self._object_index	= self._ops_tracer.SceneObject_Light_create(type_index)

	# Operation
	def setOrientation(self, orientation: Vec3f) -> None:
		data:	bytes	= orientation.convertToBytes()
		result: int		= self._ops_tracer.SceneObject_Light_config(self.object_index, 0, data)


class Light_Point(Light):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "point")
		self._object_index	= self._ops_tracer.SceneObject_Light_create(type_index)

	# Operation
	def setAttenuationCoeff(self, coeff: Vec3f) -> None:
		data: bytes		= coeff.convertToBytes()
		result:	int		= self._ops_tracer.SceneObject_Light_config(self.object_index, 0, data)
