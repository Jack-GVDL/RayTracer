from .Tracer_Base import Tracer_Base
from .Tracer_Texture import Texture


class Scatter(Tracer_Base):

	def __init__(self):
		super().__init__()

	def addTexture(self, texture: Texture, offset: int) -> bool:
		if offset < 0:
			return False

		result: int = self._ops_tracer.Texture_addTexture(self._object_index, texture.object_index, offset)
		if result != 0:
			return False
		return True
	
	def rmTexture(self, offset: int) -> bool:
		if offset < 0:
			return False

		result: int = self._ops_tracer.Texture_rmTexture(self._object_index, offset)
		if result != 0:
			return False
		return True
