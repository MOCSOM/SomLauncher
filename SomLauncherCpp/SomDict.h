#ifndef SOMDICT_H_     // equivalently, #if !defined HEADER_H_
#define SOMDICT_H_




//template<class KEY, class VALUE>
//class SomDict
//{
//private:
//	struct Node {
//		KEY _t_key;
//		VALUE _t_value;
//	};
//
//	Node* data = nullptr;
//	size_t size = 0;
//
//public:
//	SomDict() {
//		Allocator<Node> alloc;
//		data = alloc.allocate(10);
//	}
//	SomDict(size_t size): data(new Node[size]), size(size) {}
//	~SomDict(){
//		delete[] data;
//	}
//
//	const VALUE& operator[](const KEY& key) const {
//		for (int i = 0; i < size; i++) {
//			if (data[i]._t_key == key) {
//				return data[i]._t_value;
//			}
//		}
//		throw "Key not found";
//	}
//	const VALUE& operator=(const VALUE& value) const {
//		data[key]._t_value = value;	
//		return *this;
//	}
//	SomDict& operator=(const SomDict& other) {
//		if (this != &other) {
//			delete[] data;
//			data = new Node[other.size];
//			size = other.size;
//			for (size_t i = 0; i < size; i++) {
//				data[i]._t_key = other.data[i]._t_key;
//				data[i]._t_value = other.data[i]._t_value;
//			}
//		}
//		return *this;
//	}
//
//	int get_size() {
//		return size;
//	}
//	/*SomDict begin();
//	SomDict end();
//	KEY first();
//	VALUE second();*/
//	void add(KEY key, VALUE value) {
//		int curr_size = get_size();
//		Allocator<VALUE> alloc;
//		VALUE* new_value = alloc.allocate(1);
//		data[index].key = key;
//		data[index].value = value;
//		new_value[curr_size + 1] = value;
//	}
//public:
//	//void _more_mem();
//public:
//	/*__interface Count
//	{
//
//	};*/
//};
//
//template<class T>
//class Massive
//{
//public:
//	using pointer = T*;
//	using size_type = std::size_t;
//
//	Massive(size_type n){
//		Allocator<T> alloc;
//		T* bebey = alloc.allocate(n);
//
//	}
//
//	~Massive() {
//
//	}
//
//private:
//
//};

//template<typename T>
//class Allocator
//{
//protected:
//	int* _pointer_of_begin;
//	int* _pointer_of_free_space;
//	int _size;
//
//public:
//	//using value_type = T;
//	//using pointer = T*;
//	//using const_pointer = const T*;
//	//using size_type = std::size_t;
//
//	Allocator(int size) : _size(size)
//	{
//		_pointer_of_begin = new int[_size];
//	}
//	~Allocator()
//	{
//	}
//
//	/*template<class U>
//	Allocator(const Allocator<U>&) noexcept;*/
//
//	//[[nodiscard]] pointer allocate(size_type n)
//	//{
//	//	if (auto p = static_cast<pointer>(std::malloc(n * sizeof(T)))) {
//	//		return p;
//	//	}
//	//	throw 1; // Выброс исключения, если не удается выделить достаточно памяти
//	//}
//
//	//void deallocate(pointer p, size_type) noexcept
//	//{
//	//	std::free(p);
//	//}
//
//	int* allocate(int* new_pointre)
//	{
//		//new_pointre = new(_pointer_of_begin);
//		return new_pointre;
//	}
//
//	void deallocate()
//	{
//	}
//};


#endif SOMDICT_H_