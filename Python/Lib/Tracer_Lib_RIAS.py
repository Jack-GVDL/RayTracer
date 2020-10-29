from Base import RIAS


class RIAS_AABB(RIAS):

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
		type_index:	int		= self._getType_(self._ops_tracer, "aabb")
		self._object_index	= self._ops_tracer.RIAS_create(type_index)
