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

	# Operation
	def setCenter(self, center: Vec3f) -> None:
		data:	List[bytes]	= self._convert_Vec3fToBytes_(center)
		result: int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 0, data, len(data))
		
		if result != 0:
			return False
		return True

	def setRadius(self, raidus: float) -> None:
		data:	List[bytes]	= struct.pack("d", radius)
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 1, data, len(data))
		
		if result != 0:
			return False
		return True

	# helper
	def _convert_Vec3fToBytes_(self, point: Vec3f) -> List[bytes]:
		data: List[bytes] = struct.pack("d", point[0])
		data: List[bytes] = struct.pack("d", point[1])
		data: List[bytes] = struct.pack("d", point[2]) 

		data: List[bytes] = []
		data.extend(data_0)
		data.extend(data_1)
		data.extend(data_2)

		return data


class SceneObject_Trimesh(SceneObject_Hitable):

	def __init__(self):
		super().__init__()

	# Operation
	def setPoint_0(self, point: Vec3f) -> None:
		data:	List[bytes]	= self._convert_Vec3fToBytes_(point)
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 0, data, len(data))
		
		if result != 0:
			return False
		return True

	def setPoint_1(self, point: Vec3f) -> None:
		data:	List[bytes]	= self._convert_Vec3fToBytes_(point)
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 1, data, len(data))
		
		if result != 0:
			return False
		return True

	def setPoint_2(self, point: Vec3f) -> None:
		data:	List[bytes]	= self._convert_Vec3fToBytes_(point)
		result:	int			= self._ops_tracer.SceneObject_Hitable_config(self._object_index, 2, data, len(data))
		
		if result != 0:
			return False
		return True

	# helper
	def _convert_Vec3fToBytes_(self, point: Vec3f) -> List[bytes]:
		data: List[bytes] = struct.pack("d", point[0])
		data: List[bytes] = struct.pack("d", point[1])
		data: List[bytes] = struct.pack("d", point[2]) 

		data: List[bytes] = []
		data.extend(data_0)
		data.extend(data_1)
		data.extend(data_2)

		return data
