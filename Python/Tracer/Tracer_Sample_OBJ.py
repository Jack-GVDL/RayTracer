from typing import *
from Base import *
from Lib import *
from .Tracer import Tracer
from .Tracer_Loader_OBJ import Loader_OBJ
from .File_OBJ import File_OBJ
from .Tracer_Sample import Tracer_Sample


class Tracer_Sample_Cube(Tracer_Sample):

	def __init__(self):
		super().__init__()

	def _load_(self, tracer: Tracer) -> None:
		# object
		texture_emissive:		Texture_Constant	= tracer.Texture_Constant()
		texture_ambient:		Texture_Constant	= tracer.Texture_Constant()
		texture_diffuse:		Texture_Constant	= tracer.Texture_Constant()
		texture_specular:		Texture_Constant	= tracer.Texture_Constant()
		texture_shininess:		Texture_Constant	= tracer.Texture_Constant()
		texture_normal:			Texture_Constant	= tracer.Texture_Constant()
		texture_reflective:		Texture_Constant	= tracer.Texture_Constant()

		scatter_light_1:		Scatter_Light		= tracer.Scatter_Light()
		scatter_any_hit_1:		Scatter_AnyHit		= tracer.Scatter_AnyHit()
		material_diffuse_1:		Material_Default	= tracer.Material_Default()

		light_point_1:			Light_Point			= tracer.Light_Point()
		scene: 					Scene				= tracer.Scene()

		# texture
		texture_emissive.setPixel(		Vec3f(), Vec3f(0)	)
		texture_ambient.setPixel(		Vec3f(), Vec3f(0)	)
		texture_diffuse.setPixel(		Vec3f(), Vec3f(1)	)
		texture_specular.setPixel(		Vec3f(), Vec3f(1)	)
		texture_shininess.setPixel(		Vec3f(), Vec3f(0)	)
		texture_reflective.setPixel(	Vec3f(), Vec3f(0)	)

		# scatter
		scatter_light_1.setTexture(texture_emissive,	Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_1.setTexture(texture_ambient,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_1.setTexture(texture_diffuse,		Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_1.setTexture(texture_specular,	Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_1.setTexture(texture_shininess,	Scatter_Light.TextureOffset.SHININESS)
		scatter_light_1.setTexture(texture_normal,		Scatter_Light.TextureOffset.NORMAL)
		scatter_light_1.addScatter(scatter_any_hit_1)

		# material
		material_diffuse_1.addScatter(scatter_light_1)

		# load object
		file_obj_1:	File_OBJ	= File_OBJ()
		file_obj_1.path = "../OBJ/cube.obj"
		file_obj_1.load()

		loader_obj_1:	Loader_OBJ	= Loader_OBJ()
		loader_obj_1.file_obj	= file_obj_1
		loader_obj_1.tracer		= tracer
		loader_obj_1.scale		= [1.0, 1.0, 1.0]
		loader_obj_1.load()

		# hitable
		for hitable in loader_obj_1.hitable_list:
			hitable.setMaterial(material_diffuse_1)

		# light
		light_point_1.setOrigin(Vec3f(2, 2, 2))
		light_point_1.setAttenuation(Vec3f(0, 0, 0.4))
		light_point_1.setColor(Vec3f(0.5))

		# scene
		for hitable in loader_obj_1.hitable_list:
			scene.addHitable(hitable)
		scene.addLight(light_point_1)


class Tracer_Sample_Magnolia(Tracer_Sample):

	def __init__(self):
		super().__init__()

	def _load_(self, tracer: Tracer) -> None:
		# object
		texture_emissive:		Texture_Constant	= tracer.Texture_Constant()
		texture_ambient:		Texture_Constant	= tracer.Texture_Constant()
		texture_diffuse:		Texture_Constant	= tracer.Texture_Constant()
		texture_specular:		Texture_Constant	= tracer.Texture_Constant()
		texture_shininess:		Texture_Constant	= tracer.Texture_Constant()
		texture_normal:			Texture_Constant	= tracer.Texture_Constant()

		scatter_light_1:		Scatter_Light		= tracer.Scatter_Light()
		scatter_any_hit_1:		Scatter_AnyHit		= tracer.Scatter_AnyHit()
		material_diffuse_1:		Material_Default	= tracer.Material_Default()

		light_point_1:			Light_Point			= tracer.Light_Point()
		light_point_2:			Light_Point			= tracer.Light_Point()
		light_point_3:			Light_Point			= tracer.Light_Point()

		rias_aabb_1:			RIAS_AABB			= tracer.RIAS_AABB()
		scene: 					Scene				= tracer.Scene()

		# texture
		texture_emissive.setPixel(		Vec3f(), Vec3f(0)	)
		texture_ambient.setPixel(		Vec3f(), Vec3f(0)	)
		texture_diffuse.setPixel(		Vec3f(), Vec3f(1)	)
		texture_specular.setPixel(		Vec3f(), Vec3f(1)	)
		texture_shininess.setPixel(		Vec3f(), Vec3f(0)	)
		texture_normal.setPixel(		Vec3f(), Vec3f(0)	)

		# scatter
		scatter_light_1.setTexture(			texture_emissive,	Scatter_Light.TextureOffset.EMISSIVE		)
		scatter_light_1.setTexture(			texture_ambient,	Scatter_Light.TextureOffset.AMBIENT			)
		scatter_light_1.setTexture(			texture_diffuse,	Scatter_Light.TextureOffset.DIFFUSE			)
		scatter_light_1.setTexture(			texture_specular,	Scatter_Light.TextureOffset.SPECULAR		)
		scatter_light_1.setTexture(			texture_shininess,	Scatter_Light.TextureOffset.SHININESS		)
		scatter_light_1.setTexture(			texture_normal,		Scatter_Light.TextureOffset.NORMAL			)

		scatter_light_1.addScatter(scatter_any_hit_1)

		# material
		material_diffuse_1.addScatter(scatter_light_1)

		# load object
		file_obj_1 = File_OBJ()
		file_obj_1.path = "../OBJ/magnolia.obj"
		file_obj_1.load()

		loader_obj_1 = Loader_OBJ()
		loader_obj_1.file_obj	= file_obj_1
		loader_obj_1.tracer		= tracer
		loader_obj_1.scale		= [0.05, 0.05, 0.05]
		loader_obj_1.load()

		# hitable
		for hitable in loader_obj_1.hitable_list:
			hitable.setMaterial(material_diffuse_1)

		# light
		light_point_1.setOrigin(Vec3f(2, 2, -2))
		light_point_1.setAttenuation(Vec3f(0, 0, 0.4))
		light_point_1.setColor(Vec3f(0.8, 0, 0))

		light_point_2.setOrigin(Vec3f(-2, 2, 2))
		light_point_2.setAttenuation(Vec3f(0, 0, 0.4))
		light_point_2.setColor(Vec3f(0, 0, 0.8))

		light_point_3.setOrigin(Vec3f(0, 3, 0))
		light_point_3.setAttenuation(Vec3f(0, 0, 0.4))
		light_point_3.setColor(Vec3f(0.15))

		# rias
		rias_aabb_1.load()

		# scene
		scene.addRIAS(rias_aabb_1)
		scene.addLight(light_point_1)
		scene.addLight(light_point_2)
		scene.addLight(light_point_3)
