import struct
import math
from typing import List, Any
from .Tracer_Base import Tracer_Base
from .Tracer_Vec3f import Vec3f


class Texture(Tracer_Base):

	def __init__(self):
		super().__init__()

	# Operation
	def addInput(self, texture: Any, offset: int) -> bool:
		result: int = self._ops_tracer.Texture_addInput(self._object_index, texture.object_index, offset)
		return True if result == 0 else False

	def rmInput(self, offset: int) -> bool:
		result: int = self._ops_tracer.Texture_rmInput(self._object_index, offset)
		return True if result == 0 else False

	# TODO: backup
	# def addMapper(self, mapper: Mapper) -> bool:
	# 	result:	int	= self._ops_tracer.Texture_addMapper(self._object_index, mapper.object_index)
	# 	return True if result == 0 else False
	#
	# def rmMapper(self, mapper: Mapper) -> bool:
	# 	result: int = self._ops_tracer.Texture_rmMapper(self._object_index, mapper.object_index)
	# 	return True if result == 0 else False

	def setPixel(self, point: Vec3f, pixel: Vec3f) -> None:
		# be careful order of point and pixel in Texture_setPixel(pixel, point)
		result: int = self._ops_tracer.Texture_setPixel(self._object_index, pixel, point)

	def getPixel(self, point: Vec3f, pixel: Vec3f) -> None:
		# be careful order of point and pixel in Texture_getPixel(pixel, point)
		result:	int	= self._ops_tracer.Texture_getPixel(self._object_index, pixel, point)


class Texture_Input(Texture):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Texture_Type_getIndex("input")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Texture_create(self._type_index)

	# Operation
	# ...


class Texture_Convolutor(Texture):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Texture_Type_getIndex("convolutor")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Texture_create(self._type_index)

	# Operation
	def setTexture(self, texture: Texture) -> None:
		result: int = self._ops_tracer.Texture_interact(self._object_index, 0, [texture.object_index], [3], 1)

	def setKernel(self, kernel: List[float]) -> None:
		kernel_width: float = math.sqrt(len(kernel))
		if not kernel_width.is_integer():
			return

		data_width:		bytes	= struct.pack("i" * 2, int(kernel_width), 0)  # TODO: find a better way of implementation
		data_kernel:	bytes	= struct.pack("d" * len(kernel), *kernel)

		self._ops_tracer.Texture_config(self._object_index, 0, data_width, 8)
		self._ops_tracer.Texture_config(self._object_index, 1, data_kernel, len(kernel) * 8)


class Texture_Constant(Texture):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Texture_Type_getIndex("constant")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Texture_create(self._type_index)

	# Operation
	# ...


class Texture_Checkerboard(Texture):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Texture_Type_getIndex("checkerboard")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Texture_create(self._type_index)

	# Operation
	def setBoardSize(self, size: Vec3f) -> None:
		data:	bytes	= size.convertToBytes()
		result:	int		= self._ops_tracer.Texture_config(self._object_index, 0, data, len(data))


class Texture_Image(Texture):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Texture_Type_getIndex("image")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Texture_create(self._type_index)

	# Operation
	# ...


class Texture_Additor(Texture):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Texture_Type_getIndex("additor")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Texture_create(self._type_index)

	# Operation
	# ...


class Texture_Multiplier(Texture):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Texture_Type_getIndex("multiplier")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Texture_create(self._type_index)

	# Operation
	# ...


class Texture_Mapper_Sphere(Texture):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Texture_Type_getIndex("sphere")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Texture_create(self._type_index)

	# Operation
	# ...


class Texture_Mapper_Trimesh(Texture):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Texture_Type_getIndex("trimesh")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Texture_create(self._type_index)

	# Operation
	# ...


class Texture_Direction_Sphere(Texture):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Texture_Type_getIndex("sphere_dir")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Texture_create(self._type_index)

	# Operation
	# ...


class Texture_Direction_Trimesh(Texture):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Texture_Type_getIndex("trimesh_dir")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Texture_create(self._type_index)

	# Operation
	# ...
