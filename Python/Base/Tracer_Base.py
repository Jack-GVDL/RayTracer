from typing import List, Any


class Tracer_Base:

	def __init__(self):
		super().__init__()

		# data
		self._object_index: int = 0
		self._ops_tracer:	Any = None

	# Operation
	@ property
	def object_index(self) -> int:
		return self._object_index

	def setObjectIndex(self, value: int) -> None:
		self._object_index = value

	def setOps_tracer(self, ops: Any) -> None:
		self._ops_tracer = ops
