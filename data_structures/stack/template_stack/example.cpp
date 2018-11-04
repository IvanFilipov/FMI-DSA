/*
 * Example usage of the template stack idea. Some benchmarking, a competition between our data structures vs. STL.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream> // std::cout
#include <vector>   // std::vector
#include <list>     // std::list
#include <stack>    // std::stack

#include "../../../utils/benchmark.hpp"                          // our test benchmark lib
#include "../../dynamic_array/dynamic_array.hpp"                 // our custom vector
#include "../../linked_list/singly_linked_list/slinked_list.hpp" // our custom singly linked list
#include "../../linked_list/doubly_linked_list/dlinked_list.hpp" // our custom doubly linked list
#include "../dynamic_stack/dynamic_stack.hpp"                    // our custom dynamic stack

#include "template_stack.hpp" // the template for stack interface with variadic down-laying container 

// bring here some names from our lib
using namespace dsa;

// and also from std
using std::vector;
using std::list;
using std::stack;

const size_t ECOUNT = 10000;

template<typename Container>
void test_stack_adaptor() {
	
	t_stack<int, Container> st;
	
	// adding elements
	for(size_t i = 0; i < ECOUNT; i++)
		st.push(static_cast<int>(i));

	// make a copy
	t_stack<int, Container> st2 = st;
	st2.push(11); // just to be sure that stack2 is used, 
		             // because the compiler could optimize the code
	
	// check is empty?
	std::cout << "\nempty " << (st.empty() ? "yes" : "no");
	std::cout << " | size " << st.size();
	
	unsigned long long sum = 0;
	// remove elements
	for(size_t i = ECOUNT; i > 0; i--) {
		
		sum += st.peek();
		st.pop();
	}
	
	std::cout << " | sum = " << sum << std::endl;
	
	//destructor for st and st2
}

template<typename Stack>
void test_stack_plain() {
	
	Stack st;
	
	// adding elements
	for(size_t i = 0; i < ECOUNT; i++)
		st.push(static_cast<int>(i));

	// make a copy
	Stack st2 = st;
	st2.push(11); // just to be sure that stack2 is used, 
		             // because the compiler could optimize the code
	
	// check is empty?
	std::cout << "\nempty " << (st.empty() ? "yes" : "no");
	std::cout << " | size " << st.size();
	
	unsigned long long sum = 0;
	// remove elements
	for(size_t i = ECOUNT; i > 0; i--) {
		
		sum += st.top();
		st.pop();
	}
	
	std::cout << " | sum = " << sum << std::endl;
	
	//destructor for st and st2
}

int main() {
	
	/* test operations with std::vector */
	benchmark_test_fnc(test_stack_adaptor<vector<int>>, T_FORMAT::F_MILLI, "implementation on std::vector");
	
	/* test operations with our custom vector */
	benchmark_test_fnc(test_stack_adaptor<dynamic_array<int>>, T_FORMAT::F_MILLI, "implementation on dsa::dynamic_array");
	
	/* test operations with std::list */
	benchmark_test_fnc(test_stack_adaptor<list<int>>, T_FORMAT::F_MILLI, "implementation on std::list");
	
	/* test operations with our custom singly linked list */ 
	///!!! our pop_back is O(n), while std::list's one is O(1), because it is doubly linked list, that's way this one is much slower
	benchmark_test_fnc(test_stack_adaptor<slinked_list<int>>, T_FORMAT::F_MILLI, "implementation on dsa::slinked_list");
	
	/* test operations with our custom doubly linked list */
	benchmark_test_fnc(test_stack_adaptor<dlinked_list<int>>, T_FORMAT::F_MILLI, "implementation on dsa::dlinked_list");
	
	/* test operations with std::stack */
	benchmark_test_fnc(test_stack_plain<stack<int>>, T_FORMAT::F_MILLI, "implementation on std::stack");
	
	/* test operations with our custom dynamic stack */
	benchmark_test_fnc(test_stack_plain<dynamic_stack<int>>, T_FORMAT::F_MILLI, "implementation on dsa::dynamic_stack");
}
