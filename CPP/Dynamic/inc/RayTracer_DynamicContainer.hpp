// Created by Jack Tse on 2020/07/29
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/29   initial update
// 2020/08/07   add binary search, complete destroy()
// 2020/08/18   add name_map


#ifndef RAYTRACER_DYNAMICCONTAINER_HPP
#define RAYTRACER_DYNAMICCONTAINER_HPP


#include <string>
#include <vector>
#include <unordered_map>
#include <stdint.h>


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
	void setOps(init_func_t init, config_func_t config, interact_func_t interact) {
		this->ops_init		= init;
		this->ops_config	= config;
		this->ops_interact	= interact;
	}

	void setName(const std::string &name) {
		this->name = name;
	}

	void setName(const char *name) {
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
		Dynamic_ContainerListBase()
		{}

	public:
		// operation
		int						_Type_load_		();
		int						_Type_dump_		();
		int						_Type_indexOf_	(std::string name);

		// TODO: need renaming later
		Dynamic_ContainerBase*	_create_	(int type);
		int						_destroy_	(int index);
		Dynamic_ContainerBase*	_get_		(int index);
		int						_config_	(int index, int type, uint8_t *data, uint32_t size);
		int						_interact_	(int index, int type, Dynamic_ContainerBase* *list, uint32_t size);
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
		int						Type_load		();
		int						Type_dump		();
		int						Type_indexOf	(std::string name);

		Dynamic_Container<T>*	create			(int type);
		int						destroy			(int index);
        Dynamic_Container<T>*	get				(int index);
		int						config			(int index, int type, uint8_t *data, uint32_t size);
		int						interact		(int index, int type, Dynamic_ContainerBase* *list, uint32_t size);
		int						size			();

		
};


/*
// TODO: reanme: Dynamic_ContainerList
class Dynamic_ContainerClusterBase {
	// Data
	public:
		std::vector<int>						index_list;
		std::vector<Dynamic_ContainerBase>		container_list;

	// Operation
	protected:
		// init, del
		Dynamic_ContainerClusterBase()
		{}

		~Dynamic_ContainerClusterBase()
		{}

		// operation
		error_t					_setList_		(std::vector<int> index_list);
		error_t					_load_			();
		error_t					_dump_			();

		Dynamic_ContainerBase*	_data_			();
		int32_t					_size_			();
		error_t					_isLoaded_		();
};


template <class T>
class Dynamic_ContainerCluster: public Dynamic_ContainerCluster {
	// Data
	public:
		// ...

	// Operation
	public:
		// init, del
		Dynamic_ContainerCluster():
		Dynamic_ContainerClusterBase()
		{}

		~Dynamic_ContainerCluster()
		{}

		// operation
		error_t					setList			(std::vector<int> index_list);
		error_t					load			();
		error_t					dump			();

		Dynamic_Container<T>*	data			();
		int32_t					size			();
		error_t					isLoaded		();
};
*/


// Macro Function
// ...


// Static Function Prototype
// ...


// Operation Handling
template <class T>
int	Dynamic_ContainerList<T>::Type_load() {
	return _Type_load_();
}


template <class T>
int	Dynamic_ContainerList<T>::Type_dump() {
	return _Type_dump_();
}


template <class T>
int	Dynamic_ContainerList<T>::Type_indexOf(std::string name) {
	return _Type_indexOf_(name);
}


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
int Dynamic_ContainerList<T>::interact(int index, int type, Dynamic_ContainerBase* *list, uint32_t size) {
	return _interact_(index, type, list, size);
}


template <class T>
int Dynamic_ContainerList<T>::size() {
	return _size_();
}


// Static Function Implementation
namespace DynamicUtil {

	static inline int	configType		(config_type_func_t *table, void *object, int type, uint8_t *data, uint32_t size) {
		return table[type](object, data, size);
	}


	static inline int	configType		(std::vector<config_type_func_t> *table, void *object, int type, uint8_t *data, uint32_t size) {
		if (type < 0 || type >= table->size()) return -1;
		return (*table)[type](object, data, size);
	}


	static inline int	interactType	(interact_type_func_t *table, void *object, int type, void* *list, uint32_t size) {
		return table[type](object, list, size);
	}


	static inline int	interactType	(std::vector<interact_type_func_t> *table, void *object, int type, void* *list, uint32_t size) {
		if (type < 0 || type >= table->size()) return -1;
		return (*table)[type](object, list, size);
	}

};


#endif  // RAYTRACER_DYNAMICCONTAINER_HPP
