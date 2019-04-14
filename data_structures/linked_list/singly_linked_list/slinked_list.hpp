/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   linked_list.hpp
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  A basic linear data structure - singly linked list.
 *         With forward iterator iterator. STL friendly.
 * @see https://en.wikipedia.org/wiki/Linked_list
 */

#pragma once
 
#include <stdexcept>        // exception types
#include <ostream>          // std::ostream
#include <initializer_list> // std::initializer_list
#include <iterator>         // declaration of bidirectional_iterator_tag

namespace dsa {
template<typename T>
/**
 * @class slinked_list
 * @brief Basic container for elements. 
 *        Supports fast insertion/removal at position pointed by an iterator.
 *        Fast random access is not supported.
 *        Only forward iterations are possible.
 * @tparam T: type of elements stored
 */
class slinked_list {
private:
	/**
	 *  @struct node
	 *  @brief  An inner representation of each "box".
	 */ 
	struct node {
		T data;         //!< the actual stored data
		node* next_ptr; //!< a pointer to the next box
		/** Creates an node by given data. */
		node(const T& ndata, node* pnext = nullptr):
			data(ndata), next_ptr(pnext) { /**/ }
	};

private:
	/* private data members */
	node* front_ptr; //!< pointer to the first box
	node* back_ptr;  //!< pointer to the last box 
	size_t cur_size; //!< current amount of objects stored

public:
	/* object life cycle */
	/** Creates %slinked_list with no elements */
	slinked_list();
	
	/** Creates %slinked_list from initializer list */
	slinked_list(std::initializer_list<T> il);
	
	/**
	  *  @brief     %slinked_list copy constructor.
	  *  @param[in] rhs: A %slinked_list of identical element type, from which to copy.
	  */
	slinked_list(const slinked_list& rhs);
	
	/**
	  *  @brief     %slinked_list assignment operator.
	  *  @param[in] rhs: A %slinked_list of identical element type, from which to copy.
	  */
	slinked_list& operator=(const slinked_list& rhs);
	
	/** Frees all memory allocated. */
	~slinked_list();
	
public:
	/* iterator */
	typedef T value_type; //!< type of stored elements
	
	/// very basic forward iterator
	class iterator {
		// only the container will have access to the private data of iterators
		friend class slinked_list<T>;
	private:
		node* node_ptr; //!< pointer to a box from %slinked_list

	public:
		// lets make our iterator more STL friendly 
		// see more at : https://en.cppreference.com/w/cpp/iterator/iterator_traits
		typedef iterator                  self_type;
		typedef T                         value_type;
		typedef T&                        reference;
		typedef T*                        pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef ptrdiff_t                 difference_type;
		/** Basic iterator constructor - points to a box from the list */
		iterator(node* n): node_ptr(n) {}
		
	public:
		//@{
		/** access operators */
		reference operator*() { return node_ptr->data; }
		const reference operator*() const { return node_ptr->data; } // for const iterators
		pointer operator->() { return &node_ptr->data; }
		//@}
		
		//@{
		/** compare operators */
		bool operator==(const iterator& rhs) const { return node_ptr == rhs.node_ptr; }
		bool operator!=(const iterator& rhs) const { return !(rhs == *this); }
		explicit operator bool() const { return node_ptr != nullptr; }
		//@}
		
		//@{
		/** modifier operators */
		self_type& operator++() {
			
			node_ptr = node_ptr->next_ptr;
			return *this;
		}

		self_type operator++(int) {

			self_type res(*this);
			++(*this);
			return res;
		}
		//@}
	};
	
private:
	/* helpers */
	/** 
	  *  @brief     copies all elements for another list
	  *  @param[in] rhs: list from which to copy.
	  */
	void copy_from(const slinked_list& rhs);
	
public:
	/* interface */
	/**
	 * @brief  get the first element from the list
	 * @retval Reference to the front element.
	 * @throw  std::logic_error if the list is empty
	 * Time complexity O(1).
	 */
	T& front();
	
	/**
	 * @brief  get the first element from the list
	 * @retval Read-only reference to the front element.
	 * @throw  std::logic_error if the list is empty
	 * Time complexity O(1).
	 */
	const T& front() const;
	
	/**
	 * @brief  get the last element from the list
	 * @retval Reference to the back element.
	 * @throw  std::logic_error if the list is empty
	 * Time complexity O(1).
	 */
	T& back();
	
	/**
	 * @brief  get the last element from the list
	 * @retval Read-only reference to the back element.
	 * @throw  std::logic_error if the list is empty
	 * Time complexity O(1).
	 */
	const T& back() const;
	
	/**
	 * @brief         Push a new element in the beginning of the list.
	 * @param[in] el: Value to be inserted
	 * Time complexity O(1).
	 */
	void push_front(const T& el); 
	
