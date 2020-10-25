from Base import AABB


class AABB_Default(AABB):

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
		type_index:	int		= self._getType_(self._ops_tracer, "aabb_default")
		self._object_index	= self._ops_tracer.AABB_create(type_index)
