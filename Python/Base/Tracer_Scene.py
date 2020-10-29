from .Tracer_ObjectBase import Tracer_ObjectBase
from .Tracer_Hitable import Hitable
from .Tracer_Light import Light
from .Tracer_RIAS import RIAS


class Scene(Tracer_ObjectBase):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def addLight(self, light: Light) -> bool:
		assert self._ops_tracer is not None
		result:	int	= self._ops_tracer.Scene_addLight(light.object_index)
		return True if result == 0 else False

	def addHitable(self, hitable: Hitable) -> bool:
		assert self._ops_tracer is not None
		result:	int	= self._ops_tracer.Scene_addHitable(hitable.object_index)
		return True if result == 0 else False

	def addRIAS(self, rias: RIAS) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Scene_addRIAS(rias.object_index)
		return True if result == 0 else False

	def rmLight(self, light: Light) -> bool:
		assert self._ops_tracer is not None
		result:	int	= self._ops_tracer.Scene_rmLight(light.object_index)
		return True if result == 0 else False

	def rmHitable(self, hitable: Hitable) -> bool:
		assert self._ops_tracer is not None
		result:	int	= self._ops_tracer.Scene_rmHitable(hitable.object_index)
		return True if result == 0 else False

	def rmRIAS(self, rias: RIAS) -> bool:
		assert self._ops_tracer is not None
		result:	int	= self._ops_tracer.Scene_rmRIAS(rias.object_index)
		return True if result == 0 else False
