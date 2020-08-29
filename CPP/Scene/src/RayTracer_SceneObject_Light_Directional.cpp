#include "../inc/RayTracer_SceneObject_Light_Directional.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
SceneObject_Light_Directional::SceneObject_Light_Directional() {
}


SceneObject_Light_Directional::~SceneObject_Light_Directional() {
}


void SceneObject_Light_Directional::setOrientation(const Vec3f &orientation) {
	this->orientation = orientation;
}


// TODO: backup
// fp_t SceneObject_Light_Directional::getDistanceAttenuation(const Vec3f &point) const {
// 	// distance to light is inf., so f(di) goes to 0
// 	return 1.0;
// }
// 
// 
// Vec3f SceneObject_Light_Directional::getShadowAttenuation(const Scene *scene, const Vec3f &point) const {
// 	// variable preparation
// 	const Vec3f &direction	= getDirection(point);
// 	Vec3f       point_cur	= point;
// 	Vec3f       intensity	= Vec3f(1);
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


fp_t SceneObject_Light_Directional::getAttenuation(const Vec3f &point) const {
	return 1.0;
}


fp_t SceneObject_Light_Directional::getDistance(const Vec3f &point) const {
	return std::numeric_limits<fp_t>::max();
}


Vec3f SceneObject_Light_Directional::getColor(const Vec3f &point) const {
	return color;
}


Vec3f SceneObject_Light_Directional::getDirection(const Vec3f &point) const {
	return orientation;
}


// Static Function Implementation
// ...
