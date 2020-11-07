from Base import Sampler


class Sampler_Grid(Sampler):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	# TODO: not yet completed
	def setGridSize(self, w: int, h: int) -> None:
		raise NotImplementedError

	# Interface
	def start(self) -> None:
		type_index:	int		= self._getType_(self._ops_tracer, "grid")
		self._object_index	= self._ops_tracer.Sampler_create(type_index)
