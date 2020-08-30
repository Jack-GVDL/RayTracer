from Base import Surface


class Surface_Constant(Surface):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "constant")
		self._object_index	= self._ops_tracer.Surface_create(type_index)

	# Operation
	# ...


class Surface_BMP(Surface):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "bmp")
		self._object_index	= self._ops_tracer.Surface_create(type_index)

	# Operation
	def setPath(self, path: str) -> None:
		data: bytes = path.encode()
		self._ops_tracer.Surface_config(self._object_index, 0, data)
