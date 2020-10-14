from Base import Material


class Material_Default(Material):

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
		type_index:	int		= self._getType_(self._ops_tracer, "material_default")
		self._object_index	= self._ops_tracer.Material_create(type_index)
