/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   template_queue.hpp
 * @author Ivan Filipov
 * @date   11.2019
 * @brief  A template generalizing the idea,
 *         that the queue is only an adapter for linked list or array.
 */
#pragma once 

namespace dsa {
template<typename T, typename Container>
/**
 * @class t_queue
 * @brief Queue interface for different underlaying containers.
 * @tparam T: type of elements stored
 * @tparam Container: type of the underlaying container.
 *
 * @note %Container must [have back, push_back, pop_front, empty, size] in its interface.
 */
class t_queue {
private:
	Container container; //!< the underlaying container

public:
	// interface :
	/** Get the first element */
	T& front() { return container.front(); }
	
	/** Get the first element - read-only. */
	const T& front() const { return container.front(); }
	
	/** Get the last element */
	T& back() { return container.back(); }
	
	/** Get the first element read-only. */
	const T& back() const { return container.back(); }

	/** Enqueue: add new element at the end */
	void push(const T& el) { container.push_back(el); }
	
	/** Dequeue: remove first element */
	void pop() { container.pop_front(); }
	
	/** Check if the stack is empty */
	bool empty() const { return container.empty(); }
	
	/** Get the count of elements stored */
	size_t size() const { return container.size(); }
};

/// specialization for std::vector<int>, because there is no
/// pop_front in vector's interface
template<>
void t_queue<int, std::vector<int>>::pop() {
	
	std::swap(container[0], container[container.size() - 1]);
	container.pop_back();
}

/// specialization for dsa::dynamic_array<int>
template<>
void t_queue<int, dsa::dynamic_array<int>>::pop() {
	
	std::swap(container[0], container[container.size() - 1]);
	container.pop_back();
}
} // namespace dsa
