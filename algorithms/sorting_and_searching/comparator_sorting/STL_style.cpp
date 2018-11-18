/*
 * An example about usage of comparator function with sorting algorithms.
 * Advanced sorting functions implemented with STL functions over a custom vector. 
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>   // std::cout
#include <algorithm>  // std::swap
#include <functional> // std::grater, std::less

#include "../../../utils/student.h" // class for students
#include "../../../data_structures/dynamic_array/dynamic_array.hpp" // custom vector

using dsa::student; // include name
// typedef like modern syntax
using student_vec = dsa::dynamic_array<student>;

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
	std::cout << "\n\nsorted by insertion sort with operator > for names :\n";
	insertion_sort(st_vec.begin(), st_vec.end(), std::greater<student>());
	st_vec.print_elems(std::cout);
	
	std::cout << "\n\nsorted by std::sort (probably a version of quick sort) :\n";
	std::sort(st_vec.begin(), st_vec.end());
	st_vec.print_elems(std::cout);
	
	std::cout << "\n\nsorted by std::stable_sort (probably a version of merge sort) :\n";
	std::stable_sort(st_vec.begin(), st_vec.end());
	st_vec.print_elems(std::cout);
	
	std::cout << "\n\nsorted by std::stable_sort (probably a version of merge sort) :\n";
	std::stable_sort(st_vec.begin(), st_vec.end());
	st_vec.print_elems(std::cout);
	
	//std::cout << "\n\nsorted by operator > for names :\n";
	//insertion_sort(st_vec, std::less<student>());
	//st_vec.print_elems(std::cout);
	
	//std::cout << "\n\nsorted by old-style compare function for fn :\n";
	//insertion_sort(st_vec, old_style_cmp);
	//st_vec.print_elems(std::cout);

	//std::cout << "\n\nsorted by custom lambda function for fn :\n";
	//insertion_sort(st_vec, [] (const student& lhs, const student& rhs) -> bool {
		//return lhs.fn > rhs.fn;
	//});
	
	//st_vec.print_elems(std::cout);
	//std::cout << "------------------"
		    //  << std::endl;
}



int main() {
	
	/* testing abstract version of insertion, merge and heap sort */
	test_abstract_sorts();

	
	return 0;
}
