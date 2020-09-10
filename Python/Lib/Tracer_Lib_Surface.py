from Base import Surface, Texture


class Surface_Constant(Surface):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	# ...

	# Interface
	def start(self) -> None:
		type_index: int		= self._getType_(self._ops_tracer, "constant")
		self._object_index	= self._ops_tracer.Surface_create(type_index)


class Surface_BMP(Surface):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def setPath(self, path: str) -> None:
		assert self._ops_tracer is not None

		# add 0 to the end of string, otherwise there will be bug in C side (where it need c string)
		path += '\0'
		data: bytes = path.encode("utf-8")

		result: int = self._ops_tracer.Surface_config(self.object_index, 0, data)

	# Interface
	def start(self) -> None:
		type_index: int		= self._getType_(self._ops_tracer, "bmp")
		self._object_index	= self._ops_tracer.Surface_create(type_index)
