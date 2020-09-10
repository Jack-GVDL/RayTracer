from .Tracer_Ops import Ops_Tracer
from .Tracer_ObjectBase import Tracer_ObjectBase
from .Tracer_Texture import Texture


class Surface(Tracer_ObjectBase):

	@ classmethod
	def _getType_(cls, ops: Ops_Tracer, name: str) -> int:
		index: int = ops.Surface_Type_getIndex(name)
		assert index != -1, "Type not exist"
		return index

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def convertToTexture(self, texture: Texture) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Surface_interact(self.object_index, 0, (texture.object_index,), (2,))
		return True if result == 0 else False

	def load(self) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Surface_load(self.object_index)
		return True if result == 0 else False

	def dump(self) -> bool:
		assert self._ops_tracer is not None
		result: int = self._ops_tracer.Surface_dump(self.object_index)
		return True if result == 0 else False
