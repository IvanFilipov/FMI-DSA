/*
* This is template implementation of Deque with (1) random access.
* This file is part of the "Data structures and algorithms" course. FMI 2018/19
*
* Author : Plamen Minev
*/
#pragma once

#include <stdexcept>

static const size_t SIZE_OF_CHUNK = 16;
static const size_t SIZE_GROWING_STEP = 2;

namespace dsa {

template<typename T>
class deque {

private:

	// Using matrix of elements will give us the opportunity
	// to have O(1) random access
	T** elements;
	size_t front_el_index;
	size_t back_el_index;
	size_t cur_size;
	size_t chunks_used;
	size_t chunks_capacity;

public:
	deque();
	deque(const deque& rhs);
	deque& operator=(const deque& rhs);
	~deque();

private:
	void copy_from(const deque& rhs);
	void resize();

public:

	// INTERFACE
	T& front();
	const T& front() const;

	T& back();
	const T& back() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	void push_front(const T& el);
	void pop_front();

	void push_back(const T& el);
	void pop_back();

	bool empty() const;
	size_t size() const;

	void clean();
};

template<typename T>
deque<T>::deque()
	: elements(nullptr)
	, front_el_index(0)
	, back_el_index(0)
	, cur_size(0)
	, chunks_used(0)
	, chunks_capacity(0) {
	elements = new T*[SIZE_GROWING_STEP];
	elements[0] = new T[SIZE_OF_CHUNK];
	chunks_capacity = SIZE_GROWING_STEP;
}

template<typename T>
deque<T>::deque(const deque<T>& rhs)
	: deque()
{
	copy_from(rhs)
}

template<typename T>
deque<T>& deque<T>::operator=(const deque<T>& rhs) {
	if (this != &rhs)
	{
		clean();
		copy_from(rhs);
	}

	return *this;
}

template<typename T>
deque<T>::~deque() {
	clean();
}

template<typename T>
void deque<T>::copy_from(const deque<T>& rhs) {
	this->elements = new node*[rhs.chunks_capacity];
	for (size_t i = 0; i < rhs.chunks_used; i++)
	{
		this->elements[i] = new node[SIZE_OF_CHUNK];
		for (size_t j = 0; j < SIZE_OF_CHUNK; j++)
		{
			this->elements[i][j] = rhs.elements[i][j]
		}
	}

	for (size_t i = rhs.chunks_used; i < rhs.chunks_capacity; i++)
	{
		this->elements = nullptr;
	}

	this->front_el_index = rhs.front_el_index;
	this->back_el_index = rhs.back_el_index;
	this->cur_size = rhs.cur_size;
	this->chunks_used = rhs.chunks_used;
	this->chunks_capacity = rhs.chunks_capacity;
}

template<typename T>
void deque<T>::resize() {
	T** new_chunks = new T*[chunks_capacity*SIZE_GROWING_STEP];

	for (size_t i = 0; i < chunks_capacity; i++)
	{
		new_chunks[i] = elements[i];
	}

	chunks_capacity *= SIZE_GROWING_STEP;
	delete[] elements;
	elements = new_chunks;
}

template<typename T>
void deque<T>::clean() {
	for (size_t i = 0; i < chunks_used; i++)
	{
		delete[] elements[i];
	}

	delete[] elements;

	this->front_el_index = 0;
	this->back_el_index = 0;
	this->cur_size = 0;
	this->chunks_used = 0;
	this->chunks_capacity = 0;
}

template<typename T>
T& deque<T>::front() {
	return const_cast<T&>(
		static_cast<const deque<T>&>(*this).front()
		);
}

template<typename T>
const T& deque<T>::front() const {
	return elements[0][front_el_index];
}

template<typename T>
T& deque<T>::back() {
	return const_cast<T&>(
		static_cast<const deque<T>&>(*this).back()
		);
}

template<typename T>
const T& deque<T>::back() const {
	return elements[chunks_used - 1][back_el_index];
}

template<typename T>
T& deque<T>::operator[](size_t index) {
	return const_cast<T&>(
		static_cast<const deque<T>&>(*this).operator[](index)
		);
}

template<typename T>
const T& deque<T>::operator[](size_t index) const {
	if (index >= cur_size) {
		throw std::out_of_range("Invalid index!");
	}

	size_t chunk_index = (front_el_index + index - 1) / SIZE_OF_CHUNK;
	size_t element_index = (front_el_index + index - 1) % SIZE_OF_CHUNK;

	return elements[chunk_index][element_index];

}

template<typename T>
void deque<T>::push_front(const T& el) {
	if (cur_size == 0) {
		return;
	}

	if (front_el_index != 0) {
		elements[0][front_el_index--] = el;
		cur_size++;
		return;
	}

	if (chunks_used == chunks_capacity)
	{
		resize();
	}

	// Move the elements with 1 chunk down
	T* empty_chunk = elements[chunks_capacity - 1];
	for (int i = chunks_capacity - 1; i > 0; i--)
	{
		elements[i] = elements[i - 1];
	}

	elements[0] = empty_chunk = new T[SIZE_OF_CHUNK];
	elements[0][SIZE_OF_CHUNK - 1] = el;
	front_el_index = SIZE_OF_CHUNK - 1;
	cur_size++;
	chunks_used++;

}

template<typename T>
void deque<T>::pop_front() {
	if (cur_size == 0) {
		return;
	}

	if (front_el_index != SIZE_OF_CHUNK - 1) {
		cur_size--;
		front_el_index++;
		return;
	}

	delete[] elements[0];
	for (size_t i = 1; i < chunks_capacity; i++)
	{
		elements[i - 1] = elements[i];
	}
	elements[chunks_used--] = nullptr;
	front_el_index = 0;
	cur_size--;
}

template<typename T>
void deque<T>::push_back(const T& el) {
	if (back_el_index != SIZE_OF_CHUNK) {
		size_t last_used_chunk = cur_size / SIZE_OF_CHUNK;
		elements[last_used_chunk][back_el_index++] = el;
		cur_size++;
		return;
	}

	if (chunks_used == chunks_capacity-1) {
		resize();
	}

	elements[++chunks_used] = new T[SIZE_OF_CHUNK];
	back_el_index = 0;
	elements[chunks_used][back_el_index++] = el;
	cur_size++;
}

template<typename T>
void deque<T>::pop_back() {
	if (back_el_index != 0) {
		back_el_index--;
		cur_size--;
		return;
	}

	delete[] elements[--chunks_used];
	elements[chunks_used] = nullptr;
	back_el_index = SIZE_OF_CHUNK - 1;
	cur_size--;
}

template<typename T>
bool deque<T>::empty() const {
	return cur_size == 0;
}

template<typename T>
size_t deque<T>::size() const {
	return cur_size;
}

} // namespace dsa
