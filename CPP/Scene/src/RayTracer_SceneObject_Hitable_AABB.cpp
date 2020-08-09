#include <algorithm>
#include "../inc/RayTracer_SceneObject_Hitable_AABB.hpp"


// Define
// ...


// Typedef
typedef int(*compare_func_t)(const void*, const void*);


// Static Function Prototype
static int	compare_x_axis	(const void *a, const void *b);
static int	compare_y_axis	(const void *a, const void *b);
static int	compare_z_axis	(const void *a, const void *b);


// Static Data
static compare_func_t compare_func_list[] = {
	compare_x_axis,
	compare_y_axis,
	compare_z_axis
};


// Operation Handling
// aabb
Hitable_AABB* Hitable_AABB::create(
	SceneObject_Hitable* *list, int size_list, int size_leaf) {

	// create nothing if list is empty
	if (size_list == 0) {
		return nullptr;
	}

	// create leaf node if list size is smaller than max node size
	if (size_list < size_leaf) {
		Hitable_AABB *aabb = new Hitable_AABB();
		for (int i = 0; i < size_list; i++) aabb->addHitable(list[i]);
		return aabb;
	}

	// choose an axis
	// then sort list
	int index_compare = int(UtilMath::randDouble() * 3);
	qsort(list, size_list, sizeof(SceneObject_Hitable*), compare_func_list[index_compare]);

	// create aabb or aabb node
	// depend on situation
	// where if list size is smaller then max node size * 2
	// then use aabb and no need to do recursion
	Hitable_AABB		*aabb_left	= nullptr;
	Hitable_AABB		*aabb_right	= nullptr;
	Hitable_AABB		*aabb_node	= new Hitable_AABB();

	if (size_list < size_leaf * 2) {
		aabb_left	= new Hitable_AABB();
		aabb_right	= new Hitable_AABB();
		
		for (int i = 0;				i < size_list / 2;	i++)	aabb_left->addHitable(list[i]);
		for (int i = size_list / 2;	i < size_list;		i++)	aabb_right->addHitable(list[i]);

	} else {
		aabb_left	= create(list,					size_list / 2,				size_leaf);
		aabb_right	= create(list + size_list / 2,	size_list - size_list / 2,	size_leaf);

	}

	aabb_node->addHitable(aabb_left);
	aabb_node->addHitable(aabb_right);
	return aabb_node;
}


// TODO: missing uniqueness check
bool Hitable_AABB::addHitable(SceneObject_Hitable *hitable) {
	// add to list
	hitable_list.push_back(hitable);
	
	// update bounding box
	for (int i = 0; i < 3; i++) {
		bounding_min[i]	= std::min<double>(bounding_min[i], hitable->bounding_min[i]);
		bounding_max[i]	= std::max<double>(bounding_max[i], hitable->bounding_max[i]);
	}
	
	return true;
}


// TODO: not yet completed
bool Hitable_AABB::rmHitable(SceneObject_Hitable *hitable) {
	// rm from list
	// ...

	// update bounding box
	// need to go through for all child bounding box
	// ...

	return false;
}


int Hitable_AABB::getHitableSize() const {
	return hitable_list.size();
}


// only return hit child and never return self
bool Hitable_AABB::hit(RecordHit *record, double t_min, double t_max) const {
	// check if hit self bounding box
	const Vec3f	ray_pos	= record->ray.getPosition();
	const Vec3f	ray_dir	= record->ray.getDirection();

	for (int i = 0; i < 3; i++) {

		double	inv_d	= 1.0 / ray_dir[i];
		double	t0		= (bounding_min[i] - ray_pos[i]) * inv_d;
		double	t1		= (bounding_max[i] - ray_pos[i]) * inv_d;

		if (inv_d < 0.0) std::swap(t0, t1);
		double temp_min	= std::min<double>(t0, t_min);
		double temp_max	= std::max<double>(t1, t_max);

		if (temp_max <= temp_min) return false;
	}

	// check child
	RecordHit	temp_record;
	bool		is_hit			= false;
	double		closest			= t_max;

	// set ray
	temp_record.ray = record->ray;

	// search for hit in child
	for (auto *hitable : hitable_list) {
		if (!hitable->hit(&temp_record, t_min, closest)) continue;

		is_hit		= true;
		closest		= temp_record.distance;
		*record		= temp_record;
	}

	// there must be a hit
	return true;
}


// backup
// aabb node
/*
// TODO: missing uniqueness check
// TODO: not yet completed
bool Hitable_AABBNode::addHitable(SceneObject_Hitable *hitable) {
	// first check if hitable bounding box is either in left node or right node
	// if in the bounding box, then if is oversize, the need to split
	// if not in bounding box, then random add it into one of the box
	return false;
}


// TODO: not yet completed
bool Hitable_AABBNode::rmHitable(SceneObject_Hitable *hitable) {
	return false;
}


int Hitable_AABBNode::getHitableSize() const {
	return hitable_size;
}
*/


// Static Function Implementation
static int compare_x_axis(const void *a, const void *b) {
	SceneObject_Hitable *hitable_1 = *(SceneObject_Hitable**)a;
	SceneObject_Hitable *hitable_2 = *(SceneObject_Hitable**)b;

	int	mid_1	= hitable_1->bounding_min[0] + hitable_1->bounding_max[0];
	int	mid_2	= hitable_2->bounding_min[0] + hitable_2->bounding_max[0];

	// compare by mid-point of hitable
	if (mid_1 < mid_2)	return -1;
	if (mid_1 == mid_2)	return 0;
	return 1;
}


static int compare_y_axis(const void *a, const void *b) {
	SceneObject_Hitable *hitable_1 = *(SceneObject_Hitable**)a;
	SceneObject_Hitable *hitable_2 = *(SceneObject_Hitable**)b;

	int	mid_1	= hitable_1->bounding_min[1] + hitable_1->bounding_max[1];
	int	mid_2	= hitable_2->bounding_min[1] + hitable_2->bounding_max[1];

	// compare by mid-point of hitable
	if (mid_1 < mid_2)	return -1;
	if (mid_1 == mid_2)	return 0;
	return 1;
}


static int compare_z_axis(const void *a, const void *b) {
	SceneObject_Hitable *hitable_1 = *(SceneObject_Hitable**)a;
	SceneObject_Hitable *hitable_2 = *(SceneObject_Hitable**)b;

	int	mid_1	= hitable_1->bounding_min[2] + hitable_1->bounding_max[2];
	int	mid_2	= hitable_2->bounding_min[2] + hitable_2->bounding_max[2];

	// compare by mid-point of hitable
	if (mid_1 < mid_2)	return -1;
	if (mid_1 == mid_2)	return 0;
	return 1;
}
