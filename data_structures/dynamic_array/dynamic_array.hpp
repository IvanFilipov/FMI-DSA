/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   dynamic_array.hpp
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  The most basic linear data structure - dynamic array.
 *         With random access iterator. STL friendly.
 * @see https://en.wikipedia.org/wiki/Dynamic_array
 */

#pragma once
 
#include <utility>   // std::swap()
#include <stdexcept> // standard exceptions
#include <iostream>  // std::ostream
#include <initializer_list> // std::initializer_list
#include <iterator>         // declaration of random_access_iterator_tag

namespace dsa { // the "course" name space
/**
 * @class dynamic_array
 * @brief Basic container for elements. 
 *        Supports random access.
 * @tparam T: type of elements stored
 */
template<typename T>
class dynamic_array {
private:
	/* private data members */
	T* data_ptr;     //!< the data chunk
	size_t cur_size; //!< actual number of elements
	size_t capacity; //!< maximum current size, if we reach this point, reallocation in necessary	

public:
	/* object life cycle */
	/** Creates %dynamic_array with no elements */
	dynamic_array();
	
	/** 
	 * @brief Constructs %dynamic_array with preallocated memory for some elements
	 * @param[in] size: for how many elements to allocate memory for
	 */
	dynamic_array(size_t size);
	
	/** 
	 * @brief Constructs %dynamic_array with initialized elements
	 * @param[in] size: for how many elements to allocate memory for
	 * @param[in] value: initialize value
	 */
	dynamic_array(size_t size, const T& value);
	
	/** Creates %dynamic_array from initializer list */
	dynamic_array(std::initializer_list<T> ilist);
	
	/**
	  *  @brief     %dynamic_array copy constructor.
	  *  @param[in] rhs: A %dynamic_array of identical element type, from which to copy.
	  */
	dynamic_array(const dynamic_array& rhs);
	
	/**
	  *  @brief     %dynamic_array assignment operator.
	  *  @param[in] rhs: A %dynamic_array of identical element type, from which to copy.
	  */
	dynamic_array& operator=(const dynamic_array& rhs);
	
	/** Frees all memory allocated. */
	~dynamic_array();
	
public:
	/* iterator */
	/// very basic random access iterator
	/// @note a better implementation will give a const_iterator, too
	class iterator {		
	private:
		T* elem_ptr; //!< pointer to a element from the array

	public:
		// lets make our iterator more STL friendly 
		// see more at : https://en.cppreference.com/w/cpp/iterator/iterator_traits
		typedef iterator                  self_type;
		typedef T                         value_type;
		typedef T&                        reference;
		typedef T*                        pointer;
		typedef std::random_access_iterator_tag
		                                  iterator_category;
		typedef int                       difference_type;
		/** Basic iterator constructor - points to an element from the array */
		iterator(pointer e = nullptr) : elem_ptr(e) { }
		
	public:
		//@{
		/** access operators */
		reference operator*() { return *elem_ptr; }
		pointer operator->() { return elem_ptr; }
		reference operator[](size_t i) { return  *(elem_ptr + i); }
		//@}
		
		//@{
		/** compare operators */
		bool operator==(const self_type& rhs) const { return elem_ptr == rhs.elem_ptr; }
		bool operator!=(const self_type& rhs) const { return !(rhs == *this); }
		bool operator<(const self_type& rhs) const { return elem_ptr < rhs.elem_ptr; } // compare the addresses
		bool operator>(const self_type& rhs) const { return (rhs < *this); }
		bool operator<=(const self_type& rhs) const { return !(*this > rhs); }
		bool operator>=(const self_type& rhs) const { return !(*this < rhs); }
		//@}
		
		//@{
		/** modifier operators */
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
			else        while (m++) --elem_ptr; // backward moving
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
		//@}
		
		/// calculates difference between two iterators
		difference_type operator-(const self_type& rhs) const {
			
			return elem_ptr - rhs.elem_ptr;
		}
	};
	
private:
	/* helpers */
	/** 
	  *  @brief     copies all elements for another array
	  *  @param[in] rhs: array from which to copy.
	  */
	void copy_from(const dynamic_array& rhs);
   
	/**
	 * @brief search for element using Binary search
	 * @param[in] el: element to be searched for
	 * @param[in] left: left border of the current part
	 * @param[in] right: right border of the current part
	 * @retval    iterator to the element if found
	 * @retval    %end iterator, if there is no such element
	 *
	 * Actually a helper for @see find(), to be used when the
	 * array is known to be sorted.
	 * Time complexity O(logn).
	 *
	 * For more details about implementation:
	 * @see https://github.com/IvanFilipov/FMI-DSA/blob/master/algorithms/sorting_and_searching/searching/search_algorithms.c
	 */ 
	iterator binary_search(const T& el, int left, int right) const;
	
