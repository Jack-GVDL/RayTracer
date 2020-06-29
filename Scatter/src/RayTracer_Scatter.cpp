#include "../inc/RayTracer_Scatter.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
ScatterState Scatter::scatter(ScatterRecord *dst, ScatterRecord *src) const {
	if (src->depth <= 0) return SCATTER_NONE;

	// interface
	ScatterState status = _scatter_(dst, src);

	switch (status) {
		case SCATTER_NONE:
			break;

		// build connection between scatter tree
		case SCATTER_NEXT:
			dst->parent = src;
			break;

		case SCATTER_YIELD:
			break;
	};

	return status;
}


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


// Static Function Implementation
// ...
