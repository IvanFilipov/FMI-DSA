/*
 * The basic linear data structure - dynamic array. With random access iterator. STL friendly.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <utility>   // std::swap
#include <stdexcept> // standard exceptions
#include <iosfwd>    // forward declarations of ostreams
#include <initializer_list> // initializer_list

namespace dsa { // the "course" name space
template<typename T> // the data type
class dynamic_array {

private :
	/* private data members */
	T* data_ptr;     // the data chunk
	size_t cur_size; // actual number of elements
	size_t capacity; // maximum current size, if we reach this point, reallocation in necessary	

public:
	/* object life cycle */
	dynamic_array(); // default constructor
	dynamic_array(size_t size); // constructor with parameter size, allocates memory for "size" objects
	dynamic_array(std::initializer_list<T> ilist); // constructor with initializer list { ... }
	dynamic_array(const dynamic_array& rhs); // copy constructor
	dynamic_array& operator=(const dynamic_array& rhs); // assignment operator
	~dynamic_array(); // destructor
	
public :
	/* iterator */
	// very basic random access iterator
	// a better implementation will give a const_iterator, too
	class iterator {
		
	private :

		T* elem_ptr;

	public :
		// lets make our iterator more STL friendly 
		// see more at : https://en.cppreference.com/w/cpp/iterator/iterator_traits
		typedef iterator                  self_type;
		typedef T                         value_type;
		typedef T&                        reference;
		typedef T*                        pointer;
		typedef std::random_access_iterator_tag
		                                  iterator_category;
		typedef int                       difference_type;
		// basic constructor
		iterator(pointer e) : elem_ptr(e) { }
		
	public :
		
		// access operators
		reference operator*() { return *elem_ptr; }
		pointer operator->() { return elem_ptr; }
		reference operator[](size_t i) { return  *(elem_ptr + i); }
		
		// compare operators
		bool operator==(const self_type& rhs) const { return elem_ptr == rhs.elem_ptr; }
		bool operator!=(const self_type& rhs) const { return !(rhs == *this); }
		bool operator<(const self_type& rhs) const { return elem_ptr < rhs.elem_ptr; } // compare the addresses
		bool operator>(const self_type& rhs) const { return (rhs < *this); }
		bool operator<=(const self_type& rhs) const { return !(*this > rhs); }
		bool operator>=(const self_type& rhs) const { return !(*this < rhs); }
		
		// modifier operators
		self_type& operator++() {
			
			++elem_ptr;
			return *this;
		}

		self_type operator++(int) {

			self_type res(*this);
			++(*this);
			return res;
		}
		
		self_type& operator--() {
			
			--elem_ptr;
			return *this;
		}

		self_type operator--(int) {

			self_type res(*this);
			--(*this);
			return res;
		}
		
		self_type& operator+=(int i) {
			
			difference_type m = i;
			if (m >= 0) while (m--) ++elem_ptr; // forward moving
			else while (m++) --elem_ptr; // backward moving
			return *this;
		}
		
		self_type operator+(int i) const {
			
			self_type res(*this);
			return res += i;
		}
		
		self_type& operator-=(int i) {
			
			return *this+=(-i);
		}
		
		self_type operator-(int i) const {
			
			self_type res(*this);
			return res -= i;
		}
		
		// difference between two iterators
		difference_type operator-(const self_type& rhs) const {
			
			return elem_ptr - rhs.elem_ptr;
		}
	};
	
private :
	/* helpers */
	// copy all objects from another dynamic array
	void copy_from(const dynamic_array& rhs);
    // reallocate internal buffer memory
	void resize(size_t new_cap);
	
	// returns an iterator with index of the searched element
	// if the element is not found, returns iterator to end()
	iterator binary_search(const T& el, int left, int right) const;
	iterator linear_search(const T& el) const;
	/** binary search has O(logN) complexity,
		linear search - 0(N).
	*/
	
