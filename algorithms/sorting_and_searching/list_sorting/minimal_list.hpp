/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   minimal_list.hpp
 * @author Ivan Filipov
 * @date   12.2018
 * @brief  A minimal implementation of singly linked list,
 *         with support for Merge sort and Insertion sort.
 */

#pragma once
 
#include <stdexcept>        // exception types
#include <ostream>          // std::ostream
#include <initializer_list> // initializer_list

namespace dsa {
/**
 * @class minimal_list
 * @brief A singly-linked list with minimal interface.
 *
 * @tparam T: Type of stored elements.
 */
template<typename T>
class minimal_list {
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

	/* private data members */
	node*  front_ptr; //!< pointer to the first box
	node*  back_ptr;  //!< pointer to the last box 
	size_t cur_size;  //!< current amount of objects stored

public:
	/* object life cycle */
	/** Creates %minimal_list with no elements */
	minimal_list();
	
	/** Creates %minimal_list from initializer list */
	minimal_list(std::initializer_list<T> il);
	
	/** minimal_list is not copyable */
	minimal_list(const minimal_list& rhs) = delete;
	
	/** minimal_list is not copyable */
	minimal_list& operator=(const minimal_list& rhs) = delete;
	
	/** Frees all memory allocated. */
	~minimal_list();
	
private:
	/* helpers */
	/** frees the memory allocated for all list boxes */
	void clear();
	
	/**
	 * @brief merge sort helper: takes two sorted parts and returns their sorted union
	 * @param[in] first_ptr: pointer to the first part
	 * @param[in] second_ptr: pointer to the second part
	 * @retval pointer to the merged result
	 */
	node* merge(node* first_ptr, node* second_ptr);
	
	/**
	 * @brief Merge sort algorithm
	 * @param[in] head_ptr: pointer to the beginning of the list to be sorted.
	 * @param[in] size: amount of objects in the list
	 * @retval pointer to the sorted list
	 *
	 * Completely independent of the list implementation
	 * needs to know only where the list beginning is
	 */
	node* merge_sort(node* head_ptr, size_t size);
	
public:
	/* interface */
	// modifiers
	/** adds element at the end O(1) */
	void push_back(const T& el);
	
	/** adds element at the end O(1) */
	void push_front(const T& el); 
	
	/** Sorts the list using merge sort */
	void sort();
	
	/** Sorts the list using selection sort */
	void slow_sort();
	
	/** simply outputs the contain of the list */
	void print_elems(std::ostream& os) const;
	
	/** Check if the list is empty */
	bool empty() const { return cur_size == 0; }
};


template<typename T>
minimal_list<T>::minimal_list(): 
	front_ptr(nullptr), back_ptr(nullptr), cur_size(0) {
	//...
}

template<typename T>
minimal_list<T>::minimal_list(std::initializer_list<T> il): minimal_list() {
	
	for (const T& el: il)
		push_back(el);
}

template<typename T>
minimal_list<T>::~minimal_list() {

	clear();
}

template<typename T>
void minimal_list<T>::clear() {

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
void minimal_list<T>::push_front(const T& el) {

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
void minimal_list<T>::push_back(const T& el) {

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
void minimal_list<T>::print_elems(std::ostream& os) const {

	os << "content : ";
	
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

template<class T>
void minimal_list<T>::sort() {

	front_ptr = merge_sort(front_ptr, cur_size);
	
	// fixing the back pointer
	node* it = front_ptr;
	while (it->next_ptr != nullptr)
		it = it->next_ptr;
	back_ptr = it;
}

template<class T>
typename minimal_list<T>::node* minimal_list<T>::
	merge(typename minimal_list<T>::node* first_ptr,
		  typename minimal_list<T>::node* second_ptr) {
        
	if (!(first_ptr && second_ptr))
		throw std::logic_error("invalid pointers");
	// result's head
	node* head_ptr;
	// get the bigger element
	if (first_ptr->data < second_ptr->data) {
            head_ptr = first_ptr;
            first_ptr = first_ptr->next_ptr;
	} else {
		head_ptr = second_ptr;
		second_ptr = second_ptr->next_ptr;
	}
	// iterator for the result list
	node* res_ptr = head_ptr;
	// while there are elements in both list
	// get the bigger one, add it to the result
	while (first_ptr && second_ptr) {
		if (first_ptr->data < second_ptr->data) {
			head_ptr->next_ptr = first_ptr;
			first_ptr = first_ptr->next_ptr;
			head_ptr = head_ptr->next_ptr;
		} else {
			head_ptr->next_ptr = second_ptr;
			second_ptr = second_ptr->next_ptr;
			head_ptr = head_ptr->next_ptr;
		}
	}
	// get the left elements from both parts
	while (first_ptr) {
		head_ptr->next_ptr = first_ptr;
		first_ptr = first_ptr->next_ptr;
		head_ptr = head_ptr->next_ptr;
	}
	while (second_ptr) {
		head_ptr->next_ptr = second_ptr;
		second_ptr = second_ptr->next_ptr;
		head_ptr = head_ptr->next_ptr;
	}

	return res_ptr;
}

template<class T>
typename minimal_list<T>::node* minimal_list<T>::
	merge_sort(typename minimal_list<T>::node* head_ptr,
		       size_t size) {

	if (size == 1)
		return head_ptr;

	if (size == 2) {
		// swap elements if necessary 
		if (head_ptr->data > head_ptr->next_ptr->data) {
			node* temp = head_ptr;
			head_ptr = head_ptr->next_ptr;
			temp->next_ptr = head_ptr->next_ptr;
			head_ptr->next_ptr = temp;
		}
		return head_ptr;
	}

	size_t mid = size / 2;
	node* half_ptr = head_ptr;
	// going to the beginning of the second part
	while (--mid) {
		half_ptr = half_ptr->next_ptr;
	}
	// a pointer to the middle node
	node* mid_ptr = half_ptr->next_ptr;
	// broke into two lists
	half_ptr->next_ptr = nullptr;
	
	// sorting the two parts
	head_ptr = merge_sort(head_ptr, size / 2);
	mid_ptr = merge_sort(mid_ptr, size - size / 2);
	// merging them
	head_ptr = merge(head_ptr, mid_ptr);

	return head_ptr;
}

template<class T>
void minimal_list<T>::slow_sort() {
	
	if (empty()) return;
	
	node* res_head_ptr = front_ptr;
	node* res_back_ptr = front_ptr;
	node* it = front_ptr->next_ptr;
	res_head_ptr->next_ptr = nullptr;
	
	while (it) {
		// push front case
		if (res_head_ptr->data > it->data) {
			
			node* tmp = it;
			it = it->next_ptr;
			tmp->next_ptr = res_head_ptr;
			res_head_ptr = tmp;
			continue;
		}
		// iterator in result, pointing to the element, after which we are
		// going to insert the new one
		node* res_it = res_head_ptr;
		// search place
		while (res_it->next_ptr && it->data >= res_it->next_ptr->data)
			res_it = res_it->next_ptr;
		// push back case
		if (res_it == nullptr) {
			node* tmp = it;
			it = it->next_ptr;
			res_it->next_ptr = tmp;
			res_back_ptr = it;
			continue;
		}
		// insert case
		node* tmp = (res_it->next_ptr) ? res_it->next_ptr : nullptr;
		res_it->next_ptr = it;
		it = it->next_ptr;
		res_it->next_ptr->next_ptr = tmp;
		res_back_ptr = it;
	}
	// remember the result
	front_ptr = res_head_ptr;
	back_ptr  = res_back_ptr;
}
} // namespace dsa 
