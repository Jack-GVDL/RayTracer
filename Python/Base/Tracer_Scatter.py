from enum import IntEnum
from .Tracer_Base import Tracer_Base
from .Tracer_Texture import Texture


class Scatter(Tracer_Base):

	def __init__(self):
		super().__init__()

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


class Scatter_Light(Scatter):

	class TextureOffset(IntEnum):
		DIFFUSE:	int = 0
		SPECULAR:	int = 1
		EMISSIVE:	int = 2
		AMBIENT:	int = 3
		SHININESS:	int = 4
		MAX:		int = 5

	def __init__(self):
		super().__init__()

		# init
		object_index: int = self._ops_tracer.Scatter_create(0)
		self._object_index = object_index


class Scatter_Reflection(Scatter):

	def __init__(self):
		super().__init__()

		# init
		object_index: int = self._ops_tracer.Scatter_create(1)
		self._object_index = object_index


class Scatter_Refraction(Scatter):

	def __init__(self):
		super().__init__()

		# init
		object_index: int = self._ops_tracer.Scatter_create(2)
		self._object_index = object_index


class Scatter_Gradient(Scatter):

	def __init__(self):
		super().__init__()

		# init
		object_index: int = self._ops_tracer.Scatter_create(3)
		self._object_index = object_index


class Scatter_Emitter(Scatter):

	def __init__(self):
		super().__init__()

		# init
		object_index: int = self._ops_tracer.Scatter_create(4)
		self._object_index = object_index
