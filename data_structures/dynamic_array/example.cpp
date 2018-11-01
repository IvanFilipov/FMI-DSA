/*
 * Example usage of custom dynamic array. Some benchmarking and STL algorithms.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <random>    // std::random_device, std::mt19937
#include <iostream>  // std::cout
#include <algorithm> // std::sort(), std::shuffle(), std::is_sorted(), std::for_each()

#include "dynamic_array.hpp"
#include "../../utils/benchmark.hpp" // custom benchmark function

using dsa::dynamic_array;
using dsa::benchmark_test_fnc;
using dsa::T_FORMAT;

const int N_FILL = 1000000;
const int MAX_EL = 1000000;

// random generator modern c++ style : https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
std::random_device rd; // create random device
std::mt19937 random_generator(rd());  // create random generator based on that device

// a dynamic_array global object, used in benchmarking examples
dynamic_array<int> arr;

// a function that fills our array with N_FILL random elements
// all positive < MAX_EL
void init() {

	for (int i = 0; i < N_FILL; i++)
		arr.push_back(random_generator() % MAX_EL);
}
// searching in the worst case... (no such element)
// using linear search algorithm
void run_search_slow() {
	
	arr.find(-1);
}
// using binary search algorithm
void run_search_fast() {
	
	arr.find(-1, true);
}
// sort the array
void run_sort() {
	// yeah, we have random iterators,
	// how sweet is that, we can use std::sort :)
	std::sort(arr.begin(), arr.end());
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
	std::cout << "size : " << first.size() 
			  << " cap : " << first.get_capacity() 
			  << std::endl;
	
	first.insert_at(first.begin() + 33, 25);
	std::cout << "after insert value 25 at index 33 :" << std::endl;
	first.print_elems(std::cout);
	std::cout << std::endl;
	
	first.insert_at(first.begin() + 4, 14);
	std::cout << "after insert value 14 at index 4 :" << std::endl;
	first.print_elems(std::cout);
	std::cout << std::endl;
	
	first.remove_at(first.begin() + 58);
	std::cout << "after removing at index 58 :" << std::endl;
	first.print_elems(std::cout);
	std::cout << std::endl;
	
	first.remove_at(first.begin() + 4);
	std::cout << "after removing at index 4 :" << std::endl;
	first.print_elems(std::cout);
	std::cout << std::endl;
	
	dynamic_array<int> second = first;
	std::cout << "array \"second\" a copy of \"first\" :" << std::endl;
	second.print_info(std::cout);
	second.print_elems(std::cout);
}

void run_advanced_tests() {
	
	std::cout << std::endl 
	          << "---------------------------"
			  << std::endl
	          << "modern C++ tests"
			  << std::endl << std::endl;
	/* 
	 because we have iterator, which is STL compatible
	 we can take advantage of : 
	 moder C++ look-like iterations
	 STL algorithms, which take random access iterators
	*/
	
	// create a test array with initializer list
	dynamic_array<int> f_arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	
	std::cout << "iterating over all elements using iterator based for :" << std::endl;
	for (dynamic_array<int>::iterator it = f_arr.begin(); it != f_arr.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl << std::endl;
	
	std::cout << "iterating over all elements using range based for :" << std::endl;
	for (int el : f_arr) {
		std::cout << el << " ";
	}
	std::cout << std::endl << std::endl;
	
	std::cout << "\nTESTING SOME STL ALGORITHM FUNCTIONS :" << std::endl;
	std::cout << "\nelements after a shuffle :" << std::endl;
	
	std::shuffle(f_arr.begin(), f_arr.end(), random_generator);
	f_arr.print_elems(std::cout);
	std::cout << std::endl;
	
	
	int num_items3 = std::count_if(f_arr.begin(), f_arr.end(), [](int i) -> bool { return i % 3 == 0; });
    std::cout << "numbers divisible by three: " << num_items3 << std::endl;
	
	std::cout << "\nour elements multiplied by three :" << std::endl;
	std::for_each(f_arr.begin(), f_arr.end(), [](int& i) -> void { i *= 3; });
	f_arr.print_elems(std::cout);

	std::cout << "\nis the array sorted? :" 
			  << ((std::is_sorted(f_arr.begin(), f_arr.end())) ? "yes" : "no") 
			  << std::endl;
	
	std::cout << "elements after sorting them :" << std::endl;
	std::sort(f_arr.begin(), f_arr.end());
	f_arr.print_elems(std::cout);
	std::cout << std::endl;
}

int main() {

	/* initialize the global array */
	init();

	/* test 1 linear searching */
	benchmark_test_fnc(run_search_slow, T_FORMAT::F_MICRO, "linear searching");

	/* sort the array */
	benchmark_test_fnc(run_sort, T_FORMAT::F_ALL, "sorting");

	/* test 2 binary searching */
	benchmark_test_fnc(run_search_fast, T_FORMAT::F_MICRO, "binary searching");
	
	/* test 3 basic functionality */
	run_basic_tests();
	
	/* test 4 advanced functionality */
	run_advanced_tests();
	
	return 0;
}
