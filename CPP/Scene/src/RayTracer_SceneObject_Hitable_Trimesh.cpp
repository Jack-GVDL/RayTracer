#include "../inc/RayTracer_SceneObject_Hitable_Trimesh.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// hitable
void Hitable_Trimesh::setPoint(const Vec3f &p0, const Vec3f &p1, const Vec3f &p2) {
	this->point[0]	= p0;
	this->point[1]	= p1;
	this->point[2]	= p2;

	updateBoundingBox();
}


// reference
// 1. https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
bool Hitable_Trimesh::hit(RecordHit *record, double t_min, double t_max) const {
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


void Hitable_Trimesh::updateBoundingBox() {
	// point 0
	bounding_min = point[0];
	bounding_max = point[0];

	// point 1
	for (int i = 0; i < 3; i++) {
		bounding_min[i]	= std::min<double>(bounding_min[i], point[1][i]);
		bounding_max[i]	= std::max<double>(bounding_max[i], point[1][i]);
	}

	// point 2
	for (int i = 0; i < 3; i++) {
		bounding_min[i]	= std::min<double>(bounding_min[i], point[2][i]);
		bounding_max[i]	= std::max<double>(bounding_max[i], point[2][i]);
	}
}


// mapper
// TODO: backup
// void Mapper_Trimesh::setTrimesh(Hitable_Trimesh *trimesh) {
// 	this->trimesh = trimesh;
// }


// void Mapper_Trimesh::map(Vec3f &vector) const {
// 	if (trimesh == nullptr) return;

// 	// get 2d axis
// 	// one should be ac
// 	// one should be cross product of normal and ab
// 	Vec3f axis_1	= trimesh->point[1] - trimesh->point[0];
// 	Vec3f ac		= trimesh->point[2] - trimesh->point[0];
// 	Vec3f normal	= axis_1.cross(ac);
// 	Vec3f axis_2	= normal.cross(axis_1);

// 	axis_1	= axis_1.normalize();
// 	axis_2	= axis_2.normalize();

// 	// get projection length on the two axis
// 	// then map vector on a 2d plane
// 	// axis_1 as x
// 	// axis_2 as y
// 	double length_x = vector.projectLength(axis_1);
// 	double length_y = vector.projectLength(axis_2);
	
// 	vector[0] = length_x;
// 	vector[1] = length_y;
// 	vector[2] = 0;
// }


// texture - mapper
void Texture_Mapper_Trimesh::setTrimesh(Hitable_Trimesh *trimesh) {
	this->trimesh = trimesh;
}


void Texture_Mapper_Trimesh::setPixel(const Vec3f &point, const Vec3f &pixel) {

}


void Texture_Mapper_Trimesh::_getPixel_(Vec3f &dst, std::vector<Vec3f> *src) const {
	if (trimesh == nullptr) return;

	// get 2d axis
	// one should be ac
	// one should be cross product of normal and ab
	Vec3f axis_1	= trimesh->point[1] - trimesh->point[0];
	Vec3f ac		= trimesh->point[2] - trimesh->point[0];
	Vec3f normal	= axis_1.cross(ac);
	Vec3f axis_2	= normal.cross(axis_1);

	axis_1	= axis_1.normalize();
	axis_2	= axis_2.normalize();

	// get projection length on the two axis
	// then map vector on a 2d plane
	// axis_1 as x
	// axis_2 as y
	double length_x = (*src)[0].projectLength(axis_1);
	double length_y = (*src)[0].projectLength(axis_2);
	
	dst[0] = length_x;
	dst[1] = length_y;
	dst[2] = 0;
}


// TODO: backup
// void Texture_Mapper_Trimesh::_getPixel_(Vec3f &dst, const Vec3f &src) const {
// 	if (trimesh == nullptr) return;

// 	// get 2d axis
// 	// one should be ac
// 	// one should be cross product of normal and ab
// 	Vec3f axis_1	= trimesh->point[1] - trimesh->point[0];
// 	Vec3f ac		= trimesh->point[2] - trimesh->point[0];
// 	Vec3f normal	= axis_1.cross(ac);
// 	Vec3f axis_2	= normal.cross(axis_1);

// 	axis_1	= axis_1.normalize();
// 	axis_2	= axis_2.normalize();

// 	// get projection length on the two axis
// 	// then map vector on a 2d plane
// 	// axis_1 as x
// 	// axis_2 as y
// 	double length_x = src.projectLength(axis_1);
// 	double length_y = src.projectLength(axis_2);
	
// 	dst[0] = length_x;
// 	dst[1] = length_y;
// 	dst[2] = 0;
// }


// texture - direction
void Texture_Direction_Trimesh::setTrimesh(Hitable_Trimesh *trimesh) {
	this->trimesh = trimesh;
}


void Texture_Direction_Trimesh::setPixel(const Vec3f &point, const Vec3f &pixel) {

}


// TODO: not yet completed
void Texture_Direction_Trimesh::_getPixel_(Vec3f &dst, std::vector<Vec3f> *src) const {
	if (trimesh == nullptr) return;
}


// Static Function Implementation
// ...
