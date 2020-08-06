from .Tracer_Vec3f import Vec3f
from .Tracer_Base import Tracer_Base


class Mapper(Tracer_Base):

	def __init__(self):
		super().__init__()


class Mapper_Additor(Mapper):

	def __init__(self):
		super().__init__()

		# init
		self._object_index = self._ops_tracer.Mapper_create(0)

	# Operation
	def setAdditor(self, value: Vec3f) -> None:
		data:	bytes	= value.convertToBytes()
		result:	int		= self._ops_tracer.Mapper_config(self._object_index, 0, data, len(data))


class Mapper_Multiplier(Mapper):

	def __init__(self):
		super().__init__()

		# init
		self._object_index = self._ops_tracer.Mapper_create(1)

	# Operation
	def setMultiplier(self, value: Vec3f) -> None:
		data:	bytes	= value.convertToBytes()
		result:	int		= self._ops_tracer.Mapper_config(self._object_index, 0, data, len(data))
