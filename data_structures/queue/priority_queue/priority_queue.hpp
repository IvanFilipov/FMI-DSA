/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   priority_queue.hpp
 * @author Gratsiela Gancheva 
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  An advanced linear data structure - priority queue.
 *         Implemented as a binary heap.
 * @see https://en.wikipedia.org/wiki/Priority_queue
 * @see https://en.wikipedia.org/wiki/Binary_heap
 */
 
#pragma once

#include <utility>    // std::swap
#include <functional> // std::less
#include "../../dynamic_array/dynamic_array.hpp" // dsa::dynamic_array

using dsa::dynamic_array;

namespace dsa {
/**
 * @class priority_queue
 * @brief Stores elements in FIFO style, each element is associated with priority.
          Elements with higher priority are served before elements with lower priority.
 * @tparam T: type of elements stored
 * @tparam Compare: comparator function to be used for comparing priorities. [less function by default]
 */
template<typename T, typename Compare = std::less<T>> // use std::less as a default compare function
class priority_queue {
private:
	/* private data members */
	dynamic_array<T> data; //!< the heap is implemented on array 
	Compare          cmp;  //!< compare function
public:	
	/* object life cycle */
	// no dynamic memory to handle, so no need for "the big four" -
	// we are OK with the compile-generated
	/** Creates %priority_queue with no elements */
	priority_queue() = default;
	
	/**
	  *  @brief     Creates %priority_queue with no elements
	  *  @param[in] cmp: compare function to be used.
	  */
	priority_queue(const Compare& cmp);
	
	/**
	  *  @brief     %priority_queue copy constructor.
	  *  @param[in] rhs: A %priority_queue of identical element type, from which to copy.
	  */
	priority_queue(const priority_queue&) = default;
	
	/**
	  *  @brief     %priority_queue assignment operator.
	  *  @param[in] rhs: A %priority_queue of identical element type, from which to copy.
	  */
	priority_queue& operator=(const priority_queue&) = default;
	
	/** Frees all memory allocated. */
	~priority_queue() = default;

private :
	/* helpers */
	/// Returns the left child of an element on an index
	size_t get_left_child_ind(size_t index) const;
	/// Returns the right child of an element on an index
	size_t get_right_child_ind(size_t index) const;
	/// Returns the parent of an element on an index, -1 if the element has no parent
	int get_parent_ind(size_t index) const;
	/// Sifts an element down
	void sift_down(size_t index);
	/// Sifts an element up
	void sift_up(size_t index);

public:
	/* interface */
	/**
	 * @brief  Get the element with the highest priority.
	 * @retval Read-only reference to the element.
	 * @throw  std::logic_error if queue is empty
	 * Time complexity O(1).
	 */
	const T& top() const;
	
	/**
	 * @brief         Push a new element into the queue.
	 * @param[in] el: Value to be inserted
	 * Time complexity O(logn).
	 */
	void push(const T& el);
	
   /**
	 * @brief Pop the element with the highest priority.
	 * @throw std::logic_error if the queue is empty
	 * Time complexity O(logn).
	 */
	void pop();
	
	/**
	 * @brief  Checks if the %priority_queue is empty.
	 * @retval boolean: whether the priority_queue is empty.
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

template<typename T, typename Compare>
priority_queue<T, Compare>::priority_queue(const Compare& cmp): cmp(cmp) {
	//...
}

template<typename T, typename Compare>
inline
size_t priority_queue<T, Compare>::get_left_child_ind(size_t index) const {
	
	return index * 2 + 1;
}

template<typename T, typename Compare>
inline
size_t priority_queue<T, Compare>::get_right_child_ind(size_t index) const {
	
	return index * 2 + 2;
}

template<typename T, typename Compare>
inline
int priority_queue<T, Compare>::get_parent_ind(size_t index) const {
	
	return (index) ? (index - 1) / 2 : -1 ;
}

template<typename T, typename Compare>
void priority_queue<T, Compare>::sift_down(size_t index) {
	
	if (empty()) return;

	T el_to_swap = data[index];
	size_t left_child_ind = get_left_child_ind(index);

	size_t size = data.size();
	// sift until wanted position is reached
	while (left_child_ind < size) {
		int right_child_ind = get_right_child_ind(index);
		// with which child to swap
		if (left_child_ind < size - 1 && cmp(data[left_child_ind] , data[right_child_ind]))
			left_child_ind = right_child_ind;
		// the element is on its position
		if (!cmp(el_to_swap, data[left_child_ind]))
			break;
		// go down one level more 
		data[index] = data[left_child_ind];
		index = left_child_ind;
		left_child_ind = get_left_child_ind(left_child_ind);
	}

	data[index] = el_to_swap;
}

template<typename T, typename Compare>
void priority_queue<T, Compare>::sift_up(size_t index) {
	
	T el_to_swap = data[index];
	int cur_parent = get_parent_ind(index);

	while (cur_parent >= 0 && cmp(data[cur_parent], el_to_swap)) {
		data[index] = data[cur_parent];
		index = cur_parent;
		cur_parent = get_parent_ind(index);
	}
	data[index] = el_to_swap;
}

template<typename T, typename Compare>
const T& priority_queue<T, Compare>::top() const {
	
	return data.front();
}

template<typename T, typename Compare>
void priority_queue<T, Compare>::push(const T& el) {
	
	data.push_back(el);
	sift_up(data.size() - 1);
}

template<typename T, typename Compare>
void priority_queue<T, Compare>::pop() {
	
	std::swap(data.front(), data.back());
	data.pop_back();
	sift_down(0);
}

template<typename T, typename Compare>
void priority_queue<T, Compare>::clear() {
	
	data.clear();
}

template<typename T, typename Compare>
inline bool priority_queue<T, Compare>::empty() const {
	
	return data.empty();
}

template<typename T, typename Compare>
inline size_t priority_queue<T, Compare>::size() const {
	
	return data.size();
}
} // namespace dsa
