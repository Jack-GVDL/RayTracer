#include "../inc/RayTracer_SceneObject_Hitable_Trimesh.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// hitable
Hitable_Trimesh::Hitable_Trimesh() {
	point[0]	= Vec3f(0);
	point[1]	= Vec3f(0);
	point[2]	= Vec3f(0);

	updateBoundingBox();
}


Hitable_Trimesh::~Hitable_Trimesh() {
}


void Hitable_Trimesh::setPoint(const Vec3f &p0, const Vec3f &p1, const Vec3f &p2) {
	this->point[0]	= p0;
	this->point[1]	= p1;
	this->point[2]	= p2;

	updateBoundingBox();
}


// reference
// 1. https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
bool Hitable_Trimesh::hit(RecordHit *record, fp_t t_min, fp_t t_max) const {
	const Vec3f	&a		= point[0];
	const Vec3f	&b		= point[1];
	const Vec3f	&c		= point[2];

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

	// get point32_t of intersection
	Vec3f	result_point;
	fp_t	result_length;
	Ray		plane			= Ray(a, normal);
	if (!VecMath::intersectPoint_rayPlane(result_point, result_length, ray, &plane)) return false;

	// check if the intersection point32_t is inside the triangle
	if (!VecMath::checkInside_convexPolygon(result_point, point, 3, normal)) return false;

	// configure hit record
	// but first check if is between t_min and t_max
	// fp_t ray_length = result_ray.length();  
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
	bounding.setEmpty();
	bounding.unionBounding(point[0]);
	bounding.unionBounding(point[1]);
	bounding.unionBounding(point[2]);
	
	// if plane is along axis, then the bounding have no thickness
	// give the bounding some thickness
	for (uint8_t i = 0; i < 3; ++i) {
		if (bounding.min[i] != bounding.max[i]) continue;
		bounding.min[i] -= RAY_EPSILON;
		bounding.max[i] += RAY_EPSILON;
	}
}


// texture - mapper
void Texture_Mapper_Trimesh::setTrimesh(Hitable_Trimesh *trimesh) {
	this->trimesh = trimesh;
}


void Texture_Mapper_Trimesh::setPixel(const Vec3f &point, const Vec3f &pixel) {

}


void Texture_Mapper_Trimesh::_getPixel_(Vec3f &dst, Vec3f *src) const {
	if (trimesh == nullptr) {
		dst = Vec3f();
		return;
	}

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
	fp_t	length_x = (src[0]).projectLength(axis_1);
	fp_t	length_y = (src[0]).projectLength(axis_2);
	
	dst[0] = length_x;
	dst[1] = length_y;
	dst[2] = 0;
}


// texture - direction
void Texture_Direction_Trimesh::setTrimesh(Hitable_Trimesh *trimesh) {
	this->trimesh = trimesh;
}


void Texture_Direction_Trimesh::setPixel(const Vec3f &point, const Vec3f &pixel) {

}


// TODO: not yet completed
void Texture_Direction_Trimesh::_getPixel_(Vec3f &dst, Vec3f *src) const {
	if (trimesh == nullptr) {
		dst = Vec3f();
		return;
	}
}


// Static Function Implementation
// ...
