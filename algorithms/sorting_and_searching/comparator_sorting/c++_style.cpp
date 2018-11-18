/*
 * An example about usage of comparator function with sorting algorithms. C++ style. 
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

// how a sorting algorithm for sorting dynamic_array could look like :
template <typename Comparator>
void insertion_sort(student_vec& arr, Comparator cmp) {
	
	int size = arr.size();
	for (int i = 1; i < size; i++)
		for (int j = i; j > 0; j--)
			if (cmp(arr[j], arr[j - 1])) // slight difference is here
				std::swap(arr[j] , arr[j - 1]);
}

// STL like sorting function, random - access iterator is needed
// even better abstraction above the data
template <typename Iterator, typename Comparator>
void insertion_sort_iter(Iterator begin, Iterator end, Comparator cmp) {
	
	for (Iterator i = begin + 1; i < end; i++)
		for (Iterator j = i; j > begin; j--)
			if (cmp(*j, *(j - 1))) // slight difference is here
				std::swap(*j , *(j - 1));
}

bool old_style_cmp(const student& lhs, const student& rhs) {
	
	return lhs.fn < rhs.fn;
}

void test_template_comparator() {
	
	std::cout << "template comparator testing" << std::endl
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
	std::cout << "\n\nsorted by operator > for names :\n";
	insertion_sort(st_vec, std::greater<student>());
	st_vec.print_elems(std::cout);
	
	std::cout << "\n\nsorted by operator > for names :\n";
	insertion_sort(st_vec, std::less<student>());
	st_vec.print_elems(std::cout);
	
	std::cout << "\n\nsorted by old-style compare function for fn :\n";
	insertion_sort(st_vec, old_style_cmp);
	st_vec.print_elems(std::cout);

	std::cout << "\n\nsorted by custom lambda function for fn :\n";
	insertion_sort(st_vec, [] (const student& lhs, const student& rhs) -> bool {
		return lhs.fn > rhs.fn;
	});
	
	st_vec.print_elems(std::cout);
	std::cout << "------------------"
		      << std::endl;
}

void test_template_cmp_iter() {
	
	std::cout << "template comparator and iterator testing" << std::endl
		      << "------------------"
		      << std::endl;
	
	dsa::dynamic_array<int> arr = { 255, -124, 5, 11, 2, 6, 7 , -42, 13, 88, 21, 9, 8 };
	
	std::cout << "\ngiven elements :\n";
	arr.print_elems(std::cout);
	
	// sorting using operator<, std::grater is a shortcut for writing that function
	std::cout << "\n\nsorted by operator > :\n";
	insertion_sort_iter(arr.begin(), arr.end(), std::greater<int>());
	arr.print_elems(std::cout);
	// sorting with lambda
	std::cout << "\n\nsorted by lambda (<) :\n";
	insertion_sort_iter(arr.begin(), arr.end(), [] (int x, int y) { return x < y; });
	arr.print_elems(std::cout);
}

int main() {
	
	/* testing the sorting version with template comparator */
	test_template_comparator();
	/* testing the version with both template comparator and iterators */
	test_template_cmp_iter();
	
	return 0;
}