public :
	/* interface */
	// free the allocated memory
	void clear();
	
	// modifiers : 
	// add a new elem in the end
	void push_back(const T& new_el);
	//removes the last elem
	void pop_back();
	/** both with amortized O(1) complexity,
		because memory reallocations.
	*/
	// add new element on random position
	// return iterator to the new element
	iterator insert_at(const iterator& index , const T& new_el);
	// removes an elem on random position
	// returns iterator following element of the deleted one
	iterator remove_at(const iterator& index, bool keep_order = true);
	/** insert_at with O(N) time complexity.
		remove_at with O(N) default case complexity,
		but could be optimized to O(1), if element sequence is not important.
	*/
	
	// access operators :
	// at random index
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	// at the end
	const T& back() const;
	T& back();
	// at beginning
	const T& front() const;
	T& front();
	
	// getters :
	// returns the current number of elements
	size_t size() const;
	// returns the current capacity
	size_t get_capacity() const;
	// return true if the dynamic array is empty, false else
	bool empty() const;

	// searches for an element and returns iterator to it if found
	// return iterator to end, else
	// a parameter is_sorted could be passed to improve speed
	iterator find(const T& el, bool is_sorted = false) const;
	
	// iterators creation interface 
	iterator begin() {
		
		return iterator(data_ptr);
	}
	
	iterator end() {
		
		return iterator(data_ptr + cur_size);
	}
	
	// constant iterator objects. they have limited usage
	// in our implementation, much better is to create
	// another class : const_iterator
	const iterator cbegin() const {
		
		return iterator(data_ptr);
	}
	
	const iterator cend() const {
		
		return iterator(data_ptr + cur_size);
	}

	// simple output functions for easier debugging
	void print_info(std::ostream& os) const;
	void print_elems(std::ostream& os) const; 
};

/* object life cycle */

template<typename T>
dynamic_array<T>::dynamic_array() : data_ptr(nullptr), cur_size(0), capacity(0) {
	/*...*/
}

template<typename T>
dynamic_array<T>::dynamic_array(size_t size) : 
	data_ptr(new T[size]), cur_size(0), capacity(size) {
	/*...*/
}

template<typename T>
dynamic_array<T>::dynamic_array(std::initializer_list<T> ilist) : dynamic_array(ilist.size()) {
	
	// notice that we have called the constructor with "size"
	// parameter to allocate memory only once, not to resize
	// each time new element from the initializer list is added
	size_t i = 0;
	for(const T& el : ilist)    // for each element from the initializer list
		data_ptr[i++] = el;     // take its value and write it into our array
	cur_size = (i) ? i - 1 : 0; // remember how much elements we have read
}

template<typename T>
dynamic_array<T>::dynamic_array(const dynamic_array<T>& rhs) : data_ptr(nullptr), cur_size(0), capacity(0) {

	copy_from(rhs);
}

template<typename T>
dynamic_array<T>& dynamic_array<T>::operator=(const dynamic_array<T>& other) { 

	if (this != &other) {

		clear();
		copy_from(other);
	}
	
	return *this;
}

template<typename T>
dynamic_array<T>::~dynamic_array() {

	clear();
}

/* helpers */

template<typename T>
void dynamic_array<T>::copy_from(const dynamic_array<T>& rhs) {

	data_ptr = new T[rhs.capacity];

	// memcpy(data, other.data, sizeof(T) * rhs.cur_size);
	// will not do the trick, because it will make a shallow copy of
	// our objects
	for (size_t i = 0; i < rhs.cur_size; i++)
		data_ptr[i] = rhs.data_ptr[i];

	cur_size = rhs.cur_size;
	capacity = rhs.capacity;
}

template<typename T>
void dynamic_array<T>::resize(size_t new_cap) {

	T *temp = data_ptr;
	
	data_ptr = new T[new_cap];

	for (size_t i = 0; i < cur_size; i++)
		data_ptr[i] = temp[i];
	
	capacity = new_cap;

	delete[] temp;
}

template<typename T>
typename dynamic_array<T>::iterator dynamic_array<T>::
	binary_search(const T& el, int left, int right) const {

	//there is no such element
	if (left > right)
		return cend();

	int med = (left + right) / 2;

	if (data_ptr[med] == el)
		return iterator(data_ptr + med);

	if (data_ptr[med] > el)
		return binary_search(el, left, med - 1);

	if(data_ptr[med] < el)
		return binary_search(el, med + 1, right);
		
	//won't reach this line, but added just to stop compiler's complaining
	return cend();
}

template<typename T>
typename dynamic_array<T>::iterator dynamic_array<T>::linear_search(const T& el) const {

	for (size_t i = 0; i < cur_size; i++)
		if (data_ptr[i] == el)
			return iterator(data_ptr + i);

	return cend();
}

/* interface */

