from .Tracer_Ops import Ops_Tracer


class Tracer_Base:

	def __init__(self):
		super().__init__()

		# data
		self._is_started:	bool		= False
		self._ops_tracer:	Ops_Tracer	= None

	def __del__(self):
		if self._is_started:
			self._ops_tracer.RayTracer_del()

	# Operation
	def setOps_tracer(self, ops: Ops_Tracer) -> None:
		self._ops_tracer = ops

	def start(self) -> None:
		self._ops_tracer.RayTracer_init()
		self._ops_tracer.RayTracer_info()
		self._is_started = True

	def end(self) -> None:
		self._ops_tracer.RayTracer_del()
		self._is_started = False
