#include "../inc/RayTracer_DynamicContainer.cuh"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
// container
__host__ int Dynamic_ContainerBase::getIndex() {
	return index;
}


// container list
// TODO: need uniqueness check
__host__ int Dynamic_ContainerListBase::_Type_load_() {
	// insert current type into hash map
	for (int i = 0; i < type_list.size(); i++) {
		const Dynamic_ContainerType *type = type_list[i];
		name_map.insert(std::pair<std::string, int>(type->name, i));
	}

	return 0;
}


__host__ int Dynamic_ContainerListBase::_Type_dump_() {
	name_map.clear();
	return 0;
}


__host__ int Dynamic_ContainerListBase::_Type_indexOf_(std::string name) {
	std::unordered_map<std::string, int>::iterator iterator;
	iterator = name_map.find(name);
	if (iterator == name_map.end()) return -1;
	
	return iterator->second;
}


__host__ Dynamic_ContainerBase* Dynamic_ContainerListBase::_create_(int type) {
	if (type < 0 || type >= type_list.size()) return nullptr;

	void *o = type_list[type]->ops_init();
	if (o == nullptr) return nullptr;

	Dynamic_ContainerBase *container = new Dynamic_ContainerBase(object_index);
	object_index++;

	container->object	= o;
	container->type		= type;

	container_list.push_back(container);
	return container;
}


__host__ int Dynamic_ContainerListBase::_destroy_(int index) {
	if (container_list.size() == 0) return -1;

	// check if target container exist or not
	int index_target = _indexOf_(index);
	if (index_target == -1) return -1;

	// move target container to end of list
	Dynamic_ContainerBase *target = container_list[index_target];
	Dynamic_ContainerBase *temp;
	for (int i = index_target; i < container_list.size() - 2; i++) {
		temp					= container_list[i];
		container_list[i]		= container_list[i + 1];
		container_list[i + 1]	= container_list[i];
	}

	// call pop_back to remove container
	container_list.pop_back();

	// delete item
	delete target;
	return 0;

}


__host__ Dynamic_ContainerBase* Dynamic_ContainerListBase::_get_(int index) {
	int index_target = _indexOf_(index);

	if (index_target == -1) return nullptr;
	return container_list[index_target];
}


__host__ int Dynamic_ContainerListBase::_config_(int index, int type, uint8_t *data, uint32_t size) {
	Dynamic_ContainerBase *container = _get_(index);
	if (container == nullptr) return -1;

	int container_type = container->type;
	if (container_type < 0 || container_type >= type_list.size()) return -1;

	type_list[container_type]->ops_config(container->object, type, data, size);
	return 0;
}


__host__ int Dynamic_ContainerListBase::_interact_(int index, int type, Dynamic_ContainerBase* *list, uint32_t size) {
	Dynamic_ContainerBase *container = _get_(index);
	if (container == nullptr) return -1;

	int container_type = container->type;
	if (container_type < 0 || container_type >= type_list.size()) return -1;

	// TODO: currently number is fixed
	void* temp_list[8] = {0};
	for (int i = 0; i < size; i++) temp_list[i] = list[i]->object;

	type_list[container_type]->ops_interact(container->object, type, temp_list, size);
	return 0;
}


__host__ int Dynamic_ContainerListBase::_size_() {
	return (int)(container_list.size());
}


__host__ int Dynamic_ContainerListBase::_indexOf_(int index) {
	// binary search
	// list is ordered by index number of container
	// binary search is able to use
	int		index_min	= 0;
	int		index_max	= container_list.size() - 1;
	int		index_middle;
	int		index_cur;

	// should use <= instead of ==
	while (index_min <= index_max) {

		index_middle	= (index_min + index_max) / 2;
		index_cur		= container_list[index_middle]->getIndex();

		// if size of list is very large
		// chance of index_cur == index is low
		// so better let this condition (index_cur == index) to pass two branch (index_cur < index) and (index_cur > index)
		// chance of index_cur < index and index_cur > index will be very the same
		if (index < index_cur) {
			index_max = index_middle - 1;
			continue;
		} else if (index > index_cur) {
			index_min = index_middle + 1;
			continue;
		}

		return index_middle;
	}

	return -1;

	// backup
	// linear search
	// int index_target = 0;
	//
	// for (auto *container : container_list) {
	// 	if (container->getIndex() != index) {
	// 		index_target++;
	// 		continue;
	// 	}
	//
	// 	return index_target;
	// }
	// return -1;

}


// Static Function Implementation
// ...
