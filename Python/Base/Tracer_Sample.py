from .Tracer_Texture import *
from .Tracer_Scatter import *
from .Tracer_Hitable import *
from .Tracer_Light import *
from .Tracer_Camera import *
from .Tracer_Scene import Scene


class Tracer_Sample:

	@ classmethod
	def buildScene_0(cls, scene: Scene) -> None:
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
		hitable_sphere_1:	Hitable_Sphere = Hitable_Sphere()
		hitable_sphere_1.setCenter(Vec3f(0, 0, 0))
		hitable_sphere_1.setRadius(0.5)
		hitable_sphere_1.addScatter(scatter_light_1)

		# light
		light_point_1:			Light_Point = Light_Point()
		light_point_1.setOrigin(Vec3f(1, 1, 1))
		light_point_1.setColor(Vec3f(1))

		# scene
		scene.addHitable(hitable_sphere_1)
		scene.addLight(light_point_1)

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
