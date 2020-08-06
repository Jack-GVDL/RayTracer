from .Tracer_Base import Tracer_Base
from .Tracer_Texture import Texture


class Surface(Tracer_Base):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def convertToTexture(self, texture: Texture) -> bool:
		result: int = self._ops_tracer.Surface_convertToTexture(self._object_index, texture.object_index)
		return True if result == 0 else False

	def load(self) -> bool:
		result: int = self._ops_tracer.Surface_load(self._object_index)
		return True if result == 0 else False

	def dump(self) -> bool:
		result: int = self._ops_tracer.Surface_dump(self._object_index)
		return True if result == 0 else False


class Surface_Constant(Surface):

	def __init__(self):
		super().__init__()

		# init
		self._object_index = self._ops_tracer.Surface_create(0)

	# Operation
	# ...


class Surface_BMP(Surface):

	def __init__(self):
		super().__init__()

		# init
		self._object_index = self._ops_tracer.Surface_create(1)

	# Operation
	def setPath(self, path: str) -> None:
		data: bytes = path.encode()
		self._ops_tracer.Surface_config(self._object_index, 0, data, len(data))
