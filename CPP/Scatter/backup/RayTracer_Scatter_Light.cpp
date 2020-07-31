#include "../inc/RayTracer_Scatter_Light.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline Vec3f get_emissive	(const Material *material);
static inline Vec3f	get_ambient		(const Material *material, const Scene *scene);


// Operation Handling
ScatterState Scatter_Light::scatter_shootRay(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const {
	// first check if hit a target
	// if not hit a target, which mean the ray come from infinity (background)
	if (!src->is_hit) return SCATTER_NONE;

	// get intensity
	Vec3f intensity_result = Vec3f();

	const Vec3f		point_intersect	= src->hit_record.point;
	const Material	*material		= &(src->hit_record.object->material);
	const Scene		*scene			= src->scene;

	// intensity - emission
	intensity_result += get_emissive(material);
	
	// intensity - ambient
	intensity_result += get_ambient(material, src->scene);

	// intensity - light
	for (auto *light : scene->light_list) {
		const double dot_ln = src->hit_record.normal.dot(light->getDirection(point_intersect));

		// if the light source is behind the plane
		// then ignore it
		if (dot_ln <= 0) continue;

		// shadow attenuation
		const Vec3f &atten_shadow = light->getShadowAttenuation(src->scene, point_intersect);
		if (atten_shadow.isZero()) continue;

		// distance attenuation
		const double atten_distance = light->getDistanceAttenuation(point_intersect);
		
		// attenuation
		const Vec3f &attenuation = atten_shadow * atten_distance;

		// diffuse term
		const Vec3f &term_diffuse = (material->diffuse * dot_ln).prod(Vec3f::vec_one - material->transmissive);

		// specular term
		const Vec3f		&ray_reflect	= (2.0 * dot_ln * src->hit_record.normal - light->getDirection(point_intersect)).normalize();
		const double	dot_rv			= std::max<double>(ray_reflect.dot(-(src->ray.getDirection())), 0.0);
		const double	coeff_specular	= pow(dot_rv, material->shininess * 128);
		const Vec3f		&term_specular	= material->specular * coeff_specular;

		// diffuse term + specular term
		const Vec3f &term_result = term_diffuse + term_specular;

		// light intensity
		const Vec3f &intensity_light = light->getColor(point_intersect);

		// result += attenuation * term
		intensity_result += term_result.prod(attenuation.prod(intensity_light));
	}

	dst->intensity = intensity_result;
	return SCATTER_YIELD;
}


// Static Function Implementation
static inline Vec3f get_emissive(const Material *material) {
	return material->emissive;
}


static inline Vec3f get_ambient(const Material *material, const Scene *scene) {
	Vec3f result = Vec3f(0);
	for (auto *light : scene->ambient_list) {
		result += light->getColor(Vec3f());
	}

	// explanation to kt (transmissive)
	// some light will directly pass through the material
	// causing the intensity reduction
	// intensity remain = 1 - kt, where 0 <= kt <= 1
	//
	// (ambient_coeff * ambient_light) * (raw_one - tranmissive_coeff)
	// where * is "product" but not "dot"
	const Vec3f	temp_1	= material->ambient.prod(result.clamp(0, 1));
	const Vec3f	temp_2	= temp_1.prod(Vec3f::vec_one - material->transmissive);
	return temp_2;
}
