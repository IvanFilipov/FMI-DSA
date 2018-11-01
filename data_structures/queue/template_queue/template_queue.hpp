/*
 * A template generalizing the idea that the queue is only an adapter for linked list or array.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
#pragma once 

namespace dsa {
template<typename T, typename Container>
class t_queue {
	
private:
	// the laying down container could be different, 
	// it only should have an interface : back, front, push_back, pop_front, empty, size
	Container container;

public:
	// interface :
	
	// letting us to "see" the first or to "adjust" it
	T& front() { return container.front(); }
	const T& front() const { return container.front(); }
	// same for the last one
	T& back() { return container.back(); }
	const T& back() const { return container.back(); }

	// enqueue - new element at the end
	void push(const T& el) { container.push_back(el); }
	// dequeue - remove first element
	void pop() { container.pop_front(); }
	
	// getters
	bool empty() const { return container.empty(); }
	size_t size() const { return container.size(); }
};

// specialization for std::vector<int>, because there is no
// pop_front in vector's interface
template<>
void t_queue<int, std::vector<int>>::pop() {
	
	std::swap(container[0], container[container.size() - 1]);
	container.pop_back();
}

// specialization for dsa::dynamic_array<int>
template<>
void t_queue<int, dsa::dynamic_array<int>>::pop() {
	
	std::swap(container[0], container[container.size() - 1]);
	container.pop_back();
}

} // namespace dsa
