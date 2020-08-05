from .Tracer_Base import Tracer_Base
from .Tracer_Hitable import Hitable
from .Tracer_Light import Light


class Scene(Tracer_Base):

	def __init__(self):
		super().__init__()

	# Operation
	def addLight(self, light: Light) -> bool:
		result:	int	= self._ops_tracer.Scene_addLight(light.object_index)
		return True if result == 0 else False

	def addHitable(self, hitable: Hitable) -> bool:
		result:	int	= self._ops_tracer.Scene_addHitable(hitable.object_index)
		return True if result == 0 else False

	def rmLight(self, light: Light) -> bool:
		result:	int	= self._ops_tracer.Scene_rmLight(light.object_index)
		return True if result == 0 else False

	def rmHitable(self, hitable: Hitable) -> bool:
		result:	int	= self._ops_tracer.Scene_rmHitable(hitable.object_index)
		return True if result == 0 else False
