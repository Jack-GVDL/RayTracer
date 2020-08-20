import struct
from Base import Vec3f, Hitable


class Hitable_Sphere(Hitable):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "sphere")
		self._object_index	= self._ops_tracer.SceneObject_Hitable_create(type_index)

	# Operation
	def setCenter(self, center: Vec3f) -> None:
		data:	bytes		= center.convertToBytes()
		result: int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 0, data, len(data))

	def setRadius(self, radius: float) -> None:
		data:	bytes		= struct.pack("d", radius)
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 1, data, len(data))


class Hitable_Trimesh(Hitable):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "trimesh")
		self._object_index	= self._ops_tracer.SceneObject_Hitable_create(type_index)

	# Operation
	def setPoint_0(self, point: Vec3f) -> None:
		data:	bytes		= point.convertToBytes()
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 0, data, len(data))

	def setPoint_1(self, point: Vec3f) -> None:
		data:	bytes		= point.convertToBytes()
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 1, data, len(data))

	def setPoint_2(self, point: Vec3f) -> None:
		data:	bytes		= point.convertToBytes()
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 2, data, len(data))
