/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.cpp
 * @author Gratsiela Gancheva 
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  Tests and example usage of our custom priority_queue.
 */

#include <iostream> // std::cout, std::endl
#include <cstdlib>  // std::rand, std::srand
#include <ctime>    // std::time

#include "priority_queue.hpp"       // dsa::priority_queue
#include "../../../utils/student.h" // dsa::student

/// run test on randomly filled queue
void run_basic_tests() {
	// Create queue
	dsa::priority_queue<int> pqueue;
	std::cout << "Successful created priority queue!\n\n";
	// Test whether container is empty
	std::cout << "Is empty: " << ((pqueue.empty()) ? "True\n\n" : "False\n\n");
	// Get size
	std::cout << "Size: " << pqueue.size() << "\n\n";
	// Get top element
	try {
		std::cout << "Get top element: ";
		std::cout << pqueue.top() << std::endl;
	} catch (const std::out_of_range& e) {
		std::cout << e.what()<<std::endl;
	}
	std::cout << std::endl;
	 // Insert elements
	std::srand(std::time(NULL));
	for (size_t i = 0; i < 10; i++) {
		int el = std::rand() % 10;
		pqueue.push(el);
		std::cout << "Successful added element: " << el << std::endl;
	}
	std::cout << std::endl;
	// Remove elements
	while (!pqueue.empty()) {
		std::cout << "See and pop the top element... " << pqueue.top() << std::endl;
		pqueue.pop();
	}
	std::cout << std::endl;
	// Insert new element
	pqueue.push(100);
	std::cout << "Successful added element: " << 100 << "\n\n";
	// Clear queue
	std::cout << "Size before clear: " << pqueue.size() << std::endl;
	pqueue.clear();
	std::cout << "Size after clear: " << pqueue.size() << std::endl;
	std::cout << "------------------------" << std::endl;
}

/// fills a queue with students
/// @tparam Pqueue: type of priority_queue (elements and compare function)
template<typename PQueue>
void feed_with_some_students(PQueue& q) {
	
	q.push({ "Ivancho", 40000 });
	q.push({ "Mariika", 25000 });
	q.push({ "Gencho", 50001 });
	q.push({ "Pencho", 25000 });
	q.push({ "Genka", 42000 });
	q.push({ "Penka", 25000 });
	q.push({ "Kalin", 40000 });
	q.push({ "Kalinka", 25000 });
}

/// run tests with custom comparator
void run_advanced_tests() {
	
	// Create queue with students and custom comparator
	// passed as lambda function
	auto cmp_students_fn = [](const dsa::student& lhs, const dsa::student& rhs) { return lhs.fn < rhs.fn; };
	dsa::priority_queue <dsa::student,
						 decltype(cmp_students_fn)           
						> pqueue (cmp_students_fn);
						
	feed_with_some_students(pqueue);
	std::cout << "Students from queue ordered by fn :" << std::endl;
	int i = 0;
	while (!pqueue.empty()) {
		std::cout << "# " << i++ << pqueue.top() << std::endl;
		pqueue.pop();
	}
	std::cout << std::endl << std::endl;
	
	dsa::priority_queue <dsa::student> pnqueue;
						
	feed_with_some_students(pnqueue);
	std::cout << "Students from queue ordered by name (default operator<) :" << std::endl;
	i = 0;
	while (!pnqueue.empty()) {
		std::cout << "# " << i++ << pnqueue.top() << std::endl;
		pnqueue.pop();
	}
	std::cout << std::endl << std::endl;
	
	dsa::priority_queue <dsa::student, std::greater<dsa::student>> squeue;
						
	feed_with_some_students(squeue);
	std::cout << "Students from queue ordered by name (using operator>) :" << std::endl;
	i = 0;
	while (!squeue.empty()) {
		std::cout << "# " << i++ << squeue.top() << std::endl;
		squeue.pop();
	}
	std::cout << std::endl << std::endl;
}

int main() {
	
	/* test basic functionality */
	run_basic_tests();
	
	/* test advanced functionality */
	run_advanced_tests();
	
	return 0;
}
