/*
 * A basic linear data structure - singly linked list. With forward iterator iterator. STL friendly.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once
 
#include <stdexcept>        // exception types
#include <iosfwd>           // forward declarations of ostreams
#include <initializer_list> // initializer_list
#include <iterator>         // declaration of forward_iterator_tag

namespace dsa {
template<typename T>
class slinked_list {

private :
	// an inner representation of each "box" 
	struct node {

		T data;         // the actual stored data
		node* next_ptr; // a pointer to the next box
		
		// a simple constructor
		node(const T& ndata, node* pnext = nullptr) :
			data(ndata), next_ptr(pnext) { /**/ }
	};

private :
	/* private data members */
	node* front_ptr; // pointer to the first box
	node* back_ptr;  // pointer to the last box 
	size_t cur_size; // current amount of objects stored

public :
	/* object life cycle */
	slinked_list();
	slinked_list(std::initializer_list<T> il);
	slinked_list(const slinked_list& rhs);
	slinked_list& operator=(const slinked_list& rhs);
	~slinked_list();

public:
	
	typedef T value_type; // for std::back_inserter to work
	
	/* iterator */
	// very basic forward iterator
	class iterator {
		// only the container will have access to the private data of iterators
		friend class slinked_list<T>;
		
	private:

		node* node_ptr;

	public:
		// lets make our iterator more STL friendly 
		// see more at : https://en.cppreference.com/w/cpp/iterator/iterator_traits
		typedef iterator                  self_type;
		typedef T                         value_type;
		typedef T&                        reference;
		typedef T*                        pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef ptrdiff_t                 difference_type;
		// basic constructor
		iterator(node* n) : node_ptr(n) { }
		
	public:
		
		// access operators
		reference operator*() { return node_ptr->data; }
		const reference operator*() const { return node_ptr->data; } // for const iterators
		pointer operator->() { return &node_ptr->data; }
		
		// compare operators
		bool operator==(const iterator& rhs) const { return node_ptr == rhs.node_ptr; }
		bool operator!=(const iterator& rhs) const { return !(rhs == *this); }
		explicit operator bool() const { return node_ptr != nullptr; }
		
		// modifier operators
		self_type& operator++() {
			
			node_ptr = node_ptr->next_ptr;
			return *this;
		}

		self_type operator++(int) {

			self_type res(*this);
			++(*this);
			return res;
		}
	};
	
private:
	/* helpers */
	// copy all objects from another list
	void copy_from(const slinked_list& rhs);
	
public:
	/* interface */
	// frees the memory allocated for all list boxes
	void clear();
	
	// modifiers :
	// adds element at the end O(1)
	void push_back(const T& el);
	// adds element at the beginning O(1)
	void push_front(const T& el); 
	// lookup for the last element O(1)
	const T& back() const;
	T& back();
	// lookup for the first element O(1)
	const T& front() const;
	T& front();
	// remove the last element O(n)
	void pop_back();
	// remove the first element O(1)
	void pop_front();
	// inserts a new element, after the element pointed by iterator O(1)
	iterator insert_after(const iterator& it, const T& el);
	// removes the element after the element pointed by iterator O(1)
	iterator remove_after(const iterator& it);
	
	// getters :
	bool empty() const;
	size_t size() const;

	//simply outputs the contain of the list
	void print_elems(std::ostream& os) const;
	//searches the list for a given element, if found
	//returns an iterator to it, else iterator : end(), O(n)
	iterator find(const T& el) const;
	
	// iterators creation interface
	iterator begin() {

		return iterator(front_ptr);
	}

	iterator end() {

		return iterator(nullptr);
	}
	
	// constant iterator objects. they have limited usage
	// in our implementation, much better is to create
	// another class : const_iterator
	const iterator cbegin() const {

		return iterator(front_ptr);
	}

	const iterator cend() const {

		return iterator(nullptr);
	}
};

/* object life cycle */

template<typename T>
slinked_list<T>::slinked_list() : 
	front_ptr(nullptr), back_ptr(nullptr), cur_size(0) {

	//...
}
template<typename T>
slinked_list<T>::slinked_list(std::initializer_list<T> il) : slinked_list() {
	
	for(const T& el : il)
		push_back(el);
}

template<typename T>
slinked_list<T>::slinked_list(const slinked_list<T>& rhs) : 
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

/* helpers */

template<typename T>
void slinked_list<T>::copy_from(const slinked_list<T>& rhs) {

	if (rhs.empty())
		return;

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

/* interface */

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
		throw std::logic_error("the list is empty!");

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
		throw std::logic_error("the list is empty!");
		
	return back_ptr->data;
}

template<typename T>
void slinked_list<T>::pop_front() {

	if (empty())
		throw std::logic_error("the list is empty!");
	
	if(cur_size == 1) {
		// remove the first and zero the structure
		clean();
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
		throw std::logic_error("the list is empty!");
	
	if(cur_size == 1) {
		
		clean();
		return;
	}
	// we should get to the end, step by step
	node* it = front_ptr;

	while (it->next_ptr != back_ptr) {

		it = it->next_ptr;
	}
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
	insert_after(const slinked_list<T>::iterator& it, const T& el) {
	
	//insert after the last element
	if(it == end() || it.node_ptr == back_ptr) {
			
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
	remove_after(const slinked_list<T>::iterator& it) {
	
	if(empty())
		throw std::logic_error("empty queue!");
	// there is no element after this iterator
	if (it.node_ptr->next_ptr == nullptr)
			return end();
	// last element case
	if(it.node_ptr->next_ptr == back_ptr) {
			
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
void slinked_list<T>::print_elems(std::ostream& os) const {

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
} // namespace dsa
