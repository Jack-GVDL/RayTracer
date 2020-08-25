from Base import *
from .Tracer_Lib_Texture import *
from .Tracer_Lib_Scatter import *
from .Tracer_Lib_Hitable import *
from .Tracer_Lib_Light import *
from .Tracer_Lib_Surface import *


class Tracer_Sample:

	@ classmethod
	def buildScene_0(cls, scene: Scene) -> None:
		# shader
		texture_emissive:	Texture_Constant	= Texture_Constant()
		texture_ambient:	Texture_Constant	= Texture_Constant()
		texture_diffuse:	Texture_Constant	= Texture_Constant()
		texture_specular:	Texture_Constant	= Texture_Constant()
		texture_shininess:	Texture_Constant	= Texture_Constant()
		texture_normal:		Texture_Constant	= Texture_Constant()
		texture_reflective:	Texture_Constant	= Texture_Constant()

		texture_emissive.setPixel(		Vec3f(), Vec3f(0)	)
		texture_ambient.setPixel(		Vec3f(), Vec3f(0)	)
		texture_diffuse.setPixel(		Vec3f(), Vec3f(1)	)
		texture_specular.setPixel(		Vec3f(), Vec3f(1)	)
		texture_shininess.setPixel(		Vec3f(), Vec3f(1)	)
		texture_reflective.setPixel(	Vec3f(), Vec3f(0.9)	)

		# scatter
		scatter_light_1:	Scatter_Light = Scatter_Light()
		scatter_light_1.setTexture(texture_emissive,	Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_1.setTexture(texture_ambient,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_1.setTexture(texture_diffuse,		Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_1.setTexture(texture_specular,	Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_1.setTexture(texture_shininess,	Scatter_Light.TextureOffset.SHININESS)
		scatter_light_1.setTexture(texture_normal,		Scatter_Light.TextureOffset.NORMAL)

		scatter_reflection_1:	Scatter_Reflection = Scatter_Reflection()
		scatter_reflection_1.setTexture(texture_reflective,	Scatter_Reflection.TextureOffset.REFLECTIVE)

		scatter_refraction_1:	Scatter_Refraction = Scatter_Refraction()

		# scene
		hitable_sphere_1:	Hitable_Sphere = Hitable_Sphere()
		hitable_sphere_1.setCenter(Vec3f(0, 0, 0))
		hitable_sphere_1.setRadius(0.45)
		hitable_sphere_1.addScatter(scatter_light_1)

		hitable_sphere_2:	Hitable_Sphere = Hitable_Sphere()
		hitable_sphere_2.setCenter(Vec3f(1, 0, 0))
		hitable_sphere_2.setRadius(0.45)
		hitable_sphere_2.addScatter(scatter_reflection_1)
		hitable_sphere_2.addScatter(scatter_light_1)

		hitable_sphere_3:	Hitable_Sphere = Hitable_Sphere()
		hitable_sphere_3.setCenter(Vec3f(-1, 0, 0))
		hitable_sphere_3.setRadius(0.45)
		hitable_sphere_3.setTransmissive(Vec3f(0.8))
		hitable_sphere_3.setIndex(2)
		hitable_sphere_3.addScatter(scatter_refraction_1)
		hitable_sphere_3.addScatter(scatter_light_1)

		hitable_trimesh_1:	Hitable_Trimesh = Hitable_Trimesh()
		hitable_trimesh_1.setPoint_0(Vec3f(-5, -0.45, 2))
		hitable_trimesh_1.setPoint_1(Vec3f(5, -0.45, 2))
		hitable_trimesh_1.setPoint_2(Vec3f(-5, -0.45, -5))
		hitable_trimesh_1.addScatter(scatter_light_1)

		hitable_trimesh_2:	Hitable_Trimesh = Hitable_Trimesh()
		hitable_trimesh_2.setPoint_0(Vec3f(-5, -0.45, -5))
		hitable_trimesh_2.setPoint_1(Vec3f(5, -0.45, 2))
		hitable_trimesh_2.setPoint_2(Vec3f(5, -0.45, -5))
		hitable_trimesh_2.addScatter(scatter_light_1)

		hitable_trimesh_3:	Hitable_Trimesh = Hitable_Trimesh()
		hitable_trimesh_3.setPoint_0(Vec3f(-5, -0.45, -5))
		hitable_trimesh_3.setPoint_1(Vec3f(5, -0.45, -5))
		hitable_trimesh_3.setPoint_2(Vec3f(-5, 5, -5))
		hitable_trimesh_3.addScatter(scatter_light_1)

		hitable_trimesh_4:	Hitable_Trimesh = Hitable_Trimesh()
		hitable_trimesh_4.setPoint_0(Vec3f(-5, 5, -5))
		hitable_trimesh_4.setPoint_1(Vec3f(5, -0.45, -5))
		hitable_trimesh_4.setPoint_2(Vec3f(5, 5, -5))
		hitable_trimesh_4.addScatter(scatter_light_1)

		# light
		light_point_1:		Light_Point = Light_Point()
		light_point_1.setOrigin(Vec3f(1, 1, 1))
		light_point_1.setAttenuationCoeff(Vec3f(0, 0, 0.4))
		light_point_1.setColor(Vec3f(0.8))

		light_point_2:		Light_Point = Light_Point()
		light_point_2.setOrigin(Vec3f(-3, 1, -4))
		light_point_2.setAttenuationCoeff(Vec3f(0, 0, 0.4))
		light_point_2.setColor(Vec3f(0.8))

		light_dir_1:		Light_Directional = Light_Directional()
		light_dir_1.setOrientation(Vec3f(-1, 1, 1))
		light_dir_1.setColor(Vec3f(0.03))

		# scene
		scene.addHitable(hitable_sphere_1)
		scene.addHitable(hitable_sphere_2)
		scene.addHitable(hitable_sphere_3)
		scene.addHitable(hitable_trimesh_1)
		scene.addHitable(hitable_trimesh_2)
		scene.addHitable(hitable_trimesh_3)
		scene.addHitable(hitable_trimesh_4)
		scene.addLight(light_point_1)
		scene.addLight(light_point_2)
		scene.addLight(light_dir_1)

		# camera
		# TODO: not yet completed

	@ classmethod
	def buildScene_1(cls, scene: Scene) -> None:
		# shader
		texture_emissive:	Texture_Constant	= Texture_Constant()
		texture_ambient:	Texture_Constant	= Texture_Constant()
		texture_diffuse:	Texture_Constant	= Texture_Constant()
		texture_specular:	Texture_Constant	= Texture_Constant()
		texture_shininess:	Texture_Constant	= Texture_Constant()

		texture_emissive.setPixel(	Vec3f(), Vec3f(0))
		texture_ambient.setPixel(	Vec3f(), Vec3f(0))
		texture_diffuse.setPixel(	Vec3f(), Vec3f(1))
		texture_specular.setPixel(	Vec3f(), Vec3f(1))
		texture_shininess.setPixel(	Vec3f(), Vec3f(1))

		# scatter
		scatter_light_1:	Scatter_Light = Scatter_Light()
		scatter_light_1.setTexture(texture_emissive,	Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_1.setTexture(texture_ambient,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_1.setTexture(texture_diffuse,		Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_1.setTexture(texture_specular,	Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_1.setTexture(texture_shininess,	Scatter_Light.TextureOffset.SHININESS)

		# scene
		hitable_trimesh_1:	Hitable_Trimesh = Hitable_Trimesh()
		hitable_trimesh_1.setPoint_0(Vec3f(-0.5, 0, 0))
		hitable_trimesh_1.setPoint_1(Vec3f(0.5, 0, 0))
		hitable_trimesh_1.setPoint_2(Vec3f(0, 1, 0))
		hitable_trimesh_1.addScatter(scatter_light_1)

		# light
		light_point_1:			Light_Point = Light_Point()
		light_point_1.setOrigin(Vec3f(1, 1, 1))
		light_point_1.setColor(Vec3f(1))

		# scene
		scene.addHitable(hitable_trimesh_1)
		scene.addLight(light_point_1)

		# camera
		# TODO: not yet completed

	@ classmethod
	def buildScene_2(cls, scene: Scene) -> None:
		# surface
		surface_bmp:		Surface_BMP			= Surface_BMP()
		surface_bmp.setPath("../Image/IWS2000.bmp")
		surface_bmp.load()

		# shader
		texture_add_1:		Texture_Additor			= Texture_Additor()
		texture_multi_1:	Texture_Multiplier		= Texture_Multiplier()
		texture_trimesh_1:	Texture_Mapper_Trimesh	= Texture_Mapper_Trimesh()

		texture_emissive:	Texture_Constant	= Texture_Constant()
		texture_ambient:	Texture_Constant	= Texture_Constant()
		texture_diffuse:	Texture_Constant	= Texture_Constant()
		texture_specular:	Texture_Constant	= Texture_Constant()
		texture_shininess:	Texture_Constant	= Texture_Constant()
		texture_normal:		Texture_Constant	= Texture_Constant()

		texture_input_1:	Texture_Input		= Texture_Input()
		texture_input_2:	Texture_Input		= Texture_Input()
		texture_image_1:	Texture_Image		= Texture_Image()
		texture_image_2:	Texture_Image		= Texture_Image()
		texture_kernel_1:	Texture_Convolutor	= Texture_Convolutor()

		texture_emissive.setPixel(	Vec3f(), Vec3f(0))
		texture_ambient.setPixel(	Vec3f(), Vec3f(0))
		texture_diffuse.setPixel(	Vec3f(), Vec3f(1))
		texture_specular.setPixel(	Vec3f(), Vec3f(0))
		texture_shininess.setPixel(	Vec3f(), Vec3f(1))

		surface_bmp.convertToTexture(texture_image_1)
		texture_trimesh_1.addInput(texture_input_1, 0)
		texture_add_1.addInput(texture_trimesh_1, 0)
		texture_multi_1.addInput(texture_add_1, 0)
		texture_image_1.addInput(texture_multi_1, 0)

		surface_bmp.convertToTexture(texture_image_2)
		texture_image_2.addInput(texture_input_2, 0)
		texture_kernel_1.addInput(texture_multi_1, 0)
		texture_kernel_1.setTexture(texture_image_2)
		texture_kernel_1.setKernel([1.0 for _ in range(25)])

		texture_add_1.setAdditor(Vec3f(1, 0, 0))
		texture_multi_1.setMultiplier(Vec3f(750))

		# scatter
		scatter_light_1:	Scatter_Light = Scatter_Light()
		scatter_light_1.setTexture(texture_emissive,	Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_1.setTexture(texture_ambient,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_1.setTexture(texture_kernel_1,	Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_1.setTexture(texture_specular,	Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_1.setTexture(texture_shininess,	Scatter_Light.TextureOffset.SHININESS)
		scatter_light_1.setTexture(texture_normal,		Scatter_Light.TextureOffset.NORMAL)

		scatter_light_2:	Scatter_Light = Scatter_Light()
		scatter_light_2.setTexture(texture_emissive,	Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_2.setTexture(texture_ambient,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_2.setTexture(texture_kernel_1,	Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_2.setTexture(texture_specular,	Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_2.setTexture(texture_shininess,	Scatter_Light.TextureOffset.SHININESS)
		scatter_light_2.setTexture(texture_normal,		Scatter_Light.TextureOffset.NORMAL)

		# scene
		hitable_trimesh_1:	Hitable_Trimesh = Hitable_Trimesh()
		hitable_trimesh_1.setPoint_0(Vec3f(-2, 0, 0))
		hitable_trimesh_1.setPoint_1(Vec3f(2, 0, 0))
		hitable_trimesh_1.setPoint_2(Vec3f(-2, 4, 0))
		hitable_trimesh_1.addScatter(scatter_light_1)
		texture_trimesh_1.setTrimesh(hitable_trimesh_1)

		hitable_trimesh_2:	Hitable_Trimesh = Hitable_Trimesh()
		hitable_trimesh_2.setPoint_0(Vec3f(-2, 4, 0))
		hitable_trimesh_2.setPoint_1(Vec3f(2, 0, 0))
		hitable_trimesh_2.setPoint_2(Vec3f(2, 4, 0))
		hitable_trimesh_2.addScatter(scatter_light_2)

		# light
		light_point_1:		Light_Point = Light_Point()
		light_point_1.setOrigin(Vec3f(1, 1, 1))
		light_point_1.setColor(Vec3f(1))

		# scene
		scene.addHitable(hitable_trimesh_1)
		scene.addHitable(hitable_trimesh_2)
		scene.addLight(light_point_1)

		# camera
		# TODO: not yet completed

	@ classmethod
	def buildScene_3(cls, scene: Scene) -> None:
		# surface
		surface_bmp_1:		Surface_BMP		= Surface_BMP()
		surface_bmp_1.setPath("../Image/worldmap.bmp")
		surface_bmp_1.load()

		surface_bmp_2:		Surface_BMP		= Surface_BMP()
		surface_bmp_2.setPath("../Image/worldmap_ocean.bmp")
		surface_bmp_2.load()

		surface_bmp_3:		Surface_BMP		= Surface_BMP()
		surface_bmp_3.setPath("../Image/worldmap_normal.bmp")
		surface_bmp_3.load()

		# shader
		texture_add_1:			Texture_Additor			= Texture_Additor()
		texture_add_2:			Texture_Additor			= Texture_Additor()
		texture_multi_1:		Texture_Multiplier		= Texture_Multiplier()
		texture_multi_2:		Texture_Multiplier		= Texture_Multiplier()
		texture_multi_3:		Texture_Multiplier		= Texture_Multiplier()
		texture_input_1:		Texture_Input			= Texture_Input()

		texture_map_sphere_1:	Texture_Mapper_Sphere		= Texture_Mapper_Sphere()
		texture_dir_sphere_1:	Texture_Direction_Sphere	= Texture_Direction_Sphere()

		texture_emissive_1:		Texture_Constant	= Texture_Constant()
		texture_ambient_1:		Texture_Constant	= Texture_Constant()
		texture_diffuse_1:		Texture_Constant	= Texture_Constant()
		texture_specular_1:		Texture_Constant	= Texture_Constant()
		texture_shininess_1:	Texture_Constant	= Texture_Constant()
		texture_normal_1:		Texture_Constant	= Texture_Constant()

		texture_image_1:		Texture_Image		= Texture_Image()
		texture_image_2:		Texture_Image		= Texture_Image()
		texture_image_3:		Texture_Image		= Texture_Image()

		texture_emissive_1.setPixel(	Vec3f(), Vec3f(0))
		texture_ambient_1.setPixel(		Vec3f(), Vec3f(0))
		texture_diffuse_1.setPixel(		Vec3f(), Vec3f(1))
		texture_specular_1.setPixel(	Vec3f(), Vec3f(1))
		texture_shininess_1.setPixel(	Vec3f(), Vec3f(1))
		texture_normal_1.setPixel(		Vec3f(), Vec3f(0))

		texture_add_1.setAdditor(Vec3f(1, 1, 0))
		texture_add_2.setAdditor(Vec3f(-0.5, -0.5, -0.5))
		texture_multi_1.setMultiplier(Vec3f(2048 / 2, 1024 / 2, 0))
		texture_multi_2.setMultiplier(Vec3f(5))
		texture_multi_3.setMultiplier(Vec3f(0.5))

		surface_bmp_1.convertToTexture(texture_image_1)
		texture_map_sphere_1.addInput(texture_input_1, 0)
		texture_add_1.addInput(texture_map_sphere_1, 0)
		texture_multi_1.addInput(texture_add_1, 0)
		texture_image_1.addInput(texture_multi_1, 0)

		surface_bmp_2.convertToTexture(texture_image_2)
		texture_image_2.addInput(texture_multi_1, 0)

		surface_bmp_3.convertToTexture(texture_image_3)
		texture_multi_2.addInput(texture_add_1, 0)
		texture_image_3.addInput(texture_multi_1, 0)
		texture_add_2.addInput(texture_image_3, 0)
		texture_multi_3.addInput(texture_add_2, 0)
		texture_dir_sphere_1.addInput(texture_input_1, 0)
		texture_dir_sphere_1.addInput(texture_multi_3, 1)
		texture_multi_2.addInput(texture_dir_sphere_1, 0)

		# scatter
		scatter_light_1:	Scatter_Light = Scatter_Light()
		scatter_light_1.setTexture(texture_emissive_1,		Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_1.setTexture(texture_ambient_1,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_1.setTexture(texture_image_1,			Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_1.setTexture(texture_image_2,			Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_1.setTexture(texture_shininess_1,		Scatter_Light.TextureOffset.SHININESS)
		scatter_light_1.setTexture(texture_multi_2,			Scatter_Light.TextureOffset.NORMAL)

		# scene
		hitable_sphere_1:	Hitable_Sphere	= Hitable_Sphere()
		hitable_sphere_1.setRadius(1)
		hitable_sphere_1.setCenter(Vec3f(0))
		hitable_sphere_1.addScatter(scatter_light_1)

		texture_map_sphere_1.setSphere(hitable_sphere_1)
		texture_dir_sphere_1.setSphere(hitable_sphere_1)

		# light
		light_point_1:		Light_Point = Light_Point()
		light_point_1.setAttenuationCoeff(Vec3f(0, 0, 0.4))
		light_point_1.setOrigin(Vec3f(1, 2, 1))
		light_point_1.setColor(Vec3f(1))

		light_point_2:		Light_Point = Light_Point()
		light_point_2.setAttenuationCoeff(Vec3f(0, 0, 0.4))
		light_point_2.setOrigin(Vec3f(1, 0, 1))
		light_point_2.setColor(Vec3f(1))

		light_dir_1:		Light_Directional = Light_Directional()
		light_dir_1.setOrientation(Vec3f(0, 0, 1))
		light_dir_1.setColor(Vec3f(0.3))

		# scene
		scene.addHitable(hitable_sphere_1)
		scene.addLight(light_point_1)
		scene.addLight(light_point_2)
		scene.addLight(light_dir_1)

		# camera
		# TODO: not yet completed
