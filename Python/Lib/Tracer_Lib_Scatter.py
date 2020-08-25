from enum import IntEnum
from Base import Scatter


class Scatter_Light(Scatter):

	class TextureOffset(IntEnum):
		DIFFUSE:	int = 0
		SPECULAR:	int = 1
		EMISSIVE:	int = 2
		AMBIENT:	int = 3
		SHININESS:	int = 4
		NORMAL:		int = 5
		MAX:		int = 6

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "light")
		self._object_index	= self._ops_tracer.Scatter_create(type_index)


class Scatter_Reflection(Scatter):

	class TextureOffset(IntEnum):
		REFLECTIVE:		int = 0
		MAX:			int = 1

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "reflection")
		self._object_index	= self._ops_tracer.Scatter_create(type_index)


class Scatter_Refraction(Scatter):

	class TextureOffset(IntEnum):
		MAX:			int = 0

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "refraction")
		self._object_index	= self._ops_tracer.Scatter_create(type_index)


class Scatter_Gradient(Scatter):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "gradient")
		self._object_index	= self._ops_tracer.Scatter_create(type_index)


class Scatter_Emitter(Scatter):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		type_index: int		= self._getType_(self._ops_tracer, "emitter")
		self._object_index	= self._ops_tracer.Scatter_create(type_index)