	/**
	 * @brief         Push a new element at the end of the list.
	 * @param[in] el: Value to be inserted
	 * Time complexity O(1).
	 */
	void push_back(const T& el);
	
	/** Remove the first element. Time complexity O(1). */
	void pop_front();
	
	/** Remove the last element. Time complexity O(1). */
	void pop_back();
	
	/**
	 * @brief         Insert a new element after an iterator to a random position in the list.
	 * @param[in] it: Iterator to the position after which to insert the new element.
	 * @param[in] el: Value to be inserted
	 * Time complexity O(1).
	 */
	iterator insert_after(const iterator& it, const T& el);
	
	/**
	 * @brief         Remove an element after an iterator to a random position in the list.
	 * @param[in] it: Iterator to the position after which to remove the element.
	 * @param[in] el: Value to be inserted
	 * Time complexity O(1).
	 */
	iterator remove_after(const iterator& it);
	
	/**
	 * @brief         Searches the list for a specific element.
	 * @param[in] el: Element to be searched for.
	 * @retval    iterator to the element if found
	 * @retval    %end iterator, if there is no such element
	 * Time complexity O(n) - linear in elements count.
	 */
	iterator find(const T& el) const;
	
	/** Get iterator to the beginning of the list */
	iterator begin() { return iterator(front_ptr); }
	
	/** Get iterator to the end of the list */
	iterator end() { return iterator(nullptr); }
	
	// constant iterator objects. they have limited usage
	// in our implementation, much better is to create
	// another class : const_iterator
	/** Get constant iterator to the beginning of the list */
	const iterator cbegin() const {

		return iterator(front_ptr);
	}
	
	/** Get constant iterator to the end of the list */
	const iterator cend() const {

		return iterator(nullptr);
	}
	
	/**
	 * @brief  Checks if the %slinked_list is empty.
	 * @retval boolean: whether the slinked_list is empty.
	 * Time complexity O(1).
	 */
	bool empty() const;
	
	/**
	 * @brief Get the current size of the list.
 	 * @retval Current size.
 	 * Time complexity O(1).
	 */
	size_t size() const;
	
	/** Frees the resources for the list. Time complexity liner in the count of the elements. */
	void clear();
	
