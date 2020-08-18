from enum import IntEnum
from .Tracer_Base import Tracer_Base
from .Tracer_Texture import Texture


class Scatter(Tracer_Base):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	def setTexture(self, texture: Texture, offset: int) -> bool:
		if offset < 0:
			return False

		result: int = self._ops_tracer.Scatter_setTexture(self._object_index, texture.object_index, offset)
		return True if result == 0 else False
	
	def rmTexture(self, offset: int) -> bool:
		if offset < 0:
			return False

		result: int = self._ops_tracer.Scatter_rmTexture(self._object_index, offset)
		return True if result == 0 else False


class Scatter_Light(Scatter):

	class TextureOffset(IntEnum):
		DIFFUSE:	int = 0
		SPECULAR:	int = 1
		EMISSIVE:	int = 2
		AMBIENT:	int = 3
		SHININESS:	int = 4
		MAX:		int = 5

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Scatter_Type_getIndex("light")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Scatter_create(self._type_index)


class Scatter_Reflection(Scatter):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Scatter_Type_getIndex("reflection")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Scatter_create(self._type_index)


class Scatter_Refraction(Scatter):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Scatter_Type_getIndex("refraction")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Scatter_create(self._type_index)


class Scatter_Gradient(Scatter):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Scatter_Type_getIndex("gradient")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Scatter_create(self._type_index)


class Scatter_Emitter(Scatter):

	# Class
	_type_index:	int		= -1
	_is_initiated:	bool	= False

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		if not self._is_initiated:
			self._type_index	= self._ops_tracer.Scatter_Type_getIndex("emitter")
			assert self._type_index != -1, "Type not exist"

			self._is_initiated	= True

		self._object_index = self._ops_tracer.Scatter_create(self._type_index)
