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
		result: int = self._ops_tracer.Surface_interact(self._object_index, 0, [texture.object_index], [3], 1)
		return True if result == 0 else False

	def load(self) -> bool:
		result: int = self._ops_tracer.Surface_load(self._object_index)
		return True if result == 0 else False

	def dump(self) -> bool:
		result: int = self._ops_tracer.Surface_dump(self._object_index)
		return True if result == 0 else False


class Surface_Constant(Surface):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Surface_Type_getIndex("constant")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Surface_create(self._type_index)

	# Operation
	# ...


class Surface_BMP(Surface):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Surface_Type_getIndex("constant")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Surface_create(self._type_index)

	# Operation
	def setPath(self, path: str) -> None:
		data: bytes = path.encode()
		self._ops_tracer.Surface_config(self._object_index, 0, data, len(data))
