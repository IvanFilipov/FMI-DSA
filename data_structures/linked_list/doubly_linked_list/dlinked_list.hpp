/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   doubly_linked_list.hpp
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  A basic linear data structure - doubly linked list.
 *         With bidirectional iterator. STL friendly.
 * @see https://en.wikipedia.org/wiki/Doubly_linked_list
 */

#pragma once
 
#include <stdexcept>        // exception types
#include <ostream>          // std::ostream
#include <initializer_list> // std::initializer_list
#include <iterator>         // declaration of bidirectional_iterator_tag

#include <list>

namespace dsa {
/**
 * @class dlinked_list
 * @brief Basic container for elements. 
 *        Supports fast insertion/removal at random position.
 *        Fast random access is not supported.
 *        Less space efficient than singly linked list, but supports bidirectional iterations.
 * @tparam T: type of elements stored
 */
template<typename T>
class dlinked_list {
private:
	/**
	 *  @struct node
	 *  @brief  An inner representation of each "box".
	 */ 
	struct node {
		T data;         //!< the actual stored data
		node* prev_ptr; //!< a pointer to the previous box
		node* next_ptr; //!< a pointer to the next box
		/** Creates an node by given data. */
		node(const T& ndata, node* pprev = nullptr, node* pnext = nullptr):
			data(ndata), prev_ptr(pprev), next_ptr(pnext) { /**/ }
	};

private:
	/* private data members */
	node* front_ptr; //!< pointer to the first box
	node* back_ptr;  //!< pointer to the last box 
	size_t cur_size; //!< current amount of objects stored
	/// ---- a dummy element --- used as "the element after the last one"
	node* dummy; // a bit of overhead in order to make our bidirectional iterator work 
	
public:
	/* object life cycle */
	/** Creates %dlinked_list with no elements */
	dlinked_list();
	
	/** Creates %dlinked_list from initializer list */
	dlinked_list(std::initializer_list<T> il);
	
	/**
	  *  @brief     %dlinked_list copy constructor.
	  *  @param[in] rhs: A %dlinked_list of identical element type, from which to copy.
	  */
	dlinked_list(const dlinked_list& rhs);
	
	/**
	  *  @brief     %dlinked_list assignment operator.
	  *  @param[in] rhs: A %dlinked_list of identical element type, from which to copy.
	  */
	dlinked_list& operator=(const dlinked_list& rhs);
	
	/** Frees all memory allocated. */
	~dlinked_list();
	
public:
	/* iterator */
	typedef T value_type; //!< type of stored elements

	/// very basic bidirectional iterator
	class iterator {
		// only the container will have access to the private data of iterators
		friend class dlinked_list<T>;
	private:
		node* node_ptr; //!< pointer to a box from %dlinked_list

	public:
		// lets make our iterator more STL friendly 
		// see more at : https://en.cppreference.com/w/cpp/iterator/iterator_traits
		typedef iterator                  self_type;
		typedef T                         value_type;
		typedef T&                        reference;
		typedef T*                        pointer;
		typedef std::bidirectional_iterator_tag 
										  iterator_category;
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
		bool operator==(const self_type& rhs) const { return node_ptr == rhs.node_ptr; }
		bool operator!=(const self_type& rhs) const { return !(rhs == *this); }
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
		
		self_type& operator--() {
			
			node_ptr = node_ptr->prev_ptr;
			return *this;
		}

