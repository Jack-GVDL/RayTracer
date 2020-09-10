import struct
from Base import Vec3f, Hitable


class Hitable_Sphere(Hitable):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def setCenter(self, center: Vec3f) -> None:
		data:	bytes		= center.convertToBytes()
		result: int			= self._ops_tracer.SceneObject_Hitable_config(self.object_index, 0, data)

	def setRadius(self, radius: float) -> None:
		data:	bytes		= struct.pack("d", radius)
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self.object_index, 1, data)

	# Interface
	def start(self) -> None:
		type_index: int		= self._getType_(self._ops_tracer, "sphere")
		self._object_index	= self._ops_tracer.SceneObject_Hitable_create(type_index)


class Hitable_Trimesh(Hitable):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def setPoint_0(self, point: Vec3f) -> None:
		data:	bytes		= point.convertToBytes()
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self.object_index, 0, data)

	def setPoint_1(self, point: Vec3f) -> None:
		data:	bytes		= point.convertToBytes()
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self.object_index, 1, data)

	def setPoint_2(self, point: Vec3f) -> None:
		data:	bytes		= point.convertToBytes()
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self.object_index, 2, data)

	# Interface
	def start(self) -> None:
		type_index: int		= self._getType_(self._ops_tracer, "trimesh")
		self._object_index	= self._ops_tracer.SceneObject_Hitable_create(type_index)


# TODO: not yet completed
class Hitable_AABB(Hitable):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def addHitable(self, hitable: Hitable) -> bool:
		if hitable is None:
			return False

		result: int = self._ops_tracer.SceneObject_Hitable_interact(self.object_index, 0, (hitable.object_index,), (4,))
		return True if result == 0 else False

	def rmHitable(self, hitable: Hitable) -> bool:
		if hitable is None:
			return False

		result: int = self._ops_tracer.SceneObject_Hitable_interact(self.object_index, 1, (hitable.object_index,), (4,))
		return True if result == 0 else False

	# Interface
	def start(self) -> None:
		type_index: int		= self._getType_(self._ops_tracer, "aabb")
		self._object_index	= self._ops_tracer.SceneObject_Hitable_create(type_index)
