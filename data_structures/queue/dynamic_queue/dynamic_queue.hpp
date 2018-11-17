/*
 * Implementation of dynamic queue data structure. Adapter on a singly linked list.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once
 
#include<stdexcept>

// the implementation is pretty close to the
// one of singly linked list...
namespace dsa {
template<typename T>
class dynamic_queue {

private:

	struct node {
		
		T data;
		node* next_ptr;

		node(const T& d, node* ptr = nullptr) : data(d), next_ptr(ptr) {}
	};

	node* front_ptr;
	node* rear_ptr;
	size_t cur_size;
	
public:

	//BIG FOUR
	dynamic_queue();
	dynamic_queue(const dynamic_queue& rhs);
	dynamic_queue& operator=(const dynamic_queue& rhs);
	~dynamic_queue();

private:

	//HELP FUNCTIONS
	void copy_from(const dynamic_queue& rhs);
	
public:

	//INTERFACE

	// access for first / fast member
	T& front();
	const T& front()const;

	T& back();
	const T& back() const;

	// add / remove
	void push(const T& el);
	void pop();

	bool empty() const;
	size_t size() const;
	
	void clean();
};

template<class T>
dynamic_queue<T>::dynamic_queue() : front_ptr(nullptr), rear_ptr(nullptr), cur_size(0) {
	/*...*/
}

template<class T>
dynamic_queue<T>::dynamic_queue(const dynamic_queue<T>& rhs): dynamic_queue() {

	copy_from(rhs);
}

template<class T>
dynamic_queue<T>& dynamic_queue<T>::operator=(const dynamic_queue<T>& rhs) {

	if (this != &rhs) {
		clean();
		copy_from(rhs);
	}

	return *this;
}

template<class T>
dynamic_queue<T>::~dynamic_queue() {

	clean();
}

template<class T>
void dynamic_queue<T>::clean() {
	//iterating trough all elements
	node * destroyer ;
	
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
		node* copier = front_ptr;

		while (to_copy->next_ptr != 0) {
			to_copy = to_copy->next_ptr;

			copier->next_ptr = new node(to_copy->data);
			copier = copier->next_ptr;
		}
		
		rear_ptr = copier;
		cur_size = rhs.cur_size;
	} catch (std::bad_alloc &) {
		clean();
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
