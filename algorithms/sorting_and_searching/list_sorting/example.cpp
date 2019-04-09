/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.cpp
 * @author Ivan Filipov
 * @date   12.2018
 * @brief  Example usage and test of merge sort and
 *         insertion sort on singly linked list.
 */

#include <iostream> // std::cout
#include <cstdlib>  // std::rand(), std::srand()
#include <ctime>    // std::time()

#include "../../../utils/student.h"
#include "minimal_list.hpp"   // minimal slightly linked list

/// test merge sort on fixed linked list
void test_custom_merge_sort() {
	
	std::cout << "MERGE sort testing" << std::endl
		      << "------------------"
		      << std::endl
		      << std::endl;
	
	dsa::minimal_list<int> list;
	
	for (int i = 0; i < 10; i++)
		list.push_back(std::rand() % 100);

	std::cout << "starting list items : \n";
	list.print_elems(std::cout);
	list.sort();
	std::cout << "sorted list items : \n";
	list.print_elems(std::cout);
	
	
	dsa::minimal_list<dsa::student> st_list = { { "Ivancho", 40000 }, { "Mariika", 25000 },
										      { "Gencho", 50001 }, { "Pencho", 25000 },
										      { "Genka", 42000 }, { "Penka", 25000 },
										      { "Kalin", 40000 }, { "Kalinka", 25000 } };
	std::cout << "\nstarting students list : \n";
	st_list.print_elems(std::cout);
	st_list.sort();
	std::cout << "sorted list items by name (using operator<) : \n";
	st_list.print_elems(std::cout);
	std::cout << std::endl << std::endl;
}

/// test insertion sort on fixed linked list
void test_custom_insertion_sort() {
	
	std::cout << "Insertion sort testing" << std::endl
		      << "------------------"
		      << std::endl
		      << std::endl;
	
	dsa::minimal_list<int> list;
	
	for (int i = 0; i < 10; i++)
		list.push_back(std::rand() % 100);

	std::cout << "starting list items : \n";
	list.print_elems(std::cout);
	list.slow_sort();
	std::cout << "sorted list items : \n";
	list.print_elems(std::cout);
	
	dsa::minimal_list<dsa::student> st_list = { { "Ivancho", 40000 }, { "Mariika", 25000 },
										      { "Gencho", 50001 }, { "Pencho", 25000 },
										      { "Genka", 42000 }, { "Penka", 25000 },
										      { "Kalin", 40000 }, { "Kalinka", 25000 } };
	std::cout << "\nstarting students list : \n";
	st_list.print_elems(std::cout);
	st_list.slow_sort();
	std::cout << "sorted list items by name (using operator<) : \n";
	st_list.print_elems(std::cout);
	std::cout << std::endl << std::endl;
}

int main() {
	
	/* seed the random generator */
	std::srand(std::time(nullptr));
	/* test merge sort implementation */
	test_custom_merge_sort();
	/* test insertion sort implementation */
	test_custom_insertion_sort();
	
	return 0;
}
