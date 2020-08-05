from typing import List, Any
from .Tracer_Ops import Ops_Tracer


class Tracer_Base:

	# Class
	_global_ops_tracer:	Ops_Tracer = None

	@ classmethod
	def setGlobal_ops_tracer(cls, ops: Ops_Tracer) -> None:
		cls._global_ops_tracer = ops

	# Object
	def __init__(self, ops_tracer: Ops_Tracer = None):
		# super
		super().__init__()

		# data
		self._object_index: int			= 0
		self._ops_tracer:	Ops_Tracer	= None

		# init
		if ops_tracer is not None:
			self._ops_tracer = ops_tracer
		else:
			self._ops_tracer = self._global_ops_tracer

		# check
		assert self._ops_tracer is not None, "Tracer_Base: ops_tracer: Cannot be None"

	# Operation
	@ property
	def object_index(self) -> int:
		return self._object_index

	# def setObjectIndex(self, value: int) -> None:
	# 	self._object_index = value

	def setOps_tracer(self, ops: Ops_Tracer) -> None:
		self._ops_tracer = ops
