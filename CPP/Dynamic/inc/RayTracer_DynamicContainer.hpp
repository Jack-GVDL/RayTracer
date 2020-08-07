// Created by Jack Tse on 2020/07/29
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/29   initial update
// 2020/08/07   add binary search, complete destroy()


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
class Dynamic_ContainerBase {
	// Data
	protected:
		int		index;
	
	public:
		int		type;
		void	*object;

	// Operation
	public:
		// init
		Dynamic_ContainerBase(int index):
		index(index)
		{}

		// operation
		int	getIndex	();
};


template <class T>
class Dynamic_Container: public Dynamic_ContainerBase {
	// Data
	// there should be no data here

	// Operation
	public:
		// init
		Dynamic_Container(int index):
		Dynamic_ContainerBase(index)
		{}

		// operation
		T* getObject() {
			return (T*)object;
		}
};


// use this to hide implementation detail
class Dynamic_ContainerListBase {
	// Data
	public:
		std::vector<Dynamic_ContainerBase*>		container_list;
		std::vector<init_func_t>				init_list;
		std::vector<config_func_t>				config_list;

		// first valid index is 1 instead of 0
		// 0 is considered as nullptr or ERROR_NO
		// therefore, it should better not be a valid index
		int	object_index	= 1;

	// Operation
	public:
		// init
		Dynamic_ContainerListBase()
		{}

	protected:
		// operation
		Dynamic_ContainerBase*	_create_	(int type);
		int						_destroy_	(int index);
		Dynamic_ContainerBase*	_get_		(int index);
		int						_config_	(int index, int type, uint8_t *data, uint32_t size);
		int						_size_		();
		int						_indexOf_	(int index);

};


template <class T>
class Dynamic_ContainerList: public Dynamic_ContainerListBase {
	// Data
	// ...

	// Operation
	public:
		// init
		Dynamic_ContainerList():
		Dynamic_ContainerListBase()
		{}

		// operation
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
	return (Dynamic_Container<T>*)_create_(type);
}


template <class T>
int Dynamic_ContainerList<T>::destroy(int index) {
	return _destroy_(index);
}


template <class T>
Dynamic_Container<T>* Dynamic_ContainerList<T>::get(int index) {
	return (Dynamic_Container<T>*)_get_(index);
}


template <class T>
int Dynamic_ContainerList<T>::config(int index, int type, uint8_t *data, uint32_t size) {
	return _config_(index, type, data, size);
}


template <class T>
int Dynamic_ContainerList<T>::size() {
	return _size_();
}


// Inline Function Implementation
// ...


#endif  // RAYTRACER_DYNAMICCONTAINER_HPP
