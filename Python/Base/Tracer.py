from .Tracer_Base import Tracer_Base
from .Tracer_Ops import Ops_Tracer


class Tracer:

	def __init__(self):
		super().__init__()

		# data
		self._is_started:	bool		= False
		self._ops_tracer:	Ops_Tracer	= None

	# Operation
	def setOps_tracer(self, ops: Ops_Tracer) -> None:
		self._ops_tracer = ops

	def start(self) -> None:
		Tracer_Base.setGlobal_ops_tracer(self._ops_tracer)
		self._is_started = True

	def end(self) -> None:
		Tracer_Base.setGlobal_ops_tracer(None)
		self._is_started = False
