/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   template_stack.hpp
 * @author Ivan Filipov
 * @date   11.2019
 * @brief  A template generalizing the idea,
 *         that the stack is only an adapter for linked list or array.
 */

#pragma once

namespace dsa {
/**
 * @class t_stack
 * @brief Stack interface for different underlaying containers.
 * @tparam T: type of elements stored
 * @tparam Container: type of the underlaying container.
 *
 * @note %Container must [have back, push/pop_back, empty, size] in its interface.
 */
template<typename T, typename Container>
class t_stack {
private:
	Container container; //!< the underlaying container
	
public:
	// interface :
	/** Get the top element */
	T& peek() { return container.back(); }
	/** Get the top element - read-only. */
	const T& peek() const { return container.back(); }

	/** Add element on the top. */
	void push(const T& el) { container.push_back(el); }
	
	/** Remove the top element */
	void pop() { container.pop_back(); }
	
	/** Check if the stack is empty */
	bool empty() const { return container.empty(); }
	
	/** Get the count of elements stored */
	size_t size() const { return container.size(); }
};
} // namespace dsa
