from Base import *
from Lib import *
from .Tracer import Tracer


class Tracer_Sample:

	@ classmethod
	def buildScene_singleSphere(cls, tracer: Tracer) -> None:
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

		hitable_sphere_1:		Hitable_Sphere		= tracer.Hitable_Sphere()

		light_point_1:			Light_Point			= tracer.Light_Point()

		scene: 					Scene				= tracer.Scene()

		# texture
		texture_emissive.setPixel(		Vec3f(), Vec3f(0)	)
		texture_ambient.setPixel(		Vec3f(), Vec3f(0)	)
		texture_diffuse.setPixel(		Vec3f(), Vec3f(1)	)
		texture_specular.setPixel(		Vec3f(), Vec3f(0)	)
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

		# hitable
		hitable_sphere_1.setCenter(Vec3f(0, 0, 0))
		hitable_sphere_1.setRadius(0.45)
		hitable_sphere_1.setMaterial(material_diffuse_1)

		# light
		light_point_1.setOrigin(Vec3f(1, 1, 1))
		light_point_1.setAttenuation(Vec3f(0, 0, 0.4))
		light_point_1.setColor(Vec3f(0.5))

		# scene
		scene.addHitable(hitable_sphere_1)
		scene.addLight(light_point_1)

	@ classmethod
	def buildScene_0(cls, tracer: Tracer, aabb_level: int = 0) -> None:
		# object
		texture_emissive:		Texture_Constant	= tracer.Texture_Constant()
		texture_ambient:		Texture_Constant	= tracer.Texture_Constant()
		texture_diffuse:		Texture_Constant	= tracer.Texture_Constant()
		texture_specular:		Texture_Constant	= tracer.Texture_Constant()
		texture_shininess:		Texture_Constant	= tracer.Texture_Constant()
		texture_normal:			Texture_Constant	= tracer.Texture_Constant()
		texture_reflective:		Texture_Constant	= tracer.Texture_Constant()

		scatter_light_1:		Scatter_Light		= tracer.Scatter_Light()
		scatter_light_2:		Scatter_Light		= tracer.Scatter_Light()
		scatter_reflection_1:	Scatter_Reflection	= tracer.Scatter_Reflection()
		scatter_refraction_1:	Scatter_Refraction	= tracer.Scatter_Refraction()
		scatter_random_1:		Scatter_Random		= tracer.Scatter_Random()
		scatter_random_2:		Scatter_Random		= tracer.Scatter_Random()
		scatter_any_hit_1:		Scatter_AnyHit		= tracer.Scatter_AnyHit()

		material_diffuse_1:		Material_Default	= tracer.Material_Default()
		material_diffuse_2:		Material_Default	= tracer.Material_Default()
		material_reflective:	Material_Default	= tracer.Material_Default()
		material_refractive:	Material_Default	= tracer.Material_Default()

		hitable_sphere_1:		Hitable_Sphere		= tracer.Hitable_Sphere()
		hitable_sphere_2:		Hitable_Sphere		= tracer.Hitable_Sphere()
		hitable_sphere_3:		Hitable_Sphere		= tracer.Hitable_Sphere()
		hitable_trimesh_1:		Hitable_Trimesh		= tracer.Hitable_Trimesh()
		hitable_trimesh_2:		Hitable_Trimesh		= tracer.Hitable_Trimesh()
		hitable_trimesh_3:		Hitable_Trimesh		= tracer.Hitable_Trimesh()
		hitable_trimesh_4:		Hitable_Trimesh		= tracer.Hitable_Trimesh()

		# TODO: test
		# aabb_1:					AABB_Default		= tracer.AABB_Default()

		light_point_1:			Light_Point			= tracer.Light_Point()
		light_point_2:			Light_Point			= tracer.Light_Point()
		light_dir_1:			Light_Directional	= tracer.Light_Directional()

		scene: 					Scene				= tracer.Scene()

		# texture
		texture_emissive.setPixel(		Vec3f(), Vec3f(0)	)
		texture_ambient.setPixel(		Vec3f(), Vec3f(0)	)
		texture_diffuse.setPixel(		Vec3f(), Vec3f(1)	)
		texture_specular.setPixel(		Vec3f(), Vec3f(1)	)
		texture_shininess.setPixel(		Vec3f(), Vec3f(1)	)
		texture_reflective.setPixel(	Vec3f(), Vec3f(1)	)

		# scatter
		scatter_light_1.setTexture(texture_emissive,	Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_1.setTexture(texture_ambient,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_1.setTexture(texture_diffuse,		Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_1.setTexture(texture_specular,	Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_1.setTexture(texture_shininess,	Scatter_Light.TextureOffset.SHININESS)
		scatter_light_1.setTexture(texture_normal,		Scatter_Light.TextureOffset.NORMAL)

		scatter_light_2.setTexture(texture_emissive,	Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_2.setTexture(texture_ambient,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_2.setTexture(texture_diffuse,		Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_2.setTexture(texture_specular,	Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_2.setTexture(texture_shininess,	Scatter_Light.TextureOffset.SHININESS)
		scatter_light_2.setTexture(texture_normal,		Scatter_Light.TextureOffset.NORMAL)

		scatter_reflection_1.setTexture(texture_reflective,	Scatter_Reflection.TextureOffset.REFLECTIVE)

		scatter_random_1.setRadius(0.05)
		scatter_random_1.setParallel(False)
		scatter_random_1.setRaySize(1)

		scatter_random_2.setRadius(0.1)
		scatter_random_2.setParallel(False)
		scatter_random_2.setRaySize(1)

		scatter_light_1.addScatter(scatter_any_hit_1)
		scatter_light_2.addScatter(scatter_random_1)
		scatter_random_1.addScatter(scatter_any_hit_1)

		scatter_reflection_1.addScatter(scatter_random_2)

		# material
		material_diffuse_1.addScatter(scatter_light_1)

		material_diffuse_2.addScatter(scatter_light_2)

		material_reflective.addScatter(scatter_reflection_1)
		material_reflective.addScatter(scatter_light_1)

		material_refractive.addScatter(scatter_refraction_1)
		material_refractive.addScatter(scatter_light_1)
		material_refractive.setTransmissive(Vec3f(0.5))
		material_refractive.setIndex(1.5)

		# hitable
		hitable_sphere_1.setCenter(Vec3f(0, 0, 0))
		hitable_sphere_1.setRadius(0.45)
		hitable_sphere_1.setMaterial(material_diffuse_1)

		hitable_sphere_2.setCenter(Vec3f(1, 0, 0))
		hitable_sphere_2.setRadius(0.45)
		hitable_sphere_2.setMaterial(material_reflective)

		hitable_sphere_3.setCenter(Vec3f(-1, 0, 0))
		hitable_sphere_3.setRadius(0.45)
		hitable_sphere_3.setMaterial(material_refractive)

		hitable_trimesh_1.setPoint_0(Vec3f(-5, -0.45, 2))
		hitable_trimesh_1.setPoint_1(Vec3f(5, -0.45, 2))
		hitable_trimesh_1.setPoint_2(Vec3f(-5, -0.45, -5))
		hitable_trimesh_1.setMaterial(material_diffuse_2)

		hitable_trimesh_2.setPoint_0(Vec3f(-5, -0.45, -5))
		hitable_trimesh_2.setPoint_1(Vec3f(5, -0.45, 2))
		hitable_trimesh_2.setPoint_2(Vec3f(5, -0.45, -5))
		hitable_trimesh_2.setMaterial(material_diffuse_2)

		hitable_trimesh_3.setPoint_0(Vec3f(-5, -0.45, -5))
		hitable_trimesh_3.setPoint_1(Vec3f(5, -0.45, -5))
		hitable_trimesh_3.setPoint_2(Vec3f(-5, 5, -5))
		hitable_trimesh_3.setMaterial(material_diffuse_1)

		hitable_trimesh_4.setPoint_0(Vec3f(-5, 5, -5))
		hitable_trimesh_4.setPoint_1(Vec3f(5, -0.45, -5))
		hitable_trimesh_4.setPoint_2(Vec3f(5, 5, -5))
		hitable_trimesh_4.setMaterial(material_diffuse_1)

		if aabb_level == 0:
			scene.addHitable(hitable_trimesh_1)
			scene.addHitable(hitable_trimesh_2)
			scene.addHitable(hitable_trimesh_3)
			scene.addHitable(hitable_trimesh_4)

			scene.addHitable(hitable_sphere_1)
			scene.addHitable(hitable_sphere_2)
			scene.addHitable(hitable_sphere_3)

		else:
			# TODO: test
			# aabb_1.load()
			# scene.addAABB(aabb_1)
			pass

		# light
		light_point_1.setOrigin(Vec3f(1, 1, 1))
		light_point_1.setAttenuation(Vec3f(0, 0, 0.4))
		light_point_1.setColor(Vec3f(0.3))

		light_point_2.setOrigin(Vec3f(-3, 1, -4))
		light_point_2.setAttenuation(Vec3f(0, 0, 0.4))
		light_point_2.setColor(Vec3f(0.3))

		light_dir_1.setOrientation(Vec3f(-1, 1, 1))
		light_dir_1.setColor(Vec3f(0.03))

		# scene
		scene.addLight(light_point_1)
		scene.addLight(light_point_2)
		scene.addLight(light_dir_1)

	@ classmethod
	def buildScene_1(cls, tracer: Tracer) -> None:
		# object
		surface_bmp:		Surface_BMP				= tracer.Surface_BMP()

		texture_add_1:		Texture_Additor			= tracer.Texture_Additor()
		texture_multi_1:	Texture_Multiplier		= tracer.Texture_Multiplier()
		texture_trimesh_1:	Texture_Mapper_Trimesh	= tracer.Texture_Mapper_Trimesh()

		texture_emissive:	Texture_Constant		= tracer.Texture_Constant()
		texture_ambient:	Texture_Constant		= tracer.Texture_Constant()
		texture_diffuse:	Texture_Constant		= tracer.Texture_Constant()
		texture_specular:	Texture_Constant		= tracer.Texture_Constant()
		texture_shininess:	Texture_Constant		= tracer.Texture_Constant()
		texture_normal:		Texture_Constant		= tracer.Texture_Constant()
		texture_input_1:	Texture_Input			= tracer.Texture_Input()
		texture_input_2:	Texture_Input			= tracer.Texture_Input()
		texture_image_1:	Texture_Image			= tracer.Texture_Image()
		texture_image_2:	Texture_Image			= tracer.Texture_Image()
		texture_kernel_1:	Texture_Convolutor		= tracer.Texture_Convolutor()

		material_1:			Material_Default		= tracer.Material_Default()
		material_2:			Material_Default		= tracer.Material_Default()

		scatter_light_1:	Scatter_Light			= tracer.Scatter_Light()
		scatter_light_2:	Scatter_Light			= tracer.Scatter_Light()
		scatter_any_hit_1:	Scatter_AnyHit			= tracer.Scatter_AnyHit()

		hitable_trimesh_1:	Hitable_Trimesh 		= tracer.Hitable_Trimesh()
		hitable_trimesh_2:	Hitable_Trimesh 		= tracer.Hitable_Trimesh()

		light_dir_1:		Light_Directional 		= tracer.Light_Directional()

		# surface
		surface_bmp.setPath("../Image/IWS2000.bmp")
		surface_bmp.load()

		# shader
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

		texture_add_1.setAdditor(Vec3f(2, 1.5, 0))
		texture_multi_1.setMultiplier(Vec3f(500))

		texture_trimesh_1.setTrimesh(hitable_trimesh_1)

		# scatter
		scatter_light_1.setTexture(texture_emissive,	Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_1.setTexture(texture_ambient,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_1.setTexture(texture_image_1,		Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_1.setTexture(texture_specular,	Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_1.setTexture(texture_shininess,	Scatter_Light.TextureOffset.SHININESS)
		scatter_light_1.setTexture(texture_normal,		Scatter_Light.TextureOffset.NORMAL)

		scatter_light_2.setTexture(texture_emissive,	Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_2.setTexture(texture_ambient,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_2.setTexture(texture_kernel_1,	Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_2.setTexture(texture_specular,	Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_2.setTexture(texture_shininess,	Scatter_Light.TextureOffset.SHININESS)
		scatter_light_2.setTexture(texture_normal,		Scatter_Light.TextureOffset.NORMAL)

		scatter_light_1.addScatter(scatter_any_hit_1)
		scatter_light_2.addScatter(scatter_any_hit_1)

		# material
		material_1.addScatter(scatter_light_1)
		material_2.addScatter(scatter_light_2)

		# scene
		hitable_trimesh_1.setPoint_0(Vec3f(-2, -4, 0))
		hitable_trimesh_1.setPoint_1(Vec3f(2, -4, 0))
		hitable_trimesh_1.setPoint_2(Vec3f(-2, 4, 0))
		hitable_trimesh_1.setMaterial(material_1)

		hitable_trimesh_2.setPoint_0(Vec3f(-2, 4.05, 0))
		hitable_trimesh_2.setPoint_1(Vec3f(2, -3.95, 0))
		hitable_trimesh_2.setPoint_2(Vec3f(2, 4.05, 0))
		hitable_trimesh_2.setMaterial(material_2)

		# light
		light_dir_1.setColor(Vec3f(0.8))
		light_dir_1.setOrientation(Vec3f(0, 0, 1))

		# scene
		scene: Scene = tracer.Scene()
		scene.addHitable(hitable_trimesh_1)
		scene.addHitable(hitable_trimesh_2)
		scene.addLight(light_dir_1)

	@ classmethod
	def buildScene_2(cls, tracer: Tracer) -> None:
		# object
		surface_bmp_1:			Surface_BMP					= tracer.Surface_BMP()
		surface_bmp_2:			Surface_BMP					= tracer.Surface_BMP()
		surface_bmp_3:			Surface_BMP					= tracer.Surface_BMP()

		texture_add_1:			Texture_Additor				= tracer.Texture_Additor()
		texture_add_2:			Texture_Additor				= tracer.Texture_Additor()
		texture_multi_1:		Texture_Multiplier			= tracer.Texture_Multiplier()
		texture_multi_2:		Texture_Multiplier			= tracer.Texture_Multiplier()
		texture_multi_3:		Texture_Multiplier			= tracer.Texture_Multiplier()
		texture_input_1:		Texture_Input				= tracer.Texture_Input()
		texture_map_sphere_1:	Texture_Mapper_Sphere		= tracer.Texture_Mapper_Sphere()
		texture_dir_sphere_1:	Texture_Direction_Sphere	= tracer.Texture_Direction_Sphere()
		texture_emissive_1:		Texture_Constant			= tracer.Texture_Constant()
		texture_ambient_1:		Texture_Constant			= tracer.Texture_Constant()
		texture_diffuse_1:		Texture_Constant			= tracer.Texture_Constant()
		texture_specular_1:		Texture_Constant			= tracer.Texture_Constant()
		texture_shininess_1:	Texture_Constant			= tracer.Texture_Constant()
		texture_normal_1:		Texture_Constant			= tracer.Texture_Constant()
		texture_image_1:		Texture_Image				= tracer.Texture_Image()
		texture_image_2:		Texture_Image				= tracer.Texture_Image()
		texture_image_3:		Texture_Image				= tracer.Texture_Image()

		scatter_light_1:		Scatter_Light				= tracer.Scatter_Light()
		scatter_any_hit_1:		Scatter_AnyHit				= tracer.Scatter_AnyHit()

		material_1:				Material_Default			= tracer.Material_Default()

		hitable_sphere_1:		Hitable_Sphere				= tracer.Hitable_Sphere()

		light_point_1:			Light_Point 				= tracer.Light_Point()
		light_point_2:			Light_Point 				= tracer.Light_Point()
		light_dir_1:			Light_Directional 			= tracer.Light_Directional()

		# surface
		surface_bmp_1.setPath("../Image/worldmap.bmp")
		surface_bmp_1.load()

		surface_bmp_2.setPath("../Image/worldmap_ocean.bmp")
		surface_bmp_2.load()

		surface_bmp_3.setPath("../Image/worldmap_normal.bmp")
		surface_bmp_3.load()

		# shader
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
		scatter_light_1.setTexture(texture_emissive_1,		Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_1.setTexture(texture_ambient_1,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_1.setTexture(texture_image_1,			Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_1.setTexture(texture_image_2,			Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_1.setTexture(texture_shininess_1,		Scatter_Light.TextureOffset.SHININESS)
		scatter_light_1.setTexture(texture_multi_2,			Scatter_Light.TextureOffset.NORMAL)

		scatter_light_1.addScatter(scatter_any_hit_1)

		# material
		material_1.addScatter(scatter_light_1)

		# hitable
		hitable_sphere_1.setRadius(1)
		hitable_sphere_1.setCenter(Vec3f(0))
		hitable_sphere_1.setMaterial(material_1)

		texture_map_sphere_1.setSphere(hitable_sphere_1)
		texture_dir_sphere_1.setSphere(hitable_sphere_1)

		# light
		light_point_1.setAttenuation(Vec3f(0, 0, 0.4))
		light_point_1.setOrigin(Vec3f(1, 2, 1))
		light_point_1.setColor(Vec3f(0.8))

		light_point_2.setAttenuation(Vec3f(0, 0, 0.4))
		light_point_2.setOrigin(Vec3f(1, 0, 1))
		light_point_2.setColor(Vec3f(0.8))

		light_dir_1.setOrientation(Vec3f(0, 0, 1))
		light_dir_1.setColor(Vec3f(0.3))

		# scene
		scene: Scene = tracer.Scene()

		scene.addHitable(hitable_sphere_1)

		scene.addLight(light_point_1)
		scene.addLight(light_point_2)
		scene.addLight(light_dir_1)

	@ classmethod
	def buildScene_3(cls, tracer: Tracer, aabb_level: int = 0) -> None:
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

		material_1:				Material_Default	= tracer.Material_Default()

		aabb_1:					AABB_Default		= tracer.AABB_Default()

		light_point_1:			Light_Point			= tracer.Light_Point()
		light_point_2:			Light_Point			= tracer.Light_Point()
		light_dir_1:			Light_Directional	= tracer.Light_Directional()

		scene: 					Scene				= tracer.Scene()

		# texture
		texture_emissive.setPixel(		Vec3f(), Vec3f(0)	)
		texture_ambient.setPixel(		Vec3f(), Vec3f(0)	)
		texture_diffuse.setPixel(		Vec3f(), Vec3f(1)	)
		texture_specular.setPixel(		Vec3f(), Vec3f(1)	)
		texture_shininess.setPixel(		Vec3f(), Vec3f(1)	)
		texture_reflective.setPixel(	Vec3f(), Vec3f(1)	)

		# scatter
		scatter_light_1.setTexture(texture_emissive,	Scatter_Light.TextureOffset.EMISSIVE)
		scatter_light_1.setTexture(texture_ambient,		Scatter_Light.TextureOffset.AMBIENT)
		scatter_light_1.setTexture(texture_diffuse,		Scatter_Light.TextureOffset.DIFFUSE)
		scatter_light_1.setTexture(texture_specular,	Scatter_Light.TextureOffset.SPECULAR)
		scatter_light_1.setTexture(texture_shininess,	Scatter_Light.TextureOffset.SHININESS)
		scatter_light_1.setTexture(texture_normal,		Scatter_Light.TextureOffset.NORMAL)

		scatter_light_1.addScatter(scatter_any_hit_1)

		# material
		material_1.addScatter(scatter_light_1)

		# hitable
		w_half: int		= 3
		h_half: int		= 3
		radius: float	= 0.2

		if aabb_level == 0:
			for z in range(-2, 2):
				for y in range(-h_half, h_half + 1):
					for x in range(-w_half, w_half + 1):

						hitable_sphere: Hitable_Sphere = tracer.Hitable_Sphere()
						hitable_sphere.setCenter(Vec3f(x / w_half, y / h_half, z / 2))
						hitable_sphere.setRadius(radius)
						hitable_sphere.setMaterial(material_1)
						scene.addHitable(hitable_sphere)

		elif aabb_level == 1:
			hitable_aabb_1: Hitable_AABB = tracer.Hitable_AABB()
			hitable_aabb_2: Hitable_AABB = tracer.Hitable_AABB()

			for z in range(-2, 2):
				for y in range(-h_half, h_half + 1):
					for x in range(-w_half, w_half + 1):

						hitable_sphere: Hitable_Sphere = tracer.Hitable_Sphere()
						hitable_sphere.setCenter(Vec3f(x / w_half, y / h_half, z / 2))
						hitable_sphere.setRadius(radius)
						hitable_sphere.setMaterial(material_1)

						if x <= 0:
							hitable_aabb_1.addHitable(hitable_sphere)
						else:
							hitable_aabb_2.addHitable(hitable_sphere)

			scene.addHitable(hitable_aabb_1)
			scene.addHitable(hitable_aabb_2)

		else:
			for z in range(-2, 2):
				for y in range(-h_half, h_half + 1):
					for x in range(-w_half, w_half + 1):

						hitable_sphere: Hitable_Sphere = tracer.Hitable_Sphere()
						hitable_sphere.setCenter(Vec3f(x / w_half, y / h_half, z / 2))
						hitable_sphere.setRadius(radius)
						hitable_sphere.setMaterial(material_1)

			aabb_1.load()
			scene.addAABB(aabb_1)

		# light
		light_point_1.setOrigin(Vec3f(1, 1, 1))
		light_point_1.setAttenuation(Vec3f(0, 0, 0.4))
		light_point_1.setColor(Vec3f(0.3))

		light_point_2.setOrigin(Vec3f(-3, 1, -4))
		light_point_2.setAttenuation(Vec3f(0, 0, 0.4))
		light_point_2.setColor(Vec3f(0.3))

		light_dir_1.setOrientation(Vec3f(-1, 1, 1))
		light_dir_1.setColor(Vec3f(0.03))

		# scene
		scene.addLight(light_point_1)
		scene.addLight(light_point_2)
		scene.addLight(light_dir_1)
