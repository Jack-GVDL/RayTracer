#include "../inc/RayTracer_Scatter.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
ScatterState Scatter::scatter(RecordScatter *dst, RecordScatter *src) const {
	ScatterState state = SCATTER_NONE;
	state = scatter_shootRay(dst, src, state);
	// state = scatter_buildTree(dst, src, state);
	return state;
}


void Scatter::createRecord_tree(RecordScatter *dst, RecordScatter *src) const {
	// if (dst->parent == nullptr)		dst->parent		= src;
	// if (dst->scene == nullptr)		dst->scene		= src->scene;
	// if (dst->scatter == nullptr)	dst->scatter	= this;
	// if (dst->outer == nullptr)		dst->outer		= src->outer;
	// dst->depth		= src->depth - 1;

	dst->parent		= src;
	dst->scene		= src->scene;
	dst->scatter	= this;
	dst->outer		= src->outer;
	dst->depth		= src->depth - 1;
}


void Scatter::createRecord_ray(RecordScatter *dst, RecordScatter *src, const Ray &ray) const {
	dst->record_hit.ray = ray;
}


void Scatter::createRecord_threshold(RecordScatter *dst, RecordScatter *src, const Vec3f &ratio) const {
	dst->threshold	= src->threshold.prod(ratio);
	src->threshold	-= dst->threshold;
}


// Static Function Implementation
// ...
