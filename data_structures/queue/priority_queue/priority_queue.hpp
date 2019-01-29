/*
 * An advanced linear data structure - priority queue. Using heap on array.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author    : Gratsiela Gancheva
 * Co-author : Ivan Filipov	
 */
 
#pragma once

#include <utility>    // std::swap
#include <functional> // std::less
#include "../../dynamic_array/dynamic_array.hpp" // dsa::dynamic_array

using dsa::dynamic_array;

// first template argument is the type of stored objects 
// the second one is a function to be used while comparing elements
namespace dsa {
template<typename T, typename Compare = std::less<T>> // use std::less as a default compare function
class priority_queue {
	
private :
	/* private data members */
	dynamic_array<T> data; // heap on array 
	Compare          cmp; // compare function
	
public :	
	/* object life cycle */
	// no dynamic memory to handle, so no need for big 4
	priority_queue() = default;
	priority_queue(const Compare& cmp); // additional constructor with parameter compare function
	// we are OK with the compile-generated
	priority_queue(const priority_queue&)            = default;
	priority_queue& operator=(const priority_queue&) = default;
	~priority_queue()                                = default;

private :
	/* helpers */
	/// Return left child of this index
	size_t get_left_child_ind(size_t index) const;
	/// Return right child of this index
	size_t get_right_child_ind(size_t index) const;
	/// Return parent of this index, -1 if the element has no parent
	int get_parent_ind(size_t index) const;
	/// Sift element at index down
	void sift_down(size_t index);
	/// Sift element at index up
	void sift_up(size_t index);

public:
	/* interface */
	/// Access top element, but don't change it. O(1) time complexity
	const T& top() const;
	/// Insert element O(logn) time complexity
	void push(const T& el);
	/// Remove top element O(logn) time complexity
	void pop();
	/// Clear content
	void clear();
	/// Test whether container is empty
	bool empty() const;
	/// Return size
	size_t size() const;
};

template<typename T, typename Compare>
priority_queue<T, Compare>::priority_queue(const Compare& cmp) : cmp(cmp) {
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
	
	if (empty())
		return;

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
