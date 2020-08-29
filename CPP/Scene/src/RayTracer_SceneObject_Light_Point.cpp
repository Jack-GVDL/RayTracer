#include "../inc/RayTracer_SceneObject_Light_Point.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
SceneObject_Light_Point::SceneObject_Light_Point() {
}


SceneObject_Light_Point::~SceneObject_Light_Point() {
}


void SceneObject_Light_Point::setAttenuation(const Vec3f &coeff) {
	this->attenuation = coeff;
}


// TODO: backup
// fp_t  SceneObject_Light_Point::getDistanceAttenuation(const Vec3f &point) const {
// 	const fp_t		coeff_1	= attenuation_coeff[0];
// 	const fp_t		coeff_2	= attenuation_coeff[1];
// 	const fp_t		coeff_3	= attenuation_coeff[2];
// 
// 	const fp_t		d2		= (point - origin).lengthSquared();
// 	const fp_t		d1		= sqrt(d2);
// 	const fp_t		result	= coeff_1 + coeff_2 * d1 + coeff_3 * d2;
// 
// 	// do no divide by zero
// 	return result == 0 ? 1 : std::min<fp_t>(1 / result, 1);
// }
// 
// 
// Vec3f SceneObject_Light_Point::getShadowAttenuation(const Scene *scene, const Vec3f &point) const {
// 	// variable preparation
// 	const Vec3f &direction	= getDirection(point);
// 	Vec3f		point_cur	= point;
// 	Vec3f		intensity	= Vec3f(1);
// 
// 	// TODO: should move this part to scatter
// 	// first push the ray a little bit forward to prevent hit the same point
// 	point_cur = point_cur + direction * RAY_EPSILON;
// 	while (!intensity.isZero()) {
// 
// 		// check if no intersection or intersection is behind the light source
// 		RecordHit_Extend	record;
// 		RecordHit			*record_hit		= &(record.record);
// 		const fp_t			length_light	= (origin - point_cur).length();
// 		record_hit->ray						= Ray(point_cur, direction);
// 
// 		if (!scene->hit(&record))					return intensity;
// 		if (record_hit->distance >= length_light)	return intensity;
// 
// 		// new intensity *= transmissive
// 		const Material *material = &(record_hit->object->material);
// 
// 		Vec3f vec_transmissive;
// 		material->transmissive->getPixel(vec_transmissive, record_hit->point);
// 
// 		intensity *= vec_transmissive;
// 
// 		// push the ray froward a little bit
// 		point_cur = record_hit->point + direction * RAY_EPSILON;
// 
// 	}
// 
// 	return intensity;
// }


fp_t SceneObject_Light_Point::getAttenuation(const Vec3f &point) const {
	const fp_t		coeff_1	= attenuation[0];
	const fp_t		coeff_2	= attenuation[1];
	const fp_t		coeff_3	= attenuation[2];

	const fp_t		d2		= (point - origin).lengthSquared();
	const fp_t		d1		= sqrt(d2);
	const fp_t		result	= coeff_1 + coeff_2 * d1 + coeff_3 * d2;

	// do not divide by zero
	return result == 0 ? 1 : std::min<fp_t>(1 / result, 1);
}


fp_t SceneObject_Light_Point::getDistance(const Vec3f &point) const {
	return (origin - point).length();
}


Vec3f SceneObject_Light_Point::getColor(const Vec3f &point) const {
	return color;
}


Vec3f SceneObject_Light_Point::getDirection(const Vec3f &point) const {
	return (origin - point).normalize();
}


// Static Function Implementation
// ...
