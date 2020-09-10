from typing import List, Any
from .Tracer_Ops import Ops_Tracer


class Tracer_ObjectBase:

	def __init__(self):
		# super
		super().__init__()

		# data
		self._object_index: int			= 0
		self._ops_tracer:	Ops_Tracer	= None

	# Operation
	# operation
	@ property
	def object_index(self) -> int:
		return self._object_index

	def setOps_tracer(self, ops: Ops_Tracer) -> None:
		self._ops_tracer = ops

	# interface
	def start(self) -> None:
		pass

	def end(self) -> None:
		pass
