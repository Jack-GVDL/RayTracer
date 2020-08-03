// Created by Jack Tse on 2020/07/29
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/29   initial update


#ifndef RAYTRACER_DYNAMICCONTAINER_HPP
#define RAYTRACER_DYNAMICCONTAINER_HPP


#include <vector>
#include <stdint.h>


// Define
// ...


// Typedef
typedef void*(*init_func_t)();
typedef int(*config_func_t)(void*, int, uint8_t*, uint32_t);


// Enum
// ...


// Data Structure
// ...


// Data Structure
template <class T>
class Dynamic_Container {
	// Data
	protected:
		static int	global_index;
		int			index;
		
	public:
		int			type;
		T			*object;

	// Operation
	public:
		Dynamic_Container() {
			// so first valid index is 1 instead of 0
			// 0 is considered as nullptr or ERROR_NO
			// therefore, it should better not be a valid index
			index = global_index;
			global_index++;
		}

		int getIndex() {
			return index;
		}
};


template <class T>
class Dynamic_ContainerList {
	// Data
	public:
		std::vector<Dynamic_Container<T>*>	container_list;
		std::vector<init_func_t>			init_list;
		std::vector<config_func_t>			config_list;

	// Operation
	public:
		Dynamic_Container<T>*	create	(int type);
		int						destroy	(int index);
        Dynamic_Container<T>*	get		(int index);
		int						config	(int index, int type, uint8_t *data, uint32_t size);
		int						size	();
};


// Macro Function
// ...


// Operation Handling
template <class T>
Dynamic_Container<T>* Dynamic_ContainerList<T>::create(int type) {
	if (type < 0 || type >= init_list.size()) return nullptr;
	T *surface = (T*)(init_list[type]());

	Dynamic_Container<T> *container = new Dynamic_Container<T>();
	container->object	= surface;
	container->type		= type;

	container_list.push_back(container);
	return container;
}


// TODO: not yet completed
template <class T>
int Dynamic_ContainerList<T>::destroy(int index) {
	return -1;
}


// TODO: use binary search
template <class T>
Dynamic_Container<T>* Dynamic_ContainerList<T>::get(int index) {
	for (auto *container : container_list) {
		if (container->getIndex() != index) continue;
		return container;
	}
	return nullptr;
}


template <class T>
int Dynamic_ContainerList<T>::config(int index, int type, uint8_t *data, uint32_t size) {
	Dynamic_Container<T> *container = get(index);

	int container_type = container->type;
	if (container_type < 0 || container_type >= config_list.size()) return -1;

	config_list[container_type](container->object, type, data, size);
	return 0;
}


template <class T>
int Dynamic_ContainerList<T>::size() {
	return (int)(container_list.size());
}


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAMICCONTAINER_HPP
