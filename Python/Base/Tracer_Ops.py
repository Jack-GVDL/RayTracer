from typing import List


class Tracer_Ops:

	def __init__(self):
		super().__init__()

	# Operation
	# test
	# ...
	
	# surface
	def Surface_create(self, type: int) -> int:
		raise NotImplementedError

	def Surface_destroy(self, index: int) -> int:
		raise NotImplementedError

	def Surface_config(self, index: int, type: int, data: List[bytes], size: int) -> int:
		raise NotImplementedError

	# texture
	# ...

	# scatter
	def Scatter_addTexture(self, scatter_index: int, texture_index: int, offset: int) -> int:
		raise NotImplementedError

	def Scatter_rmTexture(self, scatter_index: int, offset: int) -> int:
		raise NotImplementedError

	# hitable
	# ...
