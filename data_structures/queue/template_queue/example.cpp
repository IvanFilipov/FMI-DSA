/*
 * Example usage of the template queue idea. Some benchmarking, a competition between our data structures vs. STL.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream> // std::cout
#include <vector>   // std::vector
#include <list>     // std::list
#include <queue>    // std::queue

#include "../../../utils/benchmark.hpp"                          // our test benchmark lib
#include "../../dynamic_array/dynamic_array.hpp"                 // our custom vector
#include "../../linked_list/singly_linked_list/slinked_list.hpp" // our custom singly linked list
#include "../../linked_list/doubly_linked_list/dlinked_list.hpp" // our custom doubly linked list
#include "../dynamic_queue/dynamic_queue.hpp"                    // our custom dynamic stack

#include "template_queue.hpp" // the template for stack interface with variadic down-laying container 

// bring here some names from our lib
using namespace dsa;

// and also from std
using std::vector;
using std::list;
using std::queue;

const size_t ECOUNT = 10000;

template<typename Container>
void test_queue_adaptor() {
	
	t_queue<int, Container> q;
	
	// adding elements
	for(size_t i = 0; i < ECOUNT; i++)
		q.push(static_cast<int>(i));

	// make a copy
	t_queue<int, Container> q2 =q;
	q2.push(11); // just to be sure that stack2 is used, 
		             // because the compiler could optimize the code
	
	// check is empty?
	std::cout << "\nempty " << (q.empty() ? "yes" : "no");
	std::cout << " | size " << q.size();
	
	unsigned long long sum = 0;
	// remove elements
	while(!q.empty()) {
		
		sum += q.front();
		q.pop();
	}
	
	std::cout << " | sum = " << sum << std::endl;
	
	//destructor for st and st2
}

template<typename Queue>
void test_queue_plain() {
	
	Queue q;
	
	// adding elements
	for(size_t i = 0; i < ECOUNT; i++)
		q.push(static_cast<int>(i));

	// make a copy
	Queue q2 = q;
	q2.push(11); // just to be sure that stack2 is used, 
		             // because the compiler could optimize the code
	
	// check is empty?
	std::cout << "\nempty " << (q.empty() ? "yes" : "no");
	std::cout << " | size " << q.size();
	
	unsigned long long sum = 0;
	// remove elements
	while(!q.empty()) {
		
		sum += q.front();
		q.pop();
	}
	
	std::cout << " | sum = " << sum << std::endl;
	//destructor for st and st2
}

int main() {
	
	/* test operations with std::vector */
	benchmark_test_fnc(test_queue_adaptor<vector<int>>, T_FORMAT::F_MILLI, "implementation on std::vector");
	
	/* test operations with our custom vector */
	benchmark_test_fnc(test_queue_adaptor<dynamic_array<int>>, T_FORMAT::F_MILLI, "implementation on dsa::dynamic_array");
	
	/* test operations with std::list */
	benchmark_test_fnc(test_queue_adaptor<list<int>>, T_FORMAT::F_MILLI, "implementation on std::list");
	
	/* test operations with our custom singly linked list */
	/// !!! here the situation in the competition between our list and std::list is different, because
	/// the queue only needs pop_front & push_back, both O(1) in these implementations, but std::list is doubly linked. 
	benchmark_test_fnc(test_queue_adaptor<slinked_list<int>>, T_FORMAT::F_MILLI, "implementation on dsa::slinked_list");
	
	/* test operations with our custom doubly linked list */
	benchmark_test_fnc(test_queue_adaptor<dlinked_list<int>>, T_FORMAT::F_MILLI, "implementation on dsa::dlinked_list");
		
	/* test operations with std::queue */
	benchmark_test_fnc(test_queue_plain<queue<int>>, T_FORMAT::F_MILLI, "implementation on std::queue");
	
	/* test operations with our custom dynamic queue */
	benchmark_test_fnc(test_queue_plain<dynamic_queue<int>>, T_FORMAT::F_MILLI, "implementation on dsa::dynamic_queue");
}
