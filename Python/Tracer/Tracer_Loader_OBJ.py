from typing import *
from Base import Vec3f, Hitable
from Lib import Hitable_Trimesh
from Tracer.Tracer import Tracer
from Tracer.File_OBJ import File_OBJ


# Data Structure
class Loader_OBJ:

	def __init__(self):
		super().__init__()

		# data
		self.file_obj:		File_OBJ		= None
		self.tracer:		Tracer			= None

		self.scale:			List[float]		= [1.0, 1.0, 1.0]

		self.hitable_list:	List[Hitable]	= []

	def __del__(self):
		return

	# Operation Handling
	def load(self) -> None:
		if self.file_obj is None:
			return
		if self.tracer is None:
			return

		for face in self.file_obj.face_list:
			# get vertex
			vertex_0:	Tuple[float, float, float]	= self.file_obj.vertex_list[face[0] - 1]
			vertex_1:	Tuple[float, float, float]	= self.file_obj.vertex_list[face[1] - 1]
			vertex_2:	Tuple[float, float, float]	= self.file_obj.vertex_list[face[2] - 1]

			# create hitable
			hitable: Hitable_Trimesh = self.tracer.Hitable_Trimesh()
			hitable.setPoint_0(
				Vec3f(vertex_0[0] * self.scale[0], vertex_0[1] * self.scale[1], vertex_0[2] * self.scale[2]))
			hitable.setPoint_1(
				Vec3f(vertex_1[0] * self.scale[0], vertex_1[1] * self.scale[1], vertex_1[2] * self.scale[2]))
			hitable.setPoint_2(
				Vec3f(vertex_2[0] * self.scale[0], vertex_2[1] * self.scale[1], vertex_2[2] * self.scale[2]))

			# add to self list
			self.hitable_list.append(hitable)
