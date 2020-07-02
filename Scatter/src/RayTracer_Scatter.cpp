#include "../inc/RayTracer_Scatter.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
// TODO: add uniqueness checking
bool Scatter::addChild(Scatter *scatter) {
	scatter_list.push_back(scatter);
	return true;
}


// TODO: add uniqueness checking
// TODO: not yet completed
bool Scatter::rmChild(Scatter *scatter) {
	return false;
}


ScatterState Scatter::scatter(ScatterRecord *dst, ScatterRecord *src) const {
	ScatterState state = SCATTER_NONE;
	state = scatter_shootRay(dst, src, state);
	state = scatter_buildTree(dst, src, state);
	return state;
}


ScatterState Scatter::scatter_shootRay(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const {
	return SCATTER_NONE;
}


ScatterState Scatter::scatter_buildTree(ScatterRecord *dst, ScatterRecord *src, ScatterState state) const {
	switch (state) {
		case SCATTER_NONE:
			break;

		// build connection between scatter tree
		case SCATTER_NEXT:
		case SCATTER_EQUAL_SPLIT:
			dst->parent			= src;
			dst->scene			= src->scene;
			dst->scatter		= this;
			dst->outer			= src->outer;
			dst->depth			= src->depth - 1;
			break;

		case SCATTER_YIELD:
			break;
	};

	return state;
}


// Static Function Implementation
// ...
