/*
 * Example usage of custom singly linked list. Testing with some STL algorithms.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
#include <iostream>  // std::cout
#include <algorithm> // std::count_if(), std::transform(), std::is_sorted()
#include "slinked_list.hpp"

using dsa::slinked_list;

void run_basic_tests() {
	
	slinked_list<int> f_list;

	f_list.push_back(1);
	f_list.push_back(11);
	f_list.push_back(22); 
	f_list.push_back(33);
	std::cout << "list after push_back some elements" << std::endl;
	f_list.print_elems(std::cout);
	
	f_list.push_front(44);
	f_list.push_front(55);
	std::cout << "\nlist after push_front 44, then 55" << std::endl;
	f_list.print_elems(std::cout);
	
	std::cout << "\nsearching for 11 :" << std::endl;
	slinked_list<int>::iterator it = f_list.find(11);
	if (it != f_list.end()) {

		std::cout << "found 11!" << std::endl;
		std::cout << "inserting 73 after it :" << std::endl;
		f_list.insert_after(it, 73);
		f_list.print_elems(std::cout);
	} else std::cout << "11 not found!" << std::endl;
	
	std::cout << "\nsearching for 1 :" << std::endl;
	it = f_list.find(1);
	if (it != f_list.end()) {

		std::cout << "found 1!" << std::endl;
		std::cout << "removing element after it :" << std::endl;
		f_list.remove_after(it);
		f_list.print_elems(std::cout);
	} else std::cout << "1 not found!" << std::endl;
	
	std::cout << "\nsearching for 404 :" << std::endl;
	it = f_list.find(404);
	if (it != f_list.end()) {

		std::cout << "found 404!" << std::endl;
		std::cout << "inserting 405 after it :" << std::endl;
		f_list.insert_after(it, 405);
		f_list.print_elems(std::cout);
	} else std::cout << "404 not found!" << std::endl;
	
	std::cout << "\nafter pop back :" << std::endl;
	f_list.pop_back();
	f_list.print_elems(std::cout);
	
	std::cout << "\nafter pop front :" << std::endl;
	f_list.pop_front();
	f_list.print_elems(std::cout);
	
	std::cout << "\nafter pop back :" << std::endl;
	f_list.pop_back();
	f_list.print_elems(std::cout);
	
	std::cout << "\nfirst element : " << f_list.front();
	std::cout << "after changing it to 101 : " << std::endl;
	f_list.front()  = 101;
	f_list.print_elems(std::cout);
	
	std::cout << "\nlast element : " << f_list.back();
	std::cout << "after changing it to 202 : " << std::endl;
	f_list.back()  = 202;
	f_list.print_elems(std::cout);
	
	slinked_list<int> second = f_list;
	std::cout << "\ncopy working?" << std::endl;
	second.print_elems(std::cout);
	
}	

void run_advanced_tests() {
	
	// create a test list with initializer list
	slinked_list<int> f_list = { 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10 };
	
	std::cout << "\nmodern C++ tests\n\n";
	// because we have iterator, which is STL compatible
	// we can take advantage of : 
	// moder C++ look-like iterations
	// STL algorithms
	// our structure is compatible with all algorithms that takes forward iterators 
	
	std::cout << "iterating over all elements using iterator based for :" << std::endl;
	for (slinked_list<int>::iterator it = f_list.begin(); it != f_list.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl << std::endl;
	
	std::cout << "iterating over all elements using range based for :" << std::endl;
	for (int el : f_list) {
		std::cout << el << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "applying iterator based filter for each second number :" << std::endl;
	int i = 0;
	for (slinked_list<int>::iterator it = f_list.begin(); it != f_list.end(); ) {
		if (i % 2 == 0) 
			it = f_list.remove_after(it);
		else 
			++it;
		++i;
	}
	f_list.print_elems(std::cout);
	std::cout << std::endl;

	std::cout << "applying iterator based map for +1 function :" << std::endl;
	for (slinked_list<int>::iterator it = f_list.begin(); it != f_list.end(); ++it) {

		(*it)++;
	}
	f_list.print_elems(std::cout);
	
	std::cout << "\n\nTESTING SOME STL ALGORITHM FUNCTIONS :" << std::endl;
	f_list.print_elems(std::cout);
	int num_items3 = std::count_if(f_list.begin(), f_list.end(), [](int i) -> bool {return i % 3 == 0;});
    std::cout << "number divisible by three: " << num_items3 << std::endl;
	
	std::cout << "\nour elements multiplied by three and stored into another list:" << std::endl;
	slinked_list<int> s_list;
	std::transform(f_list.begin(), f_list.end(), std::back_inserter(s_list),
                   [](int i) -> int { return i * 3; });
	s_list.print_elems(std::cout);

	std::cout << "\nis the new list sorted? :" 
			  << ((std::is_sorted(s_list.begin(), s_list.end())) ? "yes" : "no") 
			  << std::endl;
}

int main() {
	
	/* testing the interface of the class */
	run_basic_tests();
	
	/* testing the modern C++ usage of the class */
	run_advanced_tests();
		
	return 0;
}
