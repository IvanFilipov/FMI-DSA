#pragma once
#include"DynamicArray.h"

template<class T, class Compare>
class PriorityQueue
{
public:
	PriorityQueue(const Compare comp);
	~PriorityQueue();

public:
	/// Test whether container is empty
	bool empty() const;

	/// Return size
	size_t size() const;

	/// Access top element
	T& top();
	const T& top() const;

	/// Insert element
	void push(const T& element);

	/// Remove top element
	void pop();

	/// Clear content
	void clear();

private:
	/// Return left child of this index
	int left(size_t index) const;

	/// Return right child of this index
	int right(size_t index) const;

	/// Return parent of this index
	int parent(size_t index) const;

	/// Sift element at index down
	void siftDown(size_t index);

	/// Sift element at index up
	void siftUp(size_t index);
private:
	DynamicArray<T> data;
	Compare comp;
};

#include"PriorityQueue.hpp"

