import struct
from .Tracer_Vec3f import Vec3f
from .Tracer_Base import Tracer_Base
from .Tracer_Scatter import Scatter


class Hitable(Tracer_Base):

	def __init__(self):
		super().__init__()

	# Operation
	def addScatter(self, scatter: Scatter) -> bool:
		result: int = self._ops_tracer.SceneObject_Hitable_addScatter(self._object_index, scatter.object_index)
		if result != 0:
			return False
		return True
	
	def rmScatter(self, scatter: Scatter) -> bool:
		result: int = self._ops_tracer.SceneObject_Hitable_rmScatter(self._object_index, scatter.object_index)
		if result != 0:
			return False
		return True


class Hitable_Sphere(Hitable):

	def __init__(self):
		super().__init__()

		# init
		object_index: int = self._ops_tracer.SceneObject_Hitable_create(0)
		self._object_index = object_index

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

		# init
		object_index: int = self._ops_tracer.SceneObject_Hitable_create(1)
		self._object_index = object_index

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
