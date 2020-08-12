from .Tracer_Mapper import Mapper
from .Tracer_Hitable import Hitable_Sphere, Hitable_Trimesh


class Mapper_Sphere(Mapper):

	def __init__(self):
		super().__init__()

		# init
		self._object_index = self._ops_tracer.Mapper_create(2)

	# Operation
	def setSphere(self, sphere: Hitable_Sphere) -> None:
		result:	int		= self._ops_tracer.Mapper_interact(self._object_index, 0, [sphere.object_index], [5], 1)


class Mapper_Trimesh(Mapper):

	def __init__(self):
		super().__init__()

		# init
		self._object_index = self._ops_tracer.Mapper_create(3)

	# Operation
	def setTrimesh(self, trimesh: Hitable_Trimesh) -> None:
		result:	int		= self._ops_tracer.Mapper_interact(self._object_index, 0, [trimesh.object_index], [5], 1)