template<typename T>
void dynamic_array<T>::clear() {
	
	delete[] data_ptr;

	data_ptr = nullptr;
	cur_size = 0;
	capacity = 0;
}

template<typename T>
void dynamic_array<T>::push_back(const T& new_el) {
	// is a reallocation needed
	if (cur_size >= capacity) {

		size_t new_cap = (capacity == 0 ? 2 : capacity * 2);
		resize(new_cap);
	}

	data_ptr[cur_size++] = new_el;
}

template<typename T>
void dynamic_array<T>::pop_back() {

	if (cur_size)
		cur_size--;
	else
		throw std::logic_error("already empty dynamic array!");
	// optional, downsizing sometimes only slows down 
	if (cur_size * 2 <= capacity) {

		size_t new_cap = ((cur_size == 0) ? 0 : capacity / 2);
		resize(new_cap);
	}
}

template<typename T>
typename dynamic_array<T>::iterator dynamic_array<T>::
	insert_at(const iterator& it, const T& new_el) {
	
	push_back(new_el); //will take care for the memory 
	
	size_t index = it - data_ptr; // the difference between the pointers it the wanted index
	//now we should 'roll' our element back to the wanted position 
	for (size_t i = cur_size - 1; i > index; i--) {

		std::swap(data_ptr[i], data_ptr[i - 1]);
	}
	
	return iterator(data_ptr + index);
}

template<typename T>
typename dynamic_array<T>::iterator dynamic_array<T>::
	remove_at(const iterator& it, bool keep_order) {
	
	size_t index = it - iterator(data_ptr);
	if (index >= cur_size || cur_size == 1) { //just removes the last elem
		
		pop_back();
		return iterator(data_ptr + cur_size - 1);
	}

	if (!keep_order) { //faster version O(1)
		
		std::swap(data_ptr[cur_size - 1], data_ptr[index]);
		pop_back();
		return iterator(data_ptr + index);
	}

	//else rolling forward
	for(size_t i = index; i < cur_size - 1; i++)
		std::swap(data_ptr[i], data_ptr[i+1]);

	pop_back();
	return iterator(data_ptr + index);
}

template<typename T>
const T& dynamic_array<T>::operator[](size_t index) const {

	if (index >= cur_size)
		throw std::out_of_range("out of range!!!");

	return data_ptr[index];
}

template<typename T>
T& dynamic_array<T>::operator[](size_t index) {

	//casting is a bad idea in general, but
	//code duplication is even worse
	return const_cast<T&>(
			static_cast<const dynamic_array&>(*this)[index]
	);
}
template<typename T>
const T& dynamic_array<T>::back() const {
	
	return (*this)[cur_size - 1];
}

template<typename T>
T& dynamic_array<T>::back() {
	
	return (*this)[cur_size - 1];
}

template<typename T>
T& dynamic_array<T>::front()  {
	
	return (*this)[0];
}
template<typename T>
const T& dynamic_array<T>::front() const {
	
	return (*this)[0];
}

template<typename T>
inline
size_t dynamic_array<T>::size() const {

	return cur_size;
}

template<typename T>
inline
size_t dynamic_array<T>::get_capacity() const {

	return capacity;
}
template<typename T>
inline
bool dynamic_array<T>::empty() const {
	return cur_size == 0;
}

template<typename T>
typename dynamic_array<T>::iterator dynamic_array<T>::find(const T& el, bool is_sorted) const {

	if (is_sorted)
		return binary_search(el, 0, cur_size); // O(logN)
	
	return linear_search(el); // O(N)
}

template<typename T>
inline
void dynamic_array<T>::print_info(std::ostream& os) const {

	os  << "obj at : Ox" << this
		<< " buffer starts at : Ox" << data_ptr
		<< " length : " << cur_size
		<< " capacity : " << capacity << std::endl;
} 


template<typename T>
void dynamic_array<T>::print_elems(std::ostream& os) const {
	
	os << "content : ";
	
	if(cur_size == 0) {
		
		os << "{}" << std::endl;	
		return;
	}
	
	if(cur_size == 1) {
		
		os << '{' << data_ptr[0] << '}' << std::endl;
		return;
	}
	
	os << "{ ";
	for(size_t i = 0; i < cur_size - 1; i++)
		os << data_ptr[i] << ", ";		
	os << data_ptr[cur_size - 1] << " }" << std::endl;
}
} // namespace dsa
