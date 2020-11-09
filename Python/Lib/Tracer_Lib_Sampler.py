import struct
from Base import Sampler


class Sampler_Grid(Sampler):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def setGridSize(self, w: int, h: int) -> None:
		data: bytearray = bytearray()

		data.extend(struct.pack("i", w))
		data.extend(struct.pack("i", h))

		result: int = self._ops_tracer.Sampler_config(self.object_index, 0, bytes(data))

	# Interface
	def start(self) -> None:
		type_index:	int		= self._getType_(self._ops_tracer, "grid")
		self._object_index	= self._ops_tracer.Sampler_create(type_index)