		self_type operator--(int) {

			self_type res(*this);
			--(*this);
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
	void copy_from(const dlinked_list& rhs);
	
	/** makes sure that dummy is the element after the last one */
	void fix_dummy();
	
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
	 * @brief         Insert a new element at random position of the list.
	 * @param[in] it: Iterator to the position on which the new element to be inserted.
	 * @param[in] el: Value to be inserted
	 * Time complexity O(1).
	 */
	iterator insert(const iterator& it, const T& el);
	
	/**
	 * @brief         Remove an element at random position of the list.
	 * @param[in] it: Iterator to the position on which the element to be removed.
	 * Time complexity O(1).
	 */
	iterator remove(const iterator& it);
	
	/**
	 * @brief         Searches the list for a specific element.
	 * @param[in] el: Element to be searched for.
	 * @retval    iterator to the element if found
	 * @retval    %end iterator, if there is no such element
	 * Time complexity O(n) - linear in elements count.
	 */
	iterator find(const T& el) const;
	
	/** Get iterator to the beginning of the list */
	iterator begin() {

		return (front_ptr) ? iterator(front_ptr) : iterator(dummy);
	}
	
	/** Get iterator to the end of the list */
	iterator end() {

		return iterator(dummy);
	}
	
	// constant iterator objects. they have limited usage
	// in our implementation, much better is to create
	// another class - const_iterator
	/** Get constant iterator to the beginning of the list */
	const iterator cbegin() const {

		return iterator(front_ptr);
	}
	
	/** Get constant iterator to the end of the list */
	const iterator cend() const {

		return iterator(dummy);
	}
	// a kind of reversed iterators - a better implementation
	// could use another class with op--, op++ overloads
	/** Get reverse iterator from the beginning of the list */
	iterator rbegin() {

		return --end();
	}
	
	/** Get reverse iterator from the end of the list */
	iterator rend() {

		return --begin();
	}
	
	/**
	 * @brief  Checks if the %dlinked_list is empty.
	 * @retval boolean: whether the dlinked_list is empty.
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
dlinked_list<T>::dlinked_list(): 
	front_ptr(nullptr), back_ptr(nullptr),
	cur_size(0), dummy(new node({} , back_ptr)) {
	//...
}

template<typename T>
dlinked_list<T>::dlinked_list(std::initializer_list<T> il): dlinked_list() {
	
	for (const T& el: il)
		push_back(el);
	fix_dummy();
}

template<typename T>
dlinked_list<T>::dlinked_list(const dlinked_list<T>& rhs): dlinked_list() {

	copy_from(rhs);
}

template<typename T>
dlinked_list<T>& dlinked_list<T>::operator=(const dlinked_list<T>& rhs) {

	if (this != &rhs) {
		clear();
		copy_from(rhs);
	}
	
	return *this;
}

template<typename T>
dlinked_list<T>::~dlinked_list() {

	clear();
}

template<typename T>
void dlinked_list<T>::copy_from(const dlinked_list<T>& rhs) {

	if (rhs.empty()) return;

	try {
		//copy head, prev and next are both nullptrs
		front_ptr = new node(rhs.front_ptr->data);
		// for each element from rhs
		node* to_copy_it = rhs.front_ptr;
		node* copier_it = front_ptr;

		while (to_copy_it->next_ptr != rhs.dummy) {
			// move forward into rhs
			to_copy_it = to_copy_it->next_ptr;
			// copy element into this
			copier_it->next_ptr = new node(to_copy_it->data, copier_it); // connect new with current in both directions
			copier_it = copier_it->next_ptr; // make step forward
		}
		// don't forget the 'tail'
		back_ptr = copier_it;

	} catch (std::bad_alloc&) {
		clear();
		throw;
	}
	// equal size at the end, if everything is alright
	cur_size = rhs.cur_size;
	// our dummy fix
	fix_dummy();
}

template<typename T>
void dlinked_list<T>::fix_dummy() {
	
	dummy->prev_ptr = back_ptr;
	if (back_ptr) back_ptr->next_ptr = dummy;
}

template<typename T>
void dlinked_list<T>::push_front(const T& el) {

	if (empty()) {
		front_ptr = new node(el);
		back_ptr = front_ptr;
		fix_dummy();
		cur_size++;
		return;
	}
	// create the new element, connect it to the head
	front_ptr->prev_ptr = new node(el, nullptr, front_ptr);
	// mark it as a new head
	front_ptr = front_ptr->prev_ptr;

	cur_size++;
}

template<typename T>
void dlinked_list<T>::push_back(const T& el) {

	if (empty()) {
		push_front(el);
		return;
	}
	// create the new element, connect it to the 'tail'
	back_ptr->next_ptr = new node(el, back_ptr);
	// mark it as a new 'tail'
	back_ptr = back_ptr->next_ptr;

	cur_size++;
	fix_dummy();
}

template<typename T>
T& dlinked_list<T>::front() {

	return const_cast<T&>(
		static_cast<const dlinked_list&>(*this).front()
	);
}

template<typename T>
const T& dlinked_list<T>::front() const {

	if (empty())
		throw std::logic_error("the list is empty");

	return front_ptr->data;
}

template<typename T>
T& dlinked_list<T>::back() {

	return const_cast<T&>(
		static_cast<const dlinked_list&>(*this).back()
	);
}

template<typename T>
const T& dlinked_list<T>::back() const {

	if (empty())
		throw std::logic_error("the list is empty");
		
	return back_ptr->data;
}

template<typename T>
void dlinked_list<T>::pop_front() {

	if (empty())
		throw std::logic_error("the list is empty");
	
	if(cur_size == 1) {
		clear();
		return;
	}
	
	node* destroyer = front_ptr;
	front_ptr = front_ptr->next_ptr;
	delete destroyer;
	// we got at least two elements
	front_ptr->prev_ptr = nullptr;

	cur_size--;
}

template<typename T>
void dlinked_list<T>::pop_back() {

	if (empty())
		throw std::logic_error("the list is empty");
	
	if (cur_size == 1) {
		clear();
		return;
	}
	
	// we have at least two elements, move the tail one step backwards
	back_ptr = back_ptr->prev_ptr;
	// remove the last
	delete back_ptr->next_ptr;
	// mark it as a last element
	back_ptr->next_ptr = nullptr;
	
	cur_size--;
	fix_dummy();
}

template<typename T>
typename dlinked_list<T>::iterator dlinked_list<T>::find(const T& elem) const {

	node* it = front_ptr;

	while (it != dummy) {
		if (it->data == elem)
			return iterator(it);
		it = it->next_ptr;
	}
	
	return cend();
}

template<typename T>
typename dlinked_list<T>::iterator dlinked_list<T>::
	insert(const typename dlinked_list<T>::iterator& it, const T& el) {
	
	//insert after the last element
	if (it == begin() || cur_size < 2) {
		push_front(el);
		return iterator(front_ptr);
	}
	// create the new element, link it with his neighbors
	node* new_node = new node(el, it.node_ptr->prev_ptr, it.node_ptr);
	// link the element before iterator to the new one
	it.node_ptr->prev_ptr->next_ptr = new_node;
	// mark it as a element after the iterator
	it.node_ptr->prev_ptr = new_node;
	
	++cur_size; 
	return new_node;
}

template<typename T>
typename dlinked_list<T>::iterator dlinked_list<T>::
	remove(const typename dlinked_list<T>::iterator& it) {
	
	if (empty())
		throw std::logic_error("the list is empty");
	// there is no element after this iterator
	if (it == end())
		return end();
	//
	// first element case
	if (it.node_ptr == front_ptr) {
		pop_front();
		return iterator(back_ptr);	
	}
	//
	// last element case
	if (it.node_ptr == back_ptr) {
		pop_back();
		return iterator(back_ptr);
	}
	//
	// general case
	// link the previous with the next
	it.node_ptr->prev_ptr->next_ptr = it.node_ptr->next_ptr;
	// link next with the previous
	it.node_ptr->next_ptr = it.node_ptr->prev_ptr;
	// free the resources for the deleted box
	node* res = it.node_ptr->next_ptr;
	delete it.node_ptr;
	--cur_size;
	//
	return iterator(res);
}

template<typename T>
inline
bool dlinked_list<T>::empty() const {

	return cur_size == 0;
}

template<typename T>
inline
size_t dlinked_list<T>::size() const {

	return cur_size;
}

template<typename T>
void dlinked_list<T>::clear() {

	node* destroyer;
	// iterating through the elements
	while (front_ptr != nullptr && front_ptr != dummy) {
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
	fix_dummy();
}

template<typename T>
void dlinked_list<T>::print(std::ostream& os) const {
	
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
	while (it->next_ptr != dummy) {
		os << it->data << ", ";
		it = it->next_ptr;
	}
	os << it->data << " }" << std::endl;
}
} // namespace dsa
