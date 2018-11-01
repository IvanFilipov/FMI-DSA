/*
 * Implementation of the stack data structure as adapter on singly linked list.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
#include <stdexcept> // exception types

namespace dsa {
template<class T>
class dynamic_stack {
	
private:
	// representation of each box
	struct node {

		T data;
		node * next_ptr;
		node(const T& d, node* ptr = nullptr) : data(d), next_ptr(ptr) {}
	};
	/* private data members */
	size_t cur_size; // amount of objects in the stack
	node* top_ptr;   // the top of the stack

public:
	/* object life cycle */
	dynamic_stack();
	dynamic_stack(const dynamic_stack& rhs);
	dynamic_stack& operator=(const dynamic_stack& rhs);
	~dynamic_stack();

private:
	/* helpers */
	void copy_from(const dynamic_stack& rhs);
	void clean();

public:
	/* interface */
	
	// element access ( only the top is reachable. complexity O(1)
	//letting us to "see" the top or to "adjust" it
	T& top();
	const T& top() const;

	// modifiers 
	// adding a new element on the top of the stack. O(1)
	void push(const T& el);
	// remove the top element of the stack. O(1)
	void pop();
	// getters
	bool empty() const;
	size_t size() const;
};

// implementation below is almost the same as
// the one for singly linked list

template<class T>
dynamic_stack<T>::dynamic_stack() : cur_size(0), top_ptr(nullptr) {
	/*...*/
};

template<class T>
dynamic_stack<T>::~dynamic_stack() {

	clean();
}

template<class T>
dynamic_stack<T>::dynamic_stack(const dynamic_stack<T>& rhs) :cur_size(0), top_ptr(nullptr) {

	copy_from(rhs);
};

template<class T>
dynamic_stack<T>& dynamic_stack<T>::operator=(const dynamic_stack<T>& rhs) {

	if (this != &rhs){

		clean();
		copy_from(rhs);
	}

	return *this;
}

template<class T>
void dynamic_stack<T>::copy_from(const dynamic_stack<T>& rhs) {
 
	if (rhs.empty())
		return;

	try{
		top_ptr = new node(rhs.top_ptr->data);
		
		node* ours = top_ptr;
		node* theirs = rhs.top_ptr->next_ptr;

		while (theirs != nullptr){

			ours->next_ptr = new node(theirs->data);
			
			ours = ours->next_ptr;
			theirs = theirs->next_ptr;
		}

		cur_size = rhs.cur_size;
	} catch (std::bad_alloc&) {

		clean();
		throw;
	}
}

template<class T>
void dynamic_stack<T>::clean() {

	node* temp;

	while (top_ptr != nullptr) {

		temp = top_ptr;
		top_ptr = top_ptr->next_ptr;
		delete temp;
	}

	cur_size = 0;
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
