#include "../inc/RayTracer_Scatter_Light.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline Vec3f	getEmissive	(const RecordRay *record, const Vec3f &vec_emissive);
static inline Vec3f	getAmbient	(const RecordRay *record, const Vec3f &vec_ambient, const Vec3f &vec_transmissive);
static inline Vec3f	getDiffuse	(const RecordRay *record, const SceneObject_Light *light, fp_t dot_ln, const Vec3f &vec_diffuse, const Vec3f &vec_transmissive);
static inline Vec3f	getSpecular	(const RecordRay *record, const SceneObject_Light *light, fp_t dot_ln, const Vec3f &vec_specular, const Vec3f &vec_shininess);


// Operation Handling
void Scatter_Light::scatter(RecordRay *src, MemoryControl_Scatter *memory_control) const {
	// first check if hit a target
	// if not hit a target, which mean the ray come from infinity (background)
	if (!src->is_hit) {
		src->threshold = Vec3f(0);
		return;
	}

	// variable prepartion
	const Scene		*scene		= src->scene;
	RecordHit		*record_hit	= &(src->record_hit.record);
	Material		*material	= &(record_hit->object->material);

	// get intensity
	Vec3f	intensity_result	= Vec3f();

	// get coeff
	Vec3f	vec_emissive;
	Vec3f	vec_ambient;
	Vec3f	vec_diffuse;
	Vec3f	vec_specular;
	Vec3f	vec_shininess;
	Vec3f	vec_normal;
	Vec3f	vec_transmissive;

	texture_list[EMISSIVE]->getPixel(		vec_emissive,		record_hit->point);
	texture_list[AMBIENT]->getPixel(		vec_ambient,		record_hit->point);
	texture_list[DIFFUSE]->getPixel(		vec_diffuse,		record_hit->point);
	texture_list[SPECULAR]->getPixel(		vec_specular,		record_hit->point);
	texture_list[SHININESS]->getPixel(		vec_shininess,		record_hit->point);
	texture_list[NORMAL]->getPixel(			vec_normal,			record_hit->point);
	material->transmissive->getPixel(		vec_transmissive,	record_hit->point);

	// emissive intensity and ambient intensity
	intensity_result += getEmissive(src, vec_emissive);
	intensity_result += getAmbient(src, vec_ambient, vec_transmissive);

	// TODO: may need better way to do the same thing
	// adjust normal
	const Vec3f normal_original	= record_hit->normal;
	record_hit->normal			+= vec_normal;
	record_hit->normal			= record_hit->normal.normalize();

	// intensity - light
	for (auto *light : scene->light_list) {
		// if the light source is behind the plane
		// then ignore it
		const fp_t		dot_ln 			= record_hit->normal.dot(light->getDirection(record_hit->point));
		if (dot_ln <= 0) continue;

		// attenuation
		const Vec3f		&atten_shadow 	= light->getShadowAttenuation(src->scene, record_hit->point);
		if (atten_shadow.isZero()) continue;

		const fp_t		atten_distance 	= light->getDistanceAttenuation(record_hit->point);
		const Vec3f		&attenuation 	= atten_shadow * atten_distance;

		// diffuse term and specular term
		const Vec3f		&term_diffuse 	= getDiffuse(src, light, dot_ln, vec_diffuse, vec_transmissive);
		const Vec3f		&term_specular	= getSpecular(src, light, dot_ln, vec_specular, vec_shininess);
		const Vec3f		&term_result 	= term_diffuse + term_specular;

		// result += attenuation * term
		const Vec3f &intensity_light = light->getColor(record_hit->point);
		intensity_result += term_result.prod(attenuation.prod(intensity_light));
	}

	// TODO: may need better way to do the same thing
	// change back normal
	record_hit->normal = normal_original;

	src->intensity	+= (src->threshold * intensity_result);
	src->threshold	= Vec3f(0);
}


static inline Vec3f getEmissive(const RecordRay *record, const Vec3f &vec_emissive) {
	return vec_emissive;
}


// explanation to kt (transmissive)
// some light will directly pass through the material
// causing the intensity reduction
// intensity remain = 1 - kt, where 0 <= kt <= 1
//
// (ambient_coeff * ambient_light) * (raw_one - tranmissive_coeff)
// where * is "product" but not "dot"
static inline Vec3f getAmbient(const RecordRay *record, const Vec3f &vec_ambient, const Vec3f &vec_transmissive) {
	// variable preparation
	const RecordHit	*record_hit	= &(record->record_hit.record);
	const Material 	*material	= &(record_hit->object->material);

	// get amibent intensity
	Vec3f intensity_ambient		= record->scene->getAmbientIntensity();
	intensity_ambient			= intensity_ambient.clamp(0, 1);

	const Vec3f	temp_1	= intensity_ambient.prod(vec_ambient);
	const Vec3f	temp_2	= temp_1.prod(Vec3f::vec_one - vec_transmissive);
	return temp_2;
}


static inline Vec3f getDiffuse(const RecordRay *record, const SceneObject_Light *light, fp_t dot_ln, const Vec3f &vec_diffuse, const Vec3f &vec_transmissive) {
	// variable preparation
	const RecordHit	*record_hit	= &(record->record_hit.record);
	const Material 	*material	= &(record_hit->object->material);

	return (vec_diffuse * dot_ln).prod(Vec3f::vec_one - vec_transmissive);
}


static inline Vec3f getSpecular(const RecordRay *record, const SceneObject_Light *light, fp_t dot_ln, const Vec3f &vec_specular, const Vec3f &vec_shininess) {
	// variable preparation
	const RecordHit	*record_hit	= &(record->record_hit.record);
	const Material 	*material	= &(record_hit->object->material);

	// get reflected light
	// then get dot_rv
	const Vec3f		ray_reflect	= (2.0 * dot_ln * record_hit->normal - light->getDirection(record_hit->point)).normalize(); 
	const fp_t		dot_rv		= std::max<fp_t>(ray_reflect.dot(-(record_hit->ray.getDirection())), 0.0);

	// get specular term
	const fp_t coeff_specular = pow(dot_rv, vec_shininess[0] * 128);
	return vec_specular * coeff_specular;
}


// Static Function Implementation
// ...
