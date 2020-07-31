#include <limits>
#include "../inc/RayTracer_Tracer.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
// ...


// Operation Handling
Vec3f RayTracer::trace(const Camera *camera, double x, double y, int depth) const {
	Ray ray = camera->getRay(x, y);
	return trace(&ray, depth);
}


Vec3f RayTracer::trace(const Ray *ray, int depth) const {
	// init scatter record
	RecordScatter scatter_record;
	scatter_record.parent		= nullptr;
	scatter_record.scene		= scene;
	scatter_record.scatter		= nullptr;
	scatter_record.depth		= depth;

	scatter_record.record_hit.ray = *ray;

	// TODO: use cuda in future
	return trace(&scatter_record);
}


// TODO: return nothing is still ok, as the result is already in the ScatterRecord *record
Vec3f RayTracer::trace(RecordScatter *record) const {
	// depth limit check
	if (record->depth <= 0) return Vec3f();

	// first check if hit something or nothing
	// if hit, then use hit shader
	// else, use not hit shader
	record->is_hit = scene->hit(&(record->record_hit));

	const Shader *shader;
	if (record->is_hit) {
		const SceneObject_Hitable *object = record->record_hit.object;
		shader = &(object->shader);
		// if (object->shader == nullptr)	shader = &shader_hit;
		// else							shader = object->shader;

	} else {
		shader = &shader_not_hit;

	}

	// reset intensity
	record->intensity = Vec3f();

	// foreach scatter, check if needed to fire a new ray or not
	for (auto *scatter : shader->scatter_list) {

		// check if there is no threshold left for parent
		if (record->threshold.isZero()) break;

		RecordScatter	scatter_record;
		ScatterState	state = scatter->scatter(&scatter_record, record);

		// nothing to deal with current scatter
		// skip it
		if (state == SCATTER_NONE) {
			continue;
		}

		// add result intensity to parent intensity immediate
		if (state == SCATTER_YIELD) {
			const Vec3f &result = scatter_record.intensity.clamp(0, 1);
			record->intensity	+= result * record->threshold;
			break;
		}

		// TODO: not yet completed
		if (state == SCATTER_SPLIT) {
			break;
		}

		// if (state == SCATTER_NEXT)
		// fire a new ray and obtain the result
		const Vec3f &result	= trace(&scatter_record).clamp(0, 1);
		record->intensity	+= result;

	}

	return record->intensity;
}


// Static Function Implementation
// ...
