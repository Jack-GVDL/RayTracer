from .Tracer_Ops import Ops_Tracer
from .Tracer_Base import Tracer_Base
from .Tracer_Texture import Texture


class Scatter(Tracer_Base):

	@ classmethod
	def _getType_(cls, ops: Ops_Tracer, name: str) -> int:
		index: int = ops.Scatter_Type_getIndex(name)
		assert index != -1, "Type not exist"
		return index

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def setTexture(self, texture: Texture, offset: int) -> bool:
		if offset < 0:
			return False

		result: int = self._ops_tracer.Scatter_setTexture(self._object_index, texture.object_index, offset)
		return True if result == 0 else False
	
	def rmTexture(self, offset: int) -> bool:
		if offset < 0:
			return False

		result: int = self._ops_tracer.Scatter_rmTexture(self._object_index, offset)
		return True if result == 0 else False
