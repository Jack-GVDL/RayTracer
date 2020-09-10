#include <algorithm>
#include "../inc/RayTracer_SceneObject_Hitable_AABB.hpp"


// Define
// ...


// Typedef
typedef int32_t(*compare_func_t)(const void*, const void*);


// Static Function Prototype
static int32_t	compare_x_axis	(const void *a, const void *b);
static int32_t	compare_y_axis	(const void *a, const void *b);
static int32_t	compare_z_axis	(const void *a, const void *b);


// Static Data
static compare_func_t compare_func_list[] = {
	compare_x_axis,
	compare_y_axis,
	compare_z_axis
};


// Operation Handling
Hitable_AABB::Hitable_AABB() {
}


Hitable_AABB::~Hitable_AABB() {
}


Hitable_AABB* Hitable_AABB::create(
	SceneObject_Hitable* *list, int32_t size_list, int32_t size_leaf) {

	// create nothing if list is empty
	if (size_list == 0) {
		return nullptr;
	}

	// create leaf node if list size is smaller than max node size
	if (size_list < size_leaf) {
		Hitable_AABB *aabb = new Hitable_AABB();
		for (int32_t i = 0; i < size_list; ++i) aabb->addHitable(list[i]);
		return aabb;
	}

	// choose an axis
	// then sort list
	int32_t index_compare = int32_t(UtilMath::randFloat() * 3);
	qsort(list, size_list, sizeof(SceneObject_Hitable*), compare_func_list[index_compare]);

	// create aabb or aabb node
	// depend on situation
	// where if list size is smaller then max node size * 2
	// then use aabb and no need to do recursion
	Hitable_AABB		*aabb_left	= nullptr;
	Hitable_AABB		*aabb_right	= nullptr;
	Hitable_AABB		*aabb_node	= new Hitable_AABB();

	if (size_list <= size_leaf * 2) {
		aabb_left	= new Hitable_AABB();
		aabb_right	= new Hitable_AABB();

		for (int32_t i = 0;				i < size_list / 2;	++i)	aabb_left->addHitable(list[i]);
		for (int32_t i = size_list / 2;	i < size_list;		++i)	aabb_right->addHitable(list[i]);

	} else {
		aabb_left	= create(list,					size_list / 2,				size_leaf);
		aabb_right	= create(list + size_list / 2,	size_list - size_list / 2,	size_leaf);

	}

	aabb_node->addHitable(aabb_left);
	aabb_node->addHitable(aabb_right);
	return aabb_node;
}


// TODO: missing uniqueness check
int8_t Hitable_AABB::addHitable(SceneObject_Hitable *hitable) {
	hitable_list.push_back(hitable);
	bounding.unionBounding(hitable->bounding);
	return ERROR_NO;
}


// TODO: not yet completed
error_t Hitable_AABB::rmHitable(SceneObject_Hitable *hitable) {
	// rm from list
	// ...

	// update bounding box
	// need to go through for all child bounding box
	// ...

	return ERROR_ANY;
}


uint32_t Hitable_AABB::getHitableSize() const {
	return hitable_list.size();
}


// only return hit child and never return self
bool Hitable_AABB::hit(RecordHit *record, fp_t t_min, fp_t t_max) const {
	// check if box is empty or not
	// TODO: test
	if (bounding.isEmpty()) return false;

	// check if hit self bounding box
	// TODO: modularization
	const Vec3f	ray_pos	= record->ray.getPosition();
	const Vec3f	ray_dir	= record->ray.getDirection();

	for (uint8_t i = 0; i < 3; i++) {

		fp_t	inv_d	= 1.0 / ray_dir[i];
		fp_t	t0		= (bounding.min[i] - ray_pos[i]) * inv_d;
		fp_t	t1		= (bounding.max[i] - ray_pos[i]) * inv_d;

		if (inv_d < 0.0) std::swap(t0, t1);

		t_min	= std::max<fp_t>(t0, t_min);
		t_max	= std::min<fp_t>(t1, t_max);

		if (t_max <= t_min) return false;
	}

	// check child
	RecordHit	temp_record;
	bool		is_hit			= false;
	fp_t		closest			= t_max;

	// set ray
	temp_record.ray = record->ray;

	// search for hit in child
	for (SceneObject_Hitable* hitable : hitable_list) {
		if (!hitable->hit(&temp_record, t_min, closest)) continue;

		is_hit		= true;
		closest		= temp_record.distance;
		*record		= temp_record;
	}

	// cannot return true
	// hit bounding does not mean it must hit a hitable in the bounding
	return is_hit;
}


// backup
// aabb node
/*
// TODO: missing uniqueness check
// TODO: not yet completed
bool Hitable_AABBNode::addHitable(SceneObject_Hitable *hitable) {
	// first check if hitable bounding box is either in left node or right node
	// if in the bounding box, then if is oversize, the need to split
	// if not in bounding box, then random add it int32_to one of the box
	return false;
}


// TODO: not yet completed
bool Hitable_AABBNode::rmHitable(SceneObject_Hitable *hitable) {
	return false;
}


int32_t Hitable_AABBNode::getHitableSize() const {
	return hitable_size;
}
*/


// Static Function Implementation
static int32_t compare_x_axis(const void *a, const void *b) {
	SceneObject_Hitable *hitable_1 = *(SceneObject_Hitable**)a;
	SceneObject_Hitable *hitable_2 = *(SceneObject_Hitable**)b;

	int32_t	mid_1	= hitable_1->bounding.min[0] + hitable_1->bounding.max[0];
	int32_t	mid_2	= hitable_2->bounding.min[0] + hitable_2->bounding.max[0];

	// compare by mid-point32_t of hitable
	if (mid_1 < mid_2)	return -1;
	if (mid_1 == mid_2)	return 0;
	return 1;
}


static int32_t compare_y_axis(const void *a, const void *b) {
	SceneObject_Hitable *hitable_1 = *(SceneObject_Hitable**)a;
	SceneObject_Hitable *hitable_2 = *(SceneObject_Hitable**)b;

	int32_t	mid_1	= hitable_1->bounding.min[1] + hitable_1->bounding.max[1];
	int32_t	mid_2	= hitable_2->bounding.min[1] + hitable_2->bounding.max[1];

	// compare by mid-point32_t of hitable
	if (mid_1 < mid_2)	return -1;
	if (mid_1 == mid_2)	return 0;
	return 1;
}


static int32_t compare_z_axis(const void *a, const void *b) {
	SceneObject_Hitable *hitable_1 = *(SceneObject_Hitable**)a;
	SceneObject_Hitable *hitable_2 = *(SceneObject_Hitable**)b;

	int32_t	mid_1	= hitable_1->bounding.min[2] + hitable_1->bounding.max[2];
	int32_t	mid_2	= hitable_2->bounding.min[2] + hitable_2->bounding.max[2];

	// compare by mid-point32_t of hitable
	if (mid_1 < mid_2)	return -1;
	if (mid_1 == mid_2)	return 0;
	return 1;
}
