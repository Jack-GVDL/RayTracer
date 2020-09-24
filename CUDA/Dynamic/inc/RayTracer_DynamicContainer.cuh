// Author: Jack Tse 
// Email:  jacktsetcy@gmail.com
//
// Log
// 2020/09/15   initial update


#ifndef RAYTRACER_DYNAMICCONTAINER_CUH
#define RAYTRACER_DYNAMICCONTAINER_CUH


#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>


// Define
// ...


// Typedef
typedef void*	(*init_func_t)			();
typedef int		(*config_func_t)		(void*, int, uint8_t*, uint32_t);
typedef int		(*interact_func_t)		(void*, int, void**, uint32_t);

typedef int		(*config_type_func_t)	(void*, uint8_t*, uint32_t);
typedef int		(*interact_type_func_t)	(void*, void**, uint32_t);


// Enum
// ...


// Data Structure
// TODO: rename: Dynamic_ContainerSubType
struct Dynamic_ContainerType {
	// Data
	std::string			name;

	init_func_t			ops_init		= nullptr;
	config_func_t		ops_config		= nullptr;
	interact_func_t		ops_interact	= nullptr;

	// Operation
	__host__ void setOps(init_func_t init, config_func_t config, interact_func_t interact) {
		this->ops_init		= init;
		this->ops_config	= config;
		this->ops_interact	= interact;
	}

	__host__ void setName(const std::string &name) {
		this->name = name;
	}

	__host__ void setName(const char *name) {
		this->name = name;
	}
};


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
		__host__ Dynamic_ContainerBase(int index):
		index(index)
		{}

		// operation
		__host__ int	getIndex	();
};


template <class T>
class Dynamic_Container: public Dynamic_ContainerBase {
	// Data
	// there should be no data here

	// Operation
	public:
		// init
		__host__ Dynamic_Container(int index):
		Dynamic_ContainerBase(index)
		{}

		// operation
		__host__ T* getObject() {
			return (T*)object;
		}
};


// TODO: rename: Dynamic_ContainerType
// use this to hide implementation detail
class Dynamic_ContainerListBase {
	// Data
	public:
		std::vector<Dynamic_ContainerBase*>		container_list;
		std::vector<Dynamic_ContainerType*>		type_list;

		std::unordered_map<std::string, int>	name_map;

		// first valid index is 1 instead of 0
		// 0 is considered as nullptr or ERROR_NO
		// therefore, it should better not be a valid index
		int	object_index	= 1;

	// Operation
	public:
		// init
		__host__ Dynamic_ContainerListBase()
		{}

	public:
		// operation
		__host__ int						_Type_load_		();
		__host__ int						_Type_dump_		();
		__host__ int						_Type_indexOf_	(std::string name);

		// TODO: need renaming later
		__host__ Dynamic_ContainerBase*		_create_		(int type);
		__host__ int						_destroy_		(int index);
		__host__ Dynamic_ContainerBase*		_get_			(int index);
		__host__ int						_config_		(int index, int type, uint8_t *data, uint32_t size);
		__host__ int						_interact_		(int index, int type, Dynamic_ContainerBase* *list, uint32_t size);
		__host__ int						_size_			();
		__host__ int						_indexOf_		(int index);

};


template <class T>
class Dynamic_ContainerList: public Dynamic_ContainerListBase {
	// Data
	// ...

	// Operation
	public:
		// init
		__host__ Dynamic_ContainerList():
		Dynamic_ContainerListBase()
		{}

		// operation
		__host__ int						Type_load		();
		__host__ int						Type_dump		();
		__host__ int						Type_indexOf	(std::string name);

		__host__ Dynamic_Container<T>*		create			(int type);
		__host__ int						destroy			(int index);
        __host__ Dynamic_Container<T>*		get				(int index);
		__host__ int						config			(int index, int type, uint8_t *data, uint32_t size);
		__host__ int						interact		(int index, int type, Dynamic_ContainerBase* *list, uint32_t size);
		__host__ int						size			();

		
};


// Macro Function
// ...


// Static Function Prototype
// ...


// Operation Handling
template <class T>
__host__ int Dynamic_ContainerList<T>::Type_load() {
	return _Type_load_();
}


template <class T>
__host__ int Dynamic_ContainerList<T>::Type_dump() {
	return _Type_dump_();
}


template <class T>
__host__ int Dynamic_ContainerList<T>::Type_indexOf(std::string name) {
	return _Type_indexOf_(name);
}


template <class T>
__host__ Dynamic_Container<T>* Dynamic_ContainerList<T>::create(int type) {
	return (Dynamic_Container<T>*)_create_(type);
}


template <class T>
__host__ int Dynamic_ContainerList<T>::destroy(int index) {
	return _destroy_(index);
}


template <class T>
__host__ Dynamic_Container<T>* Dynamic_ContainerList<T>::get(int index) {
	return (Dynamic_Container<T>*)_get_(index);
}


template <class T>
__host__ int Dynamic_ContainerList<T>::config(int index, int type, uint8_t *data, uint32_t size) {
	return _config_(index, type, data, size);
}


template <class T>
__host__ int Dynamic_ContainerList<T>::interact(int index, int type, Dynamic_ContainerBase* *list, uint32_t size) {
	return _interact_(index, type, list, size);
}


template <class T>
__host__ int Dynamic_ContainerList<T>::size() {
	return _size_();
}


// Static Function Implementation
namespace DynamicUtil {

	__host__ static inline int configType(config_type_func_t *table, void *object, int type, uint8_t *data, uint32_t size) {
		return table[type](object, data, size);
	}


	__host__ static inline int configType(std::vector<config_type_func_t> *table, void *object, int type, uint8_t *data, uint32_t size) {
		if (type < 0 || type >= table->size()) return -1;
		return (*table)[type](object, data, size);
	}


	__host__ static inline int interactType(interact_type_func_t *table, void *object, int type, void* *list, uint32_t size) {
		return table[type](object, list, size);
	}


	__host__ static inline int interactType(std::vector<interact_type_func_t> *table, void *object, int type, void* *list, uint32_t size) {
		if (type < 0 || type >= table->size()) return -1;
		return (*table)[type](object, list, size);
	}

};


#endif  // RAYTRACER_DYNAMICCONTAINER_CUH