	/**
	 * @brief search for element using Linear search
	 * @param[in] el: element to be searched for
	 * @retval    iterator to the element if found
	 * @retval    %end iterator, if there is no such element
	 *
	 * Actually a helper for @see find(), to be used when the
	 * array is known to be unsorted.
	 * Time complexity O(n).
	 */ 
	iterator linear_search(const T& el) const;

public:
	/* interface */
	/**
	 * @brief Reallocates internal buffer memory
	 * @param[in] new_cap: desirable capacity
	 */
	void resize(size_t new_cap);
	
	/**
	 * @brief Swaps two dynamic arrays
	 * @param[in] rhs: another array to be swapped with
	 * @note only pointers swap is preformed, not element by element,
	 *       thats why the time complexity is O(1).
	 */
	void swap_with(dynamic_array& rhs);
	
	/**
	 * @brief  get the first element from the array
	 * @retval Reference to the front element.
	 * @throw  std::logic_error if the array is empty
	 * Time complexity O(1).
	 */
	T& front();
	
	/**
	 * @brief  get the first element from the array
	 * @retval Read-only reference to the front element.
	 * @throw  std::logic_error if the array is empty
	 * Time complexity O(1).
	 */
	const T& front() const;
	
	/**
	 * @brief  get the last element from the array
	 * @retval Reference to the back element.
	 * @throw  std::logic_error if the array is empty
	 * Time complexity O(1).
	 */
	T& back();
	
	/**
	 * @brief  get the last element from the array
	 * @retval Read-only reference to the back element.
	 * @throw  std::logic_error if the array is empty
	 * Time complexity O(1).
	 */
	const T& back() const;
	
	/**
	 * @brief  get element on a random position
	 * @param[in] index: the wanted position
	 * @retval Reference to that element.
	 * @throw  std::out_of_range if the index is outside the array.
	 * Time complexity O(1).
	 */
	T& operator[](size_t index);
	
	/**
	 * @brief  get element on a random position
	 * @param[in] index: the wanted position
	 * @retval Read-only reference to that element.
	 * @throw  std::out_of_range if the index is outside the array.
	 * Time complexity O(1).
	 */
	const T& operator[](size_t index) const;
	
	/**
	 * @brief         Push a new element at the end of the array.
	 * @param[in] el: Value to be inserted
	 * Time complexity amortized O(1), because memory reallocations may be needed.
	 */
	void push_back(const T& new_el);
	
	/**
	 * @brief         Remove the last element.
	 * Time complexity amortized O(1), because memory reallocations may be needed.
	 * @note in std::vector's implementation, only growing allocations are done,
	 *       in our implementation, we also downsize the array.
	 */
	void pop_back();
	
	/**
	 * @brief         Insert a new element at random position of the array.
	 * @param[in] it: Iterator to the position on which the new element to be inserted.
	 * @param[in] el: Value to be inserted
	 * Time complexity O(n), because all element after that index are rolled with one position.
	 */
	iterator insert_at(const iterator& index , const T& new_el);
	
	/**
	 * @brief         Remove an element at random position of the array.
	 * @param[in] it: Iterator to the position on which the element to be removed.
	 * @param[in] keep_order: if set to true, keeps the order of elements, it is slower, but
	 *            expected. [default value = true].
	 * Time complexity O(n).
	 * @note the time complexity could be optimized to O(1), if element sequence is not important.
	 */
	iterator remove_at(const iterator& index, bool keep_order = true);
	
	/**
	 * @brief         Searches the array for a specific element.
	 * @param[in] el: Element to be searched for.
	 * @param[in] is_sorted: could be set to true, if the array is known to be sorted,
	 *            that will significantly improve speed. [by default = false]. 
	 * @retval    iterator to the element if found
	 * @retval    %end iterator, if there is no such element
	 * Time complexity O(n) - linear in elements count, if not sorted,
	 * log(n) - if sorted.
	 */
	iterator find(const T& el, bool is_sorted = false) const;
	
	/** Get iterator to the beginning of the array */
	iterator begin() { return iterator(data_ptr); }
	
	/** Get iterator to the end of the array */
	iterator end() { return iterator(data_ptr + cur_size); }
	
	// constant iterator objects. they have limited usage
	// in our implementation, much better is to create
	// another class: const_iterator
	/** Get constant iterator to the beginning of the array */
	const iterator cbegin() const {
		
		return iterator(data_ptr);
	}
	
