from typing import List
import struct
from .Tracer_Vec3f import Vec3f
from .Tracer_Base import Tracer_Base
from .Tracer_Scatter import Scatter


class SceneObject_Hitable(Tracer_Base):

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


class SceneObject_Sphere(SceneObject_Hitable):

	def __init__(self):
		super().__init__()

		# init
		object_index: int = self._ops_tracer.SceneObject_Hitable_create(0)
		self.setObjectIndex(object_index)

	# Operation
	def setCenter(self, center: Vec3f) -> None:
		data:	bytes		= bytes(_convert_Vec3fToBytes_(center))
		result: int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 0, data, len(data))
		
		# if result != 0:
		# 	return False
		# return True

	def setRadius(self, radius: float) -> None:
		data:	bytes		= struct.pack("d", radius)
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 1, data, len(data))
		
		# if result != 0:
		# 	return False
		# return True


class SceneObject_Trimesh(SceneObject_Hitable):

	def __init__(self):
		super().__init__()

		# init
		object_index: int = self._ops_tracer.SceneObject_Hitable_create(1)
		self.setObjectIndex(object_index)

	# Operation
	def setPoint_0(self, point: Vec3f) -> None:
		data:	bytes		= bytes(_convert_Vec3fToBytes_(point))
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 0, data, len(data))
		
		# if result != 0:
		# 	return False
		# return True

	def setPoint_1(self, point: Vec3f) -> None:
		data:	bytes		= bytes(_convert_Vec3fToBytes_(point))
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 1, data, len(data))
		
		# if result != 0:
		# 	return False
		# return True

	def setPoint_2(self, point: Vec3f) -> None:
		data:	bytes		= bytes(_convert_Vec3fToBytes_(point))
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 2, data, len(data))
		
		# if result != 0:
		# 	return False
		# return True

	# helper


# Static Function
def _convert_Vec3fToBytes_(point: Vec3f) -> bytearray:
	data: bytearray = bytearray()

	data.extend(struct.pack("d", point[0]))
	data.extend(struct.pack("d", point[1]))
	data.extend(struct.pack("d", point[2]))

	return data
