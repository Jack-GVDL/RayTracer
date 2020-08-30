from .Tracer_Base import Tracer_Base
from .Tracer_Ops import Ops_Tracer
import os


# Data Structure
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


# Operation
# TODO: should move these things to class
# add dll directory
os.add_dll_directory("C:/WINDOWS/system32")
os.add_dll_directory("D:/Anaconda/Library/mingw-w64/bin")  # TODO: it should not use Anaconda

# check
# ops_tracer.Test_checkStatus(0, bytes(), 0)
# ops_tracer.Test_checkStatus(1, bytes(), 0)
