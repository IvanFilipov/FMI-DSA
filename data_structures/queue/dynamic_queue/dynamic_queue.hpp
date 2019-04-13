/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   dynamic_queue.hpp
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  Implementation of the queue data structure as 
 *         an adapter on singly linked list.
 * @see https://en.wikipedia.org/wiki/Queue_(abstract_data_type)
 */

#pragma once
 
#include <stdexcept> // exception types

namespace dsa {
/**
 * @class dynamic_queue
 * @brief Stores elements in FIFO style.
 * @tparam T: type of elements stored
 */
template<typename T>
class dynamic_queue {
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
	node*  front_ptr; //!< pointer to the front element
	node*  rear_ptr;  //!< pointer to the back element
	size_t cur_size;  //!< current amount of objects in the queue

public:
	/* object life cycle */
	/** Creates %dynamic_queue with no elements */
	dynamic_queue();
	
	/**
	  *  @brief     %dynamic_queue copy constructor.
	  *  @param[in] rhs: A %dynamic_queue of identical element type, from which to copy.
	  */
	dynamic_queue(const dynamic_queue& rhs);
	
	/**
	  *  @brief     %dynamic_queue assignment operator.
	  *  @param[in] rhs: A %dynamic_queue of identical element type, from which to copy.
	  */
	dynamic_queue& operator=(const dynamic_queue& rhs);
	
	/** Frees all memory allocated. */
	~dynamic_queue();

private:
	/* helpers */
	/** 
	  *  @brief     copies all elements for another queue
	  *  @param[in] rhs: queue from which to copy.
	  */
	void copy_from(const dynamic_queue& rhs);
	
public:
	/* interface */
	/**
	 * @brief  get the front element of the queue
	 * @retval Reference to the front element.
	 * @throw  std::logic_error if queue is empty
	 * Time complexity O(1).
	 */
	T& front();
	
	/**
	 * @brief  get the front element of the queue
	 * @retval Read-only reference to the front element.
	 * @throw  std::logic_error if queue is empty
	 * Time complexity O(1).
	 */
	const T& front()const;
	
	/**
	 * @brief  get the back element of the queue
	 * @retval Reference to the back element.
	 * @throw  std::logic_error if queue is empty
	 * Time complexity O(1).
	 */
	T& back();
	
	/**
	 * @brief  get the back element of the queue
	 * @retval Read-only reference to the back element.
	 * @throw  std::logic_error if queue is empty
	 * Time complexity O(1).
	 */
	const T& back() const;

	/**
	 * @brief         Push a new element at the back of the queue.
	 * @param[in] el: Value to be inserted
	 * Time complexity O(1).
	 */
	void push(const T& el);
	
	/**
	 * @brief Pop the front element of the queue.
	 * @throw std::logic_error if the queue is empty
	 * Time complexity O(1).
	 */
	void pop();

	/**
	 * @brief  Checks if the %dynamic_queue is empty.
	 * @retval boolean: whether the dynamic_queue is empty.
	 * Time complexity O(1).
	 */
	bool empty() const;
	
	/**
	 * @brief Get the current size of the queue.
 	 * @retval Current size.
 	 * Time complexity O(1).
	 */
	size_t size() const;
	
	/** Frees the resources for the queue. Time complexity liner in the count of the elements. */
	void clear();
};

template<class T>
dynamic_queue<T>::dynamic_queue(): 
	front_ptr(nullptr), rear_ptr(nullptr), cur_size(0) {
	/*...*/
}

template<class T>
dynamic_queue<T>::dynamic_queue(const dynamic_queue<T>& rhs): dynamic_queue() {

	copy_from(rhs);
}

template<class T>
dynamic_queue<T>& dynamic_queue<T>::operator=(const dynamic_queue<T>& rhs) {

	if (this != &rhs) {
		clear();
		copy_from(rhs);
	}

	return *this;
}

template<class T>
dynamic_queue<T>::~dynamic_queue() {

	clear();
}

template<class T>
void dynamic_queue<T>::clear() {
	//iterating trough all elements
	node* destroyer ;
	
	while (front_ptr != nullptr) {
		//taking the first one
		destroyer = front_ptr;		
		//setting the new first one to the one linked with the old first one
		front_ptr = front_ptr->next_ptr;
		//the one pointer by destroyer will be deleted
		delete destroyer;
	}

	rear_ptr = nullptr;
	front_ptr = nullptr;
	cur_size = 0;
}

template<class T>
void dynamic_queue<T>::copy_from(const dynamic_queue<T>& rhs) {
	
	if (rhs.empty())
		return;

	try {
		front_ptr = new node(rhs.front_ptr->data);

		node* to_copy = rhs.front_ptr;
		node* copier  = front_ptr;

		while (to_copy->next_ptr != 0) {
			to_copy = to_copy->next_ptr;
			copier->next_ptr = new node(to_copy->data);
			copier = copier->next_ptr;
		}
		
		rear_ptr = copier;
		cur_size = rhs.cur_size;
	} catch (std::bad_alloc &) {
		clear();
		throw;
	}
}

template<class T>
void dynamic_queue<T>::push(const T& el) {

	if (empty()) {
		front_ptr = new node(el);
		rear_ptr = front_ptr;
		cur_size++;
		return;
	}

	node* new_elem = new node(el);

	rear_ptr->next_ptr = new_elem;
	rear_ptr = rear_ptr->next_ptr;
	cur_size++;
}

template<class T>
void dynamic_queue<T>::pop() {

	if (empty())
		throw std::logic_error("empty dynamic_queue!");
	
	node* destroyer = front_ptr;

	front_ptr = front_ptr->next_ptr;

	delete destroyer;
	cur_size--;
}

template<class T>
const T& dynamic_queue<T>::front() const {

	if (empty())
		throw std::logic_error("empty dynamic_queue!");
	 
	return front_ptr->data;
}

template<class T>
T& dynamic_queue<T>::front() {

	return const_cast<T&>(
		static_cast<const dynamic_queue<T>&>(*this).front()				
	);
}

template<class T>
const T& dynamic_queue<T>::back() const { 

	if (empty())
		throw std::logic_error("empty!");
	 
	return rear_ptr->data;
}

template<class T>
T& dynamic_queue<T>::back() {

	return const_cast<T&>(
		static_cast<const dynamic_queue<T>&>(*this).back()				
	);
}

template<class T>
inline
bool dynamic_queue<T>::empty() const {

	return cur_size == 0;
}

template<class T>
inline
size_t dynamic_queue<T>::size() const {

	return cur_size;
}
} // namespace dsa
