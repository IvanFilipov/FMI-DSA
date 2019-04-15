/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   dynamic_stack.hpp
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  Implementation of the stack data structure as 
 *         an adapter on singly linked list.
 * @see https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
 */

#pragma once 
 
#include <stdexcept> // exception types

namespace dsa {
/**
 * @class dynamic_stack
 * @brief Stores elements in LIFO style.
 * @tparam T: type of elements stored
 */
template<class T>
class dynamic_stack {
private:
	/**
	 *  @struct node
	 *  @brief  An inner representation of each "box".
	 */ 
	struct node {
		T     data;     //!< the actual stored data
		node* next_ptr; //!< a pointer to the next box
		/** Creates an node by given data. */
		node(const T& ndata, node* next_ptr = nullptr) :
			data(ndata), next_ptr(next_ptr) { /**/ }
	};

private:
	/* private data members */
	size_t cur_size; //!< current amount of objects in the stack
	node* top_ptr;   //!< pointer to the top of the stack

public:
	/* object life cycle */
	/** Creates %dynamic_stack with no elements */
	dynamic_stack();
	
	/**
	  *  @brief     %dynamic_stack copy constructor.
	  *  @param[in] rhs: A %dynamic_stack of identical element type, from which to copy.
	  */
	dynamic_stack(const dynamic_stack& rhs);
	
	/**
	  *  @brief     %dynamic_stack assignment operator.
	  *  @param[in] rhs: A %dynamic_stack of identical element type, from which to copy.
	  */
	dynamic_stack& operator=(const dynamic_stack& rhs);
	
	/** Frees all memory allocated. */
	~dynamic_stack();

private:
	/* helpers */
	/** 
	  *  @brief     copies all elements for another stack
	  *  @param[in] rhs: stack from which to copy.
	  */
	void copy_from(const dynamic_stack& rhs);
	
public:
	/* interface */
	/**
	 * @brief  get the top element of the stack
	 * @retval Reference to the first element.
	 * @throw  std::logic_error if stack is empty
	 * Time complexity O(1).
	 */
	T& top();
	
	/**
	 * @brief  get the top element of the stack
	 * @retval Read-only reference to the top element.
	 * @throw  std::logic_error if stack is empty
	 * Time complexity O(1).
	 */
	const T& top() const;

	/**
	 * @brief         Push a new element on the top of the stack.
	 * @param[in] el: Value to be inserted
	 * Time complexity O(1).
	 */
	void push(const T& el);
	
	/**
	 * @brief Pop the top element of the stack.
	 * @throw std::logic_error if the stack is empty
	 * Time complexity O(1).
	 */
	void pop();
	
	/**
	 * @brief  Checks if the %dynamic_stack is empty.
	 * @retval boolean: whether the dynamic_stack is empty.
	 * Time complexity O(1).
	 */
	bool empty() const;
	
	/**
	 * @brief Get the current size of the stack.
 	 * @retval Current size.
 	 * Time complexity O(1).
	 */
	size_t size() const;
	
	/** Frees the resources for the stack. Time complexity liner in the count of the elements. */
	void clear();
};

template<class T>
dynamic_stack<T>::dynamic_stack(): cur_size(0), top_ptr(nullptr) {
	/*...*/
}

template<class T>
dynamic_stack<T>::~dynamic_stack() {

	clear();
}

template<class T>
dynamic_stack<T>::dynamic_stack(const dynamic_stack<T>& rhs): dynamic_stack() {

	copy_from(rhs);
}

template<class T>
dynamic_stack<T>& dynamic_stack<T>::operator=(const dynamic_stack<T>& rhs) {

	if (this != &rhs) {
		clear();
		copy_from(rhs);
	}

	return *this;
}

template<class T>
void dynamic_stack<T>::copy_from(const dynamic_stack<T>& rhs) {
 
	if (rhs.empty()) return;

	try {
		// copy other's top
		top_ptr = new node(rhs.top_ptr->data);
		// iterate through the two stacks
		node* ours = top_ptr;
		node* theirs = rhs.top_ptr->next_ptr;
		// until end of other is reach, copy one element
		while (theirs != nullptr) {
			ours->next_ptr = new node(theirs->data);
			ours = ours->next_ptr;
			theirs = theirs->next_ptr;
		}
		cur_size = rhs.cur_size;
	} catch (std::bad_alloc&) {
		// if exception is caught, clear all the memory allocated
		clear();
		throw; // re-throw the same exception
	}
}

template<class T>
void dynamic_stack<T>::clear() {

	node* temp;

	while (top_ptr != nullptr) {
		temp = top_ptr;
		top_ptr = top_ptr->next_ptr;
		delete temp;
	}

	cur_size = 0;
	top_ptr  = nullptr;
}

template<class T>
void dynamic_stack<T>::push(const T& el) {

	node* new_el = new node(el, top_ptr);
	top_ptr = new_el;
	cur_size++;
}

template<class T>
void dynamic_stack<T>::pop() {

	if (empty())
		throw std::logic_error("the stack is empty !");

	node* temp = top_ptr;
	top_ptr = top_ptr->next_ptr;
	delete temp;

	cur_size--;
}


template<class T>
inline
bool dynamic_stack<T>::empty() const {

	return cur_size == 0;
}

template<class T>
const T& dynamic_stack<T>::top() const {

	if (empty()) throw std::logic_error("the stack is empty");

	return top_ptr->data;
}

template<class T>
T& dynamic_stack<T>::top() {

	return const_cast<T&>(
		static_cast<const dynamic_stack<T>&>(*this).top()			
	);	
}

template<class T>
inline
size_t dynamic_stack<T>::size() const {

	return cur_size;
}
} // namespace dsa