	/**
	 *  @brief Debug print of the list.
	 *  @param[in,out] os: a stream to write to.
	 */
	void print(std::ostream& os) const;
};


template<typename T>
slinked_list<T>::slinked_list(): 
	front_ptr(nullptr), back_ptr(nullptr), cur_size(0) {

	//...
}

template<typename T>
slinked_list<T>::slinked_list(std::initializer_list<T> il): slinked_list() {
	
	for (const T& el: il)
		push_back(el);
}

template<typename T>
slinked_list<T>::slinked_list(const slinked_list<T>& rhs): 
	front_ptr(nullptr), back_ptr(nullptr), cur_size(0) {

	copy_from(rhs);
}

template<typename T>
slinked_list<T>& slinked_list<T>::operator=(const slinked_list<T>& rhs) {

	if (this != &rhs) {
		clear();
		copy_from(rhs);
	}

	return *this;
}

template<typename T>
slinked_list<T>::~slinked_list() {

	clear();
}

template<typename T>
void slinked_list<T>::copy_from(const slinked_list<T>& rhs) {

	if (rhs.empty()) return;

	try {
		//copy head
		front_ptr = new node(rhs.front_ptr->data);
		// for each element from rhs
		node* to_copy_it = rhs.front_ptr;
		node* copier_it = front_ptr;

		while (to_copy_it->next_ptr != nullptr) {
			// move forward into rhs
			to_copy_it = to_copy_it->next_ptr;
			// copy element into this
			copier_it->next_ptr = new node(to_copy_it->data);
			copier_it = copier_it->next_ptr;
		}
		// don't forget the 'tail'
		back_ptr = copier_it;

	} catch (std::bad_alloc&) {
		clear();
		throw;
	}
	// equal size at the end, if everything is alright
	cur_size = rhs.cur_size;
}

template<typename T>
void slinked_list<T>::push_front(const T& el) {

	if (empty()) {
		front_ptr = new node(el);
		back_ptr = front_ptr;
		cur_size++;
		return;
	}
	// create the new element
	node* new_elem = new node(el);
	// connect it with the current 'head'
	new_elem->next_ptr = front_ptr;
	// mark it as a new 'head'
	front_ptr = new_elem;

	cur_size++;
}

template<typename T>
void slinked_list<T>::push_back(const T& el) {

	if (empty()) {
		push_front(el);
		return;
	}
	// connect the new element to the 'tail'
	back_ptr->next_ptr = new node(el);
	// mark it as a new 'tail'
	back_ptr = back_ptr->next_ptr;

	cur_size++;
}

template<typename T>
T& slinked_list<T>::front() {

	return const_cast<T&>(
		static_cast<const slinked_list&>(*this).front()
	);
}

template<typename T>
const T& slinked_list<T>::front() const {

	if (empty())
		throw std::logic_error("the list is empty");

	return front_ptr->data;
}

template<typename T>
T& slinked_list<T>::back() {

	return const_cast<T&>(
		static_cast<const slinked_list&>(*this).back()
	);
}

template<typename T>
const T& slinked_list<T>::back() const {

	if (empty())
		throw std::logic_error("the list is empty");
		
	return back_ptr->data;
}

template<typename T>
void slinked_list<T>::pop_front() {

	if (empty())
		throw std::logic_error("the list is empty");
	
	if (cur_size == 1) {
		// remove the first and zero the structure
		clear();
		return;
	}
	
	node* destroyer = front_ptr;
	front_ptr = front_ptr->next_ptr;
	delete destroyer;

	cur_size--;
}

template<typename T>
void slinked_list<T>::pop_back() {

	if (empty())
		throw std::logic_error("the list is empty");
	
	if (cur_size == 1) {
		clear();
		return;
	}
	// we should get to the end, step by step
	node* it = front_ptr;
	// iterate to the last element
	while (it->next_ptr != back_ptr)
		it = it->next_ptr;
	// remove the 'tail'
	delete back_ptr;
	// redirect the 'tail' to the element before it
	back_ptr = it;
	// mark it as a last element
	back_ptr->next_ptr = nullptr;

	cur_size--;
}

template<typename T>
typename slinked_list<T>::iterator slinked_list<T>::find(const T& elem) const {

	node* it = front_ptr;

	while (it != nullptr) {
		if (it->data == elem)
			return iterator(it);
		it = it->next_ptr;
	}
	
	return cend();
}

template<typename T>
typename slinked_list<T>::iterator slinked_list<T>::
	insert_after(const typename slinked_list<T>::iterator& it, const T& el) {
	
	// insert after the last element
	if (it == end() || it.node_ptr == back_ptr) {
		push_back(el);
		return iterator(back_ptr);
	}
	// create the new element
	node* new_node = new node(el);
	// link it to the next element after the iterator
	new_node->next_ptr = it.node_ptr->next_ptr;
	// mark it as a element after the iterator
	it.node_ptr->next_ptr = new_node;
	
	++cur_size; 
	return new_node;
}

template<typename T>
typename slinked_list<T>::iterator slinked_list<T>::
	remove_after(const typename slinked_list<T>::iterator& it) {
	
	if (empty())
		throw std::logic_error("empty queue!");
	// there is no element after this iterator
	if (it.node_ptr->next_ptr == nullptr)
			return end();
	// last element case
	if (it.node_ptr->next_ptr == back_ptr) {
		delete back_ptr;
		back_ptr = it.node_ptr;
		back_ptr->next_ptr = nullptr;
		return iterator(back_ptr);
	}
	// a pointer to the element which is about to be deleted
	node* to_delete = it.node_ptr->next_ptr;
	
	// we will have node_ptr->next_ptr->next_ptr, because, the ptr->next_ptr is not the last element
	// connecting the pointed by iterator box with the box two steps in front of it
	it.node_ptr->next_ptr = it.node_ptr->next_ptr->next_ptr;
	// free the resources for the deleted box
	delete to_delete;
	--cur_size;
	return it.node_ptr->next_ptr;
}

template<typename T>
inline
bool slinked_list<T>::empty() const {

	return cur_size == 0;
}

template<typename T>
inline
size_t slinked_list<T>::size() const {

	return cur_size;
}

template<typename T>
void slinked_list<T>::clear() {

	node* destroyer;
	// iterating through the elements
	while (front_ptr != nullptr) {
		// remember where the current 'head' is
		destroyer = front_ptr;
		// move one step forward
		front_ptr = front_ptr->next_ptr;
		// remove the 'old head'
		delete destroyer;
	}
	// zeros all members
	front_ptr = nullptr;
	back_ptr = nullptr;
	cur_size = 0;
}

template<typename T>
void slinked_list<T>::print(std::ostream& os) const {
	
	if(cur_size == 0) {
		os << "{}" << std::endl;	
		return;
	}
	
	if(cur_size == 1) {
		os << '{' << front_ptr->data << '}' << std::endl;
		return;
	}
	
	os << "{ ";
	node* it = front_ptr;
	while (it->next_ptr != nullptr) {
		os << it->data << ", ";
		it = it->next_ptr;
	}
	os << it->data << " }" << std::endl;
}
} // namespace dsa
