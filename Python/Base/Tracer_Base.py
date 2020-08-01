from typing import List, Any
from .Tracer_Ops import Tracer_Ops


class Tracer_Base:

	def __init__(self):
		super().__init__()

		# data
		self._object_index: int			= 0
		self._ops_tracer:	Tracer_Ops	= None

	# Operation
	@ property
	def object_index(self) -> int:
		return self._object_index

	def setObjectIndex(self, value: int) -> None:
		self._object_index = value

	def setOps_tracer(self, ops: Tracer_Ops) -> None:
		self._ops_tracer = ops
