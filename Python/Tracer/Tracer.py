from Base import *
from Lib import *
import os


# Data Structure
class Tracer(Tracer_Base):

	def __init__(self):
		super().__init__()

		# data
		# ...

	# Operation
	def setSampler(self, sampler: Sampler) -> None:
		self._ops_tracer.Tracer_setSampler(sampler.object_index)

	# Class Creator
	# scene
	def Scene(self) -> Scene:
		obj = Scene()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	# surface
	def Surface_Constant(self) -> Surface_Constant:
		obj = Surface_Constant()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Surface_BMP(self) -> Surface_BMP:
		obj = Surface_BMP()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	# texture
	def Texture_Input(self) -> Texture_Input:
		obj = Texture_Input()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Texture_Convolutor(self) -> Texture_Convolutor:
		obj = Texture_Convolutor()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Texture_Constant(self) -> Texture_Constant:
		obj = Texture_Constant()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Texture_Checkerboard(self) -> Texture_Checkerboard:
		obj = Texture_Checkerboard()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Texture_Image(self) -> Texture_Image:
		obj = Texture_Image()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Texture_Additor(self) -> Texture_Additor:
		obj = Texture_Additor()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Texture_Multiplier(self) -> Texture_Multiplier:
		obj = Texture_Multiplier()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Texture_Mapper_Sphere(self) -> Texture_Mapper_Sphere:
		obj = Texture_Mapper_Sphere()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Texture_Mapper_Trimesh(self) -> Texture_Mapper_Trimesh:
		obj = Texture_Mapper_Trimesh()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Texture_Direction_Sphere(self) -> Texture_Direction_Sphere:
		obj = Texture_Direction_Sphere()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Texture_Direction_Trimesh(self) -> Texture_Direction_Trimesh:
		obj = Texture_Direction_Trimesh()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	# material
	def Material_Default(self) -> Material_Default:
		obj = Material_Default()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	# scatter
	def Scatter_Light(self) -> Scatter_Light:
		obj = Scatter_Light()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Scatter_Reflection(self) -> Scatter_Reflection:
		obj = Scatter_Reflection()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Scatter_Refraction(self) -> Scatter_Refraction:
		obj = Scatter_Refraction()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Scatter_Gradient(self) -> Scatter_Gradient:
		obj = Scatter_Gradient()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Scatter_Emitter(self) -> Scatter_Emitter:
		obj = Scatter_Emitter()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Scatter_Random(self) -> Scatter_Random:
		obj = Scatter_Random()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Scatter_AnyHit(self) -> Scatter_AnyHit:
		obj = Scatter_AnyHit()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	# hitable
	def Hitable_Sphere(self) -> Hitable_Sphere:
		obj = Hitable_Sphere()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Hitable_Trimesh(self) -> Hitable_Trimesh:
		obj = Hitable_Trimesh()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Hitable_AABB(self) -> Hitable_AABB:
		obj = Hitable_AABB()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	# aabb
	def RIAS_AABB(self) -> RIAS_AABB:
		obj = RIAS_AABB()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	# light
	def Light_Directional(self) -> Light_Directional:
		obj = Light_Directional()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	def Light_Point(self) -> Light_Point:
		obj = Light_Point()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	# camera
	def Camera_Default(self) -> Camera_Default:
		obj = Camera_Default()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj

	# sampler
	def Sampler_Grid(self) -> Sampler_Grid:
		obj = Sampler_Grid()
		obj.setOps_tracer(self._ops_tracer)
		obj.start()
		return obj


# Operation
# TODO: should move these things to class
# add dll directory
os.add_dll_directory("C:/WINDOWS/system32")
os.add_dll_directory("D:/Anaconda/Library/mingw-w64/bin")  # TODO: it should not use Anaconda
