
#include<iostream>
template<class T, class Compare>
PriorityQueue<T, Compare>::PriorityQueue(const Compare comp)
	:data(), comp(comp)
{}

template<class T, class Compare>
PriorityQueue<T, Compare>::~PriorityQueue()
{
	clear();
}

/// Test whether container is empty
template<class T, class Compare>
inline bool PriorityQueue<T, Compare>::empty() const
{
	return data.empty();
}

/// Return size
template<class T, class Compare>
inline size_t PriorityQueue<T, Compare>::size() const
{
	return data.size();
}

/// Access top element
template<class T, class Compare>
T&  PriorityQueue<T, Compare>::top()
{
	return data.front();
}

template<class T, class Compare>
const T&  PriorityQueue<T, Compare>::top() const
{
	return data.front();
}

/// Insert element
template<class T, class Compare>
void  PriorityQueue<T, Compare>::push(const T& element)
{
	data.push_back(element);
	siftUp(data.size() - 1);
}

/// Remove top element
template<class T, class Compare>
void  PriorityQueue<T, Compare>::pop()
{
	swap(data.front(), data.back());
	data.pop_back();
	siftDown(0);
}

/// Clear content
template<class T, class Compare>
void  PriorityQueue<T, Compare>::clear()
{
	data.clear();
}

/// Return left child of this index
template<class T, class Compare>
int  PriorityQueue<T, Compare>::left(size_t index) const
{
	return index * 2 + 1;
}

/// Return right child of this index
template<class T, class Compare>
int  PriorityQueue<T, Compare>::right(size_t index) const
{
	return index * 2 + 2;
}

/// Return parent of this index
template<class T, class Compare>
int  PriorityQueue<T, Compare>::parent(size_t index) const
{
	return (!index) ? -1 : (index - 1) / 2;
}

/// Sift element at index down
template<class T, class Compare>
void  PriorityQueue<T, Compare>::siftDown(size_t index)
{
	if (empty())
		return;

	T elementToSwap = data[index];
	int leftChild = left(index);

	size_t size = data.size();
	while (leftChild <  size)
	{
		int rightChild = right(index);
		if (leftChild < size - 1 && comp(data[leftChild] , data[rightChild]) > 0)
			leftChild = rightChild;
		
		if (elementToSwap < data[leftChild])
			break;

		data[index] = data[leftChild];
		index = leftChild;
		leftChild = left(leftChild);
	}

	data[index] = elementToSwap;
}

/// Sift element at index up
template<class T, class Compare>
void  PriorityQueue<T, Compare>::siftUp(size_t index)
{
	T elementToSwap = data[index];
	int currentParent = parent(index);

	while (currentParent >= 0 && comp(data[currentParent],elementToSwap) > 0 )
	{
		data[index] = data[currentParent];
		index = currentParent;
		currentParent = parent(index);
	}
	data[index] = elementToSwap;
}