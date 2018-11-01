/*
 * A template generalizing the idea that the stack is only an adapter for linked list or array.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
#pragma once

namespace dsa {
template<typename T, typename Container>
class t_stack {
	
private:
	// the laying down container could be different, 
	// it only should have an interface : back, push/pop_back, empty, size
	Container container;

public:
	// interface :
	
	// letting us to "see" the top or to "adjust" it
	T& peek() { return container.back(); }
	const T& peek() const { return container.back(); }

	// remove / add top element
	void push(const T& el) { container.push_back(el); }
	void pop() { container.pop_back(); }
	
	// getters
	bool empty() const { return container.empty(); }
	size_t size() const { return container.size(); }
};
} // namespace dsa
