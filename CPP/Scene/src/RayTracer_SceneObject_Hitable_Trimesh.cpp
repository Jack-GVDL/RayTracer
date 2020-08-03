#include "../inc/RayTracer_SceneObject_Hitable_Trimesh.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
void SceneObject_Trimesh::setPoint(const Vec3f &p0, const Vec3f &p1, const Vec3f &p2) {
	this->point[0]	= p0;
	this->point[1]	= p1;
	this->point[2]	= p2;
}


// reference
// 1. https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
bool SceneObject_Trimesh::hit(RecordHit *record, double t_min, double t_max) const {
	const Vec3f	&a	= point[0];
	const Vec3f	&b	= point[1];
	const Vec3f	&c	= point[2];

	const Ray	*ray	= &(record->ray);
	Vec3f		ray_pos	= ray->getPosition();
	Vec3f		ray_dir	= ray->getDirection();

	const Vec3f &ab		= b - a;
	const Vec3f &ac		= c - a;
	Vec3f 		normal	= ab.cross(ac);

	// there exist some bad triangles such that two vertices coincide
	// i.e. become a line, which means there must be no collision
	if (normal.isZero()) return false;
	normal = normal.normalize();

	// get point of intersection
	Vec3f	result_point;
	double	result_length;
	Ray		plane			= Ray(a, normal);
	if (!VecMath::intersectPoint_rayPlane(result_point, result_length, ray, &plane)) return false;

	// check if the intersection point is inside the triangle
	if (!VecMath::checkInside_convexPolygon(result_point, point, 3, normal)) return false;

	// configure hit record
	// but first check if is between t_min and t_max
	// double ray_length = result_ray.length();  
	if (result_length <= t_min || result_length >= t_max) return false;

	record->distance	= result_length;
	record->point		= result_point;
	record->normal		= normal;
	record->object		= (SceneObject_Hitable*)this;

	// adjust normal
	VecMath::reverseNormal_incidentRay(record->normal, ray->getDirection());
	
	return true;
}


// Static Function Implementation
// ...
