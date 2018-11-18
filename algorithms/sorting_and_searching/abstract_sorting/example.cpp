/*
 * Example usage of our abstract sorting algorithms.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>   // std::cout
#include <functional> // std::grater, std::less

#include "abstract_sorting.hpp"     // abstract sorting algorithms with STL
#include "../../../utils/student.h" // class for students
#include "../../../data_structures/dynamic_array/dynamic_array.hpp" // custom vector

using namespace dsa; // include name
// typedef like modern syntax
using student_vec = dynamic_array<student>;

void test_abstract_sorts() {
	
	std::cout << "abstract sorting algorithms testing" << std::endl
		      << "------------------"
		      << std::endl
		      << std::endl;
		      
	student_vec st_vec = { { "Ivancho", 40000 }, { "Mariika", 25000 },
						   { "Gencho", 50001 }, { "Pencho", 25000 },
						   { "Genka", 42000 }, { "Penka", 25000 },
						   { "Kalin", 40000 }, { "Kalinka", 25000 } };

	std::cout << "\ngiven elements :\n";
	st_vec.print_elems(std::cout);
	
	// sorting using operator<, std::grater is a shortcut for writing that function
	std::cout << "\n\nsorted by dsa::insertion_sort with operator > for names :\n";
	dsa::insertion_sort(st_vec.begin(), st_vec.end(), std::greater<student>());
	st_vec.print_elems(std::cout);
	
	std::cout << "\n\nsorted by std::sort (probably a version of quick sort) :\n";
	std::sort(st_vec.begin(), st_vec.end());
	st_vec.print_elems(std::cout);
	
	std::cout << "\n\nsorted by std::stable_sort (probably a version of merge sort) :\n";
	std::stable_sort(st_vec.begin(), st_vec.end());
	st_vec.print_elems(std::cout);
	
	std::cout << "\n\nsorted by dsa::merge_sort with operator < for names :\n";
	dsa::merge_sort(st_vec.begin(), st_vec.end(), std::less<student>());
	st_vec.print_elems(std::cout);
	
	std::cout << "\n\nsorted by dsa::heap_sort with operator > for names :\n";
	dsa::heap_sort(st_vec.begin(), st_vec.end(), std::greater<student>());
	st_vec.print_elems(std::cout);
}



int main() {
	
	/* testing abstract version of insertion, merge and heap sort */
	test_abstract_sorts();
	
	return 0;
}
