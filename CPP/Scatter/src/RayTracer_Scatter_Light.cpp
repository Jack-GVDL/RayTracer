#include "../inc/RayTracer_Scatter_Light.hpp"
#include "../inc/RayTracer_Scatter_AnyHit.hpp"


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
Scatter_Light::Scatter_Light() {
	// texture
	texture_list = new Texture*[MAX];
	texture_size = MAX;

	texture_list[DIFFUSE]	= nullptr;
	texture_list[SPECULAR]	= nullptr;
	texture_list[EMISSIVE]	= nullptr;
	texture_list[AMBIENT]	= nullptr;
	texture_list[SHININESS]	= nullptr;
	texture_list[NORMAL]	= nullptr;
}


Scatter_Light::~Scatter_Light() {
}


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

	// get texture
	Vec3f	vec_emissive;
	Vec3f	vec_ambient;
	Vec3f	vec_diffuse;
	Vec3f	vec_specular;
	Vec3f	vec_shininess;
	Vec3f	vec_normal;
	Vec3f	vec_transmissive;

	texture_list[EMISSIVE]->getPixel(	vec_emissive,		record_hit->point	);
	texture_list[AMBIENT]->getPixel(	vec_ambient,		record_hit->point	);
	texture_list[DIFFUSE]->getPixel(	vec_diffuse,		record_hit->point	);
	texture_list[SPECULAR]->getPixel(	vec_specular,		record_hit->point	);
	texture_list[SHININESS]->getPixel(	vec_shininess,		record_hit->point	);
	texture_list[NORMAL]->getPixel(		vec_normal,			record_hit->point	);
	material->transmissive->getPixel(	vec_transmissive,	record_hit->point	);

	// adjust normal
	// const Vec3f normal_original	= record_hit->normal;
	record_hit->normal	+= vec_normal;
	record_hit->normal	= record_hit->normal.normalize();

	// intensity - light
	for (auto *light : scene->light_list) {

		// if the light source is behind the plane
		// then ignore
		const fp_t dot_ln = record_hit->normal.dot(light->getDirection(record_hit->point));
		if (dot_ln <= 0) continue;

		// distance attenuation
		fp_t atten_distance = light->getAttenuation(record_hit->point);
		if (atten_distance == 0) continue;

		// diffuse and specular term
		const Vec3f		&term_diffuse 	= getDiffuse(src, light, dot_ln, vec_diffuse, vec_transmissive);
		const Vec3f		&term_specular	= getSpecular(src, light, dot_ln, vec_specular, vec_shininess);
		const Vec3f		&term_result 	= term_diffuse + term_specular;

		// create new ray
		RecordRay *record = (RecordRay*)memory_control->createRecord();
		if (record == nullptr) break;

		setRecord_tree(		record, src																	);
		setRecord_ray(		record, src, Ray(record_hit->point, light->getDirection(record_hit->point))	);
		setRecord_scatter(	record, src																	);

		// ray length (from light source to object)
		record->record_hit.length_max = light->getDistance(record_hit->point);

		// thresold
		record->threshold = src->threshold * term_result * light->getColor(record_hit->point) * atten_distance;
	}

	// no need to change back the value, record should not be used again
	// change back normal
	// record_hit->normal = normal_original;

	// emissive intensity and ambient intensity
	Vec3f	intensity_result	= Vec3f();
	intensity_result	+= getEmissive(src, vec_emissive);
	intensity_result	+= getAmbient(src, vec_ambient, vec_transmissive);

	src->intensity		+= (src->threshold * intensity_result);
	src->threshold		= Vec3f(0);
}


// Static Function Implementation
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
