from .Tracer_Base import Tracer_Base
from .Tracer_Vec3f import Vec3f
from .Tracer_Mapper import Mapper


class Texture(Tracer_Base):

	def __init__(self):
		super().__init__()

	# Operation
	def addMapper(self, mapper: Mapper) -> bool:
		result:	int	= self._ops_tracer.Texture_addMapper(self._object_index, mapper.object_index)
		return True if result == 0 else False

	def rmMapper(self, mapper: Mapper) -> bool:
		result: int = self._ops_tracer.Texture_rmMapper(self._object_index, mapper.object_index)
		return True if result == 0 else False

	def setPixel(self, point: Vec3f, pixel: Vec3f) -> None:
		# be careful order of point and pixel in Texture_setPixel(pixel, point)
		result: int = self._ops_tracer.Texture_setPixel(self._object_index, pixel, point)

	def getPixel(self, point: Vec3f, pixel: Vec3f) -> None:
		# be careful order of point and pixel in Texture_getPixel(pixel, point)
		result:	int	= self._ops_tracer.Texture_getPixel(self._object_index, pixel, point)


class Texture_Constant(Texture):

	def __init__(self):
		super().__init__()

		# init
		self._object_index = self._ops_tracer.Texture_create(0)

	# Operation
	# ...


class Texture_Checkerboard(Texture):

	def __init__(self):
		super().__init__()

		# init
		self._object_index = self._ops_tracer.Texture_create(1)

	# Operation
	def setBoardSize(self, size: Vec3f) -> None:
		data:	bytes	= size.convertToBytes()
		result:	int		= self._ops_tracer.Texture_config(self._object_index, 0, data, len(data))


class Texture_Image(Texture):

	def __init__(self):
		super().__init__()

		# init
		self._object_index = self._ops_tracer.Texture_create(2)

	# Operation
	# ...
