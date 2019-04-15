/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   static_queue.hpp
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  Implementation of static queue data structure as 
 *         an adapter on "cyclic" array. No dynamic memory allocations.
 * @see https://en.wikipedia.org/wiki/Queue_(abstract_data_type)
 */
 
#pragma once
 
#include <stdexcept> // exception types

namespace dsa {
/**
 * @class static_queue
 * @brief Stores elements in FIFO style.
 * @tparam T: type of elements stored
 * @tparam N: size of underlaying array, must be known at compile time.
 */
template <typename T, size_t N>
class static_queue {
private:
	/* private data members */
	T data[N];     //!< the underlaying array
	size_t head;   //!< index of the head
	size_t tail;   //!< index of the tail
	bool is_empty; //!< boolean for emptiness

public:
	/* object life cycle */
	// no dynamic memory to handle, so no need for "the big four" -
	// we are OK with the compile-generated
	/** Creates %static_queue with no elements */
	static_queue(): head(0), tail(0), is_empty(true) {};
	
	/**
	  *  @brief     %static_queue copy constructor.
	  *  @param[in] rhs: A %static_queue of identical element type, from which to copy.
	  */
	static_queue(const static_queue&) = default;
	
	/**
	  *  @brief     %static_queue assignment operator.
	  *  @param[in] rhs: A %static_queue of identical element type, from which to copy.
	  */
	static_queue& operator=(const static_queue&) = default;
	
	/** Destroys an object */
	~static_queue() = default; 
	
public:
	/* interface */
	/**
	 * @brief         Push a new element at the back of the queue.
	 * @param[in] el: Value to be inserted
	 * @throw std::logic_error if the queue is full
	 * Time complexity O(1).
	 * @note STL friendly name, but "enqueue" is preferable.
	 */
	void push(const T& el);
	
	/**
	 * @brief Pop the front element of the queue.
	 * @retval Copy of the front element.
	 * @throw std::logic_error if the queue is empty
	 * Time complexity O(1).
	 * @note "dequeue" is generally a better name for that method.
	 */
	T pop();
	
	/**
	 * @brief  Checks if the %static_queue is empty.
	 * @retval boolean: whether the static_queue is empty.
	 * Time complexity O(1).
	 */
	bool empty() const { return is_empty; };
	
	/**
	 * @brief Get the current size of the queue.
 	 * @retval Current size.
 	 * Time complexity O(1).
	 */
	size_t size() const;
	
	/** Resets all values */
	void clear();
};

template <typename T, size_t N>
void static_queue<T, N>::push(const T& el) {

	// there is no space
	if ((tail == head) && !is_empty)
		throw std::logic_error("the queue is full");
	//
	//adding the new element and move the tail
	data[tail++] = el;
	//
	//makes the queue cyclic
	if (tail >= N)
		tail = 0;
	//
	is_empty = false;
}

template <typename T, size_t N>
T static_queue<T, N>::pop() {
	// empty?
	if (is_empty) throw std::logic_error("empty queue");
	//
	// a copy of the first element
	T el = data[head++]; // move the head
	//
	// make the queue cyclic
	if (head >= N)
		head = 0;
	//
	// check if the head has "caught" the tail
	if (head == tail) is_empty = true;
	//
	return el;
}

template <typename T, size_t N>
inline size_t static_queue<T, N>::size() const {
	// empty
	if (is_empty) return 0;
	//
	// full
	if (head == tail && !is_empty) return N;
	//
	// can't determinate so easy, we should
	// make a walk around
	size_t num_elems = 0;

	if (head > tail) { // we should make a new cycle
		num_elems += (N - head);
		num_elems += tail;
	} else {
		num_elems += (tail - head);
	}
	//
	return num_elems;
}

template <typename T, size_t N>
inline
void static_queue<T, N>::clear() {

	head = 0;
	tail = 0;
	is_empty = true;
}
} // namespace dsa