	/** Get constant iterator to the end of the array */
	const iterator cend() const {
		
		return iterator(data_ptr + cur_size);
	}
	
	/**
	 * @brief  Checks if the %dynamic_array is empty.
	 * @retval boolean: whether the dynamic_array is empty.
	 * Time complexity O(1).
	 */
	bool empty() const;
	
	/**
	 * @brief Get the current size of the array.
 	 * @retval Current size.
 	 * Time complexity O(1).
	 */
	size_t size() const;
	
	/** Frees the resources for the list. Time complexity liner in the count of the elements. */
	void clear();
	
	/** Get the current capacity. */
	size_t get_capacity() const;
	
	/** Prints debug info about an instance of %dynamic_array */
	void print_info(std::ostream& os) const;
	
	/**
	 *  @brief Debug print of the array.
	 *  @param[in,out] os: a stream to write to.
	 */
	void print_elems(std::ostream& os) const; 
};

template<typename T>
dynamic_array<T>::dynamic_array():
	data_ptr(nullptr), cur_size(0), capacity(0) {
	/*...*/
}

template<typename T>
dynamic_array<T>::dynamic_array(size_t size): 
	data_ptr(new T[size]), cur_size(0), capacity(size) {
	/*...*/
}
template<typename T>
dynamic_array<T>::dynamic_array(size_t size, const T& value): 
	data_ptr(new T[size]), cur_size(size), capacity(size) {
	
	for (size_t i = 0; i < cur_size; i++)
		data_ptr[i] = value;
}

template<typename T>
dynamic_array<T>::dynamic_array(std::initializer_list<T> ilist): 
	dynamic_array(ilist.size()) {
	
	// notice that we have called the constructor with "size"
	// parameter to allocate memory only once, not to resize
	// each time new element from the initializer list is added
	size_t i = 0;
	for (const T& el: ilist)    // for each element from the initializer list
		data_ptr[i++] = el;     // take its value and write it into our array
	cur_size = (i) ? i - 1 : 0; // remember how much elements we have read
}

template<typename T>
dynamic_array<T>::dynamic_array(const dynamic_array<T>& rhs): dynamic_array() {

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
typename dynamic_array<T>::iterator dynamic_array<T>::
	binary_search(const T& el, int left, int right) const {
	// there is no such element
	if (left > right)
		return cend();

	int mid = left + (right - left) / 2;

	if (data_ptr[mid] == el)
		return iterator(data_ptr + mid);

	if (data_ptr[mid] > el)
		return binary_search(el, left, mid - 1);

	if (data_ptr[mid] < el)
		return binary_search(el, mid + 1, right);
		
	// won't reach this line, but added just to stop compiler's complaining
	return cend();
}

template<typename T>
typename dynamic_array<T>::iterator dynamic_array<T>::
	linear_search(const T& el) const {

	for (size_t i = 0; i < cur_size; i++)
		if (data_ptr[i] == el)
			return iterator(data_ptr + i);

	return cend();
}

template<typename T>
void dynamic_array<T>::clear() {
	
	delete[] data_ptr;

	data_ptr = nullptr;
	cur_size = 0;
	capacity = 0;
}

template<typename T>
void dynamic_array<T>::resize(size_t new_cap) {

	T* temp = data_ptr;
	
	data_ptr = new T[new_cap];

	for (size_t i = 0; i < cur_size; i++)
		data_ptr[i] = temp[i];
	
	capacity = new_cap;

	delete[] temp;
}

template<typename T>
void dynamic_array<T>::swap_with(dynamic_array<T>& rhs) {
	
	std::swap(data_ptr, rhs.data_ptr);
	std::swap(capacity, rhs.capacity);
	std::swap(cur_size, rhs.cur_size);
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
		throw std::logic_error("already empty dynamic array");
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
	for (size_t i = cur_size - 1; i > index; i--)
		std::swap(data_ptr[i], data_ptr[i - 1]);
	
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
	for (size_t i = index; i < cur_size - 1; i++)
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
		return binary_search(el, 0, (int)cur_size - 1); // O(logN)
	
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
		
	if (cur_size == 0) {
		os << "{}" << std::endl;	
		return;
	}
	
	if (cur_size == 1) {
		os << '{' << data_ptr[0] << '}' << std::endl;
		return;
	}
	
	os << "{ ";
	for (size_t i = 0; i < cur_size - 1; i++)
		os << data_ptr[i] << ", ";		
	os << data_ptr[cur_size - 1] << " }" << std::endl;
}
} // namespace dsa
