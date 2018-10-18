#include <stdlib.h> //rand, srand
#include <time.h> //time
#include <iostream> //std::cout

#include "dynamic_array.hpp"
#include "../../utils/benchmark.hpp"

const int N_FILL = 100000;
const int MAX_EL = 100000;

//an DynamicArray global object
dynamic_array<int> arr;

//a function that fills our array with 100000 random elements
//all positive < 100000
void init() {

	for (int i = 0; i < N_FILL; i++)
		arr.push_back(rand() % MAX_EL);
}

//searching in the worst case... (no such element)
void run_search() {
	
	arr.search(-1);
}

//sort the array
void run_sort() {
	
	arr.sort();
}

//testing some basic functionality of our class
//push / pop / add / remove / copy
void run_basic_tests() {
	
	std::cout << std::endl 
	          << "---------------------------"
			  << std::endl
	          << "running basic test"
			  << std::endl << std::endl;
	
	dynamic_array<int> first;
	std::cout << "array \"first\" :" << std::endl;
	first.print_info(std::cout);

	first.push_back(7);
	first.push_back(8);
	first.push_back(9);
	first.push_back(10);
	first.push_back(15);
	first.push_back(23);
	std::cout << "after pushing back some elements :" << std::endl;
	first.print_info(std::cout);
	first.print_elems(std::cout);
	std::cout << std::endl;
	
	
	std::cout << "element on index 3 : " << first[3] << std::endl; 
	std::cout << "size : " << first.get_size() 
			  << " cap : " << first.get_capacity() 
			  << std::endl;
	
	first.insert_at(33, 25);
	std::cout << "after insert value 25 at index 33 :" << std::endl;
	first.print_elems(std::cout);
	std::cout << std::endl;
	
	first.insert_at(4, 14);
	std::cout << "after insert value 14 at index 4 :" << std::endl;
	first.print_elems(std::cout);
	std::cout << std::endl;
	
	first.remove_at(58);
	std::cout << "after removing at index 58 :" << std::endl;
	first.print_elems(std::cout);
	std::cout << std::endl;
	
	first.remove_at(4);
	std::cout << "after removing at index 4 :" << std::endl;
	first.print_elems(std::cout);
	std::cout << std::endl;
	
	dynamic_array<int> second = first;
	std::cout << "array \"second\" a copy of \"first\" :" << std::endl;
	second.print_info(std::cout);
	second.print_elems(std::cout);
}

int main() {

	/* seed the random generator */
	srand(static_cast<unsigned int>(time(nullptr)));
	
	/* initialize the array */
	init();

	/* test 1 linear searching */
	benchmark_test_fnc(run_search, T_FORMAT::F_MICRO, "linear searching");

	/* sort the array */
	benchmark_test_fnc(run_sort, T_FORMAT::F_ALL, "slow sorting");

	/* test 2 binary searching */
	benchmark_test_fnc(run_search, T_FORMAT::F_MICRO, "binary searching");
	
	/* test 3 basic functionality */
	run_basic_tests();
	
	return 0;
}
