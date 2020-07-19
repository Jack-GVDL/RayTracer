#include "../inc/RayTracer_SceneObject_Hitable_Trimesh.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// reference
// 1. https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
bool SceneObject_Trimesh::hit(const Ray *ray, float t_min, float t_max, HitRecord *record) const {
	const Vec3f	&a	= point[0];
	const Vec3f	&b	= point[1];
	const Vec3f	&c	= point[2];

	Vec3f ray_pos	= ray->getPosition();
	Vec3f ray_dir	= ray->getDirection();

	const Vec3f &ab		= b - a;
	const Vec3f &ac		= c - a;
	Vec3f 		normal	= ab.cross(ac);

	// there exist some bad triangles such that two vertices coincide
	// i.e. become a line, which means there must be no collision
	if (normal.isZero()) return false;
	normal = normal.normalize();

	// check if the normal is need to be reversed
	// normal should be somehow oppose to the direction of incoming ray
	// TODO: find a better name for dot_temp_1
	Vec3f	n				= normal;			// backup the normal
	Vec3f	vec_pos_normal	= (a - ray_pos); 	// vector from ray position to point A
	double dot_temp_1		= vec_pos_normal.dot(normal);
	if (dot_temp_1 > 0) normal = -normal;

	// check if the ray is away from the plane
	// including ray that is perpendicular to the plane
	double dot_dir_normal = ray_dir.dot(-normal);
	if (-dot_dir_normal > RAY_EPSILON) return false;

	// find the intersection point of the ray on the plane
	// first project vec_pos_normal onto the reversed normal
	// then project ray_dir onto the reversed normal
	// it is noticed that the direction of vec_project_1 and vec_project_2 should be the same
	Vec3f	vec_project_1	= vec_pos_normal.projectOn(-normal);
	Vec3f	vec_project_2	= ray_dir.projectOn(-normal);
	double	ratio			= vec_project_1.length() / vec_project_2.length();

	Vec3f	result_ray		= ratio * ray_dir;
	Vec3f	result_point	= ray_pos + result_ray;

	// check if the intersection point is inside the triangle
	if (!VecMath::checkInside_convexPolygon(result_point, point, 3, n)) return false;

	// const Vec3f &ab		= b - a;
	// const Vec3f &bc		= c - b;
	// const Vec3f &ca		= a - c;
	// Vec3f		vec_temp_1;  // TODO find a better name for this

	// vec_temp_1 = ab.cross(result_point - a);
	// if (n.dot(vec_temp_1) < 0) return false;

	// vec_temp_1 = bc.cross(result_point - b);
	// if (n.dot(vec_temp_1) < 0) return false;

	// vec_temp_1 = ca.cross(result_point - c);
	// if (n.dot(vec_temp_1) < 0) return false;

	// configure hit record
	// but first check if is between t_min and t_max
	// TODO: find a beter name for this
	double temp = result_ray.length();
	if (temp <= t_min || temp >= t_max) return false;

	record->distance	= temp;
	record->point		= result_point;
	record->normal		= normal;
	record->object		= (SceneObject_Hitable*)this;
	return true;
}


// Static Function Implementation
// ...
