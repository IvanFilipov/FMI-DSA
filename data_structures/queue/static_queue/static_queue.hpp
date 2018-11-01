/*
 * Implementation of static queue data structure. Adapter on a "cyclic" array. No dynamic memory allocations.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
#include <stdexcept> // exception types

// first template argument is the type of stored objects 
// the second one is a compile time known constant - the size of
// the underlaying array
namespace dsa {
template <typename T, size_t N>
class static_queue {

private:

	T data[N]; // the underlaying array

	size_t head;  // just indexes
	size_t tail;  // where to add/remove

	bool is_empty;

public:

	// no dynamic memory to handle, so no need for big 4
	static_queue() : head(0), tail(0), is_empty(true) {};
	// we are OK with the compile-generated
	static_queue(const static_queue&) = default;
	static_queue& operator=(const static_queue&) = default;
	~static_queue() = default; 
	
public:
	// interface
	// adding a new element in the back
	// STL friendly name, "enqueue" is preferable
	void push(const T& el);
	// removing an element from the front. "dequeue" is better name
	T pop();
	// what is the current size
	size_t size() const;
	// resets all values
	void clean();
	// is the queue empty
	bool empty() const { return is_empty; };
};

template <typename T, size_t N>
void static_queue<T, N>::push(const T& el) {

	//there is no space
	if ((tail == head) && !is_empty)
		throw std::logic_error("the static_queue is FULL!");
	//adding the new element and move the tail
	data[tail++] = el;
	//makes the static_queue cyclic
	if (tail >= N)
		tail = 0;

	is_empty = false;
}

template <typename T, size_t N>
T static_queue<T, N>::pop() {

	if (is_empty)
		throw std::logic_error("EMPTY static_queue!");
	
	// a copy of the first element
	T el = data[head++]; // move the head

	//makes the static_queue cyclic
	if (head >= N)
		head = 0;

	if (head == tail) // the head has "caught" the tail
		is_empty = true;
	// return the element
	return el;
}

template <typename T, size_t N>
inline size_t static_queue<T, N>::size() const {
	// empty
	if (is_empty)
		return 0;
	// full
	if (head == tail && !is_empty)
		return N;
	
	// can't determinate so easy, we should
	// make a walk around
	size_t num_elems = 0;

	if (head > tail) { // we should make a new cycle
		
		num_elems += (N - head);
		num_elems += tail;
	}
	else
		num_elems += (tail - head);

	return num_elems;
}

template <typename T, size_t N>
inline
void static_queue<T, N>::clean() {

	head = 0;
	tail = 0;
	is_empty = true;
}
} // namespace dsa
