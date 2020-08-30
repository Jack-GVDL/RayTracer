import struct
import math
from typing import List, Any
from Base import Texture, Vec3f
from .Tracer_Lib_Hitable import Hitable_Trimesh, Hitable_Sphere


class Texture_Input(Texture):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "input")
		self._object_index	= self._ops_tracer.Texture_create(type_index)

	# Operation
	# ...


class Texture_Convolutor(Texture):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "convolutor")
		self._object_index	= self._ops_tracer.Texture_create(type_index)

	# Operation
	def setTexture(self, texture: Texture) -> None:
		result: int = self._ops_tracer.Texture_interact(self.object_index, 0, [texture.object_index], [2])

	def setKernel(self, kernel: List[float]) -> None:
		kernel_width: float = math.sqrt(len(kernel))
		if not kernel_width.is_integer():
			return

		data_width:		bytes	= struct.pack("i" * 2, int(kernel_width), 0)  # TODO: find a better way of implementation
		data_kernel:	bytes	= struct.pack("d" * len(kernel), *kernel)

		self._ops_tracer.Texture_config(self.object_index, 0, data_width)
		self._ops_tracer.Texture_config(self.object_index, 1, data_kernel)


class Texture_Constant(Texture):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "constant")
		self._object_index	= self._ops_tracer.Texture_create(type_index)

	# Operation
	# ...


class Texture_Checkerboard(Texture):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "checkerboard")
		self._object_index	= self._ops_tracer.Texture_create(type_index)

	# Operation
	def setBoardSize(self, size: Vec3f) -> None:
		data:	bytes	= size.convertToBytes()
		result:	int		= self._ops_tracer.Texture_config(self._object_index, 0, data)


class Texture_Image(Texture):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "image")
		self._object_index	= self._ops_tracer.Texture_create(type_index)

	# Operation
	# ...


class Texture_Additor(Texture):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "math_additor")
		self._object_index	= self._ops_tracer.Texture_create(type_index)

	# Operation
	def setAdditor(self, value: Vec3f) -> None:
		data:	bytes	= value.convertToBytes()
		result: int		= self._ops_tracer.Texture_config(self.object_index, 0, data)


class Texture_Multiplier(Texture):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "math_multiplier")
		self._object_index	= self._ops_tracer.Texture_create(type_index)

	# Operation
	def setMultiplier(self, value: Vec3f) -> None:
		data:	bytes	= value.convertToBytes()
		result: int		= self._ops_tracer.Texture_config(self.object_index, 0, data)


class Texture_Mapper_Sphere(Texture):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "mapper_sphere")
		self._object_index	= self._ops_tracer.Texture_create(type_index)

	# Operation
	def setSphere(self, sphere: Hitable_Sphere) -> None:
		result: int = self._ops_tracer.Texture_interact(self.object_index, 0, [sphere.object_index], [4])


class Texture_Mapper_Trimesh(Texture):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "mapper_trimesh")
		self._object_index	= self._ops_tracer.Texture_create(type_index)

	# Operation
	def setTrimesh(self, trimesh: Hitable_Trimesh) -> None:
		result: int = self._ops_tracer.Texture_interact(self.object_index, 0, [trimesh.object_index], [4])


class Texture_Direction_Sphere(Texture):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "dir_sphere")
		self._object_index	= self._ops_tracer.Texture_create(type_index)

	# Operation
	def setSphere(self, sphere: Hitable_Sphere) -> None:
		result: int = self._ops_tracer.Texture_interact(self.object_index, 0, [sphere.object_index], [4])


class Texture_Direction_Trimesh(Texture):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "dir_trimesh")
		self._object_index	= self._ops_tracer.Texture_create(type_index)

	# Operation
	def setTrimesh(self, trimesh: Hitable_Trimesh) -> None:
		result: int = self._ops_tracer.Texture_interact(self.object_index, 0, [trimesh.object_index], [2])
