/*
 * Example usage of custom doubly linked list. Testing with some STL algorithms.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
#include <iostream>  // std::cout
#include <algorithm> // std::count_if(), std::transform(), 
                     // std::is_sorted(), std::reverse(), std::merge()
#include "dlinked_list.hpp"
#include <list>

using dsa::dlinked_list;

void run_basic_tests() {
	
	dlinked_list<int> f_list;

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
	dlinked_list<int>::iterator it = f_list.find(11);
	if (it != f_list.end()) {

		std::cout << "found 11!" << std::endl;
		std::cout << "inserting 73 on it's position :" << std::endl;
		f_list.insert(it, 73);
		f_list.print_elems(std::cout);
	} else std::cout << "11 not found!" << std::endl;
	
	std::cout << "\nsearching for 1 :" << std::endl;
	it = f_list.find(1);
	if (it != f_list.end()) {

		std::cout << "found 1!" << std::endl;
		std::cout << "removing it :" << std::endl;
		f_list.remove(it);
		f_list.print_elems(std::cout);
	} else std::cout << "1 not found!" << std::endl;
	
	std::cout << "\nsearching for 404 :" << std::endl;
	it = f_list.find(404);
	if (it != f_list.end()) {

		std::cout << "found 404!" << std::endl;
		std::cout << "inserting 405 on it's position :" << std::endl;
		f_list.insert(it, 405);
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
	
	
	dlinked_list<int> second = f_list;
	std::cout << "\ncopy working?" << std::endl;
	second.print_elems(std::cout);
	
}	

void run_advanced_tests() {
	
	// create a test list with initializer list
	dlinked_list<int> f_list = { 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10 };
	
	std::cout << "\nmodern C++ tests\n\n";
	// because we have iterator, which is STL compatible
	// we can take advantage of : 
	// moder C++ look-like iterations
	// STL algorithms
	// our structure is compatible with all algorithms that takes forward iterators 
	
	std::cout << "iterating forward over all elements using iterator based for :" << std::endl;
	for (dlinked_list<int>::iterator it = f_list.begin(); it != f_list.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl << std::endl;
	
	std::cout << "iterating backward over all elements using iterator based for :" << std::endl;
	for (dlinked_list<int>::iterator it = f_list.rbegin(); it != f_list.rend(); --it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl << std::endl;
	
	std::cout << "iterating over all elements using range based for :" << std::endl;
	for (int el : f_list) {
		std::cout << el << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "applying iterator based filter for even numbers :" << std::endl;
	for (dlinked_list<int>::iterator it = f_list.begin(); it != f_list.end(); ) {
		if (*it % 2 == 0) 
			it = f_list.remove(it);
		else 
			++it;
	}
	f_list.print_elems(std::cout);
	std::cout << std::endl;

	std::cout << "applying iterator based map for +1 function :" << std::endl;
	for (dlinked_list<int>::iterator it = f_list.begin(); it != f_list.end(); ++it) {

		(*it)++;
	}
	f_list.print_elems(std::cout);
	
	std::cout << "\n\nTESTING SOME STL ALGORITHM FUNCTIONS :" << std::endl;
	f_list.print_elems(std::cout);
	int num_items3 = std::count_if(f_list.begin(), f_list.end(), [](int i) -> bool {return i % 3 == 0;});
    std::cout << "number divisible by three: " << num_items3 << std::endl;
	
	std::cout << "\nour elements multiplied by three and stored into another list:" << std::endl;
	dlinked_list<int> s_list;
	std::transform(f_list.begin(), f_list.end(), std::back_inserter(s_list),
                   [](int i) -> int { return i * 3; });
	s_list.print_elems(std::cout);

	std::cout << "\nis the new list sorted? :" 
			  << ((std::is_sorted(s_list.begin(), s_list.end())) ? "yes" : "no") 
			  << std::endl;
			  
	std::cout << "\nreversed list from our:" << std::endl;
	dlinked_list<int> rev_list = s_list;
	std::reverse_copy(s_list.begin(), s_list.end(), rev_list.begin());
	rev_list.print_elems(std::cout); 
	
	std::cout << "\nreversing the result :" << std::endl;
	std::reverse(rev_list.begin(), rev_list.end());
	rev_list.print_elems(std::cout);
	
	
	std::cout << "\nmerging the result with { 10, 20, 30, 40 }:" << std::endl;
	dlinked_list<int> m = { 10, 20, 30, 40 };
	dlinked_list<int> merge_res;
    std::merge(m.begin(), m.end(), rev_list.begin(), rev_list.end(), std::back_inserter(merge_res));
	merge_res.print_elems(std::cout);
}

int main() {
	
	/* testing the interface of the class */
	run_basic_tests();
	
	/* testing the modern C++ usage of the class */
	run_advanced_tests();
		
	return 0;
}
