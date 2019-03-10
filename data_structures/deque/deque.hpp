/*
* This is template implementation of Deque with (1) random access.
* This file is part of the "Data structures and algorithms" course. FMI 2018/19
*
* Author : Plamen Minev
*/
#pragma once
#include "../dynamic_array/dynamic_array.hpp"

static const size_t SIZE_OF_CHUNK = 16;
static const size_t SIZE_GROWING_STEP = 2;

namespace sda {

template<typename T>
class deque {

private:
	struct node {
		T data;
		node* next_ptr;

		node(const T& d, node* ptr = nullptr)
			: data(d)
			, next_ptr(ptr)
		{}
	};

	// Using matrix of elements will give us the opportunity
	// to have O(1) random access
	node** elements;
	node* front_ptr;
	node* back_ptr;
	size_t cur_size;
	size_t capacity;

public:
	deque();
	deque(const deque& rhs);
	deque& operator=(const deque& rhs);
	~deque;

private:
	void copy_from(const deque& rhs);

public:

	// INTERFACE

	T& back();
	const T& back() const;

	T& back();
	const T& back() const;

	T& operator=(size_t index);
	const T& operator=(size_t index) const;

	void push_front(const T& el);
	void pop_front();

	void push_back(const T& el);
	void pop_back();

	bool empty() const;
	size_t size() const;

	void clean();
};
}