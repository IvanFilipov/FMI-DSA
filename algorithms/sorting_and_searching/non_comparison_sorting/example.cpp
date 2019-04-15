/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.cpp
 * @author Ivan Filipov
 * @author Nikolay Babulkov	
 * @date   12.2019
 * @brief  An example usage of our non-comparison sorting implementations. 
 */

#include <cstdio> // std::printf(), std::putchar()

#include "non_comparison_sorting.h"

using std::printf;
using std::putchar;

/// printing array with contain which can be casted to integer
template <typename T>
void print_array(const std::vector<T>& arr) {
	
	for(int i : arr)
		printf("%d ", i);
	putchar('\n');
}

/// test counting sort on fixed array
void test_counting_sort() {
	
	std::vector<unsigned char> arr = { 124 ,5 , 11, 2, 6, 7 , 42 , 13 , 88 , 21 ,9 , 8 };
	printf("\n--------------\n");
	printf("\ngiven array : \n");
	print_array(arr);

	counting_sort(arr);
	
	printf("\nresult of counting sort : \n");
	print_array(arr);	
}

/// test MSD radix sort on fixed array of strings
void test_msd_radix() {
	
	std::vector<std::string> given_names = { "pesho", "gosho", "katrin", "jean",
	                                         "claude", "van", "damme" };
	printf("\n--------------\n");
	printf("\ngiven names : \n");
	for (const std::string& name : given_names)
		printf("\"%s\" ", name.c_str());
		
	msd_strings_radix_sort(given_names, 0, given_names.size(), 0);

	printf("\n\nafter MSD radix sorting : \n");
	for (const std::string& name : given_names)
		printf("\"%s\" ", name.c_str());
	putchar('\n');
}

/// test LSD radix sort on fixed array 
void test_lsd_radix() {
	
	std::vector<int> vec = { 22211, 555, 444, 1223, 1000, 322, 245, 231, 3, 23 };
	printf("\n--------------\n");
	printf("\ngiven array:\n");
	print_array(vec);
	
	lsd_radix_sort(vec);
	
	printf("\nsorted output from LSD radix sorting: \n");
	print_array(vec);	
}

int main() {
	
	/* run counting sort algorithm */
	test_counting_sort();
	/* run MSD strings radix sort algorithm */
	test_msd_radix();
	/* run LSD integers radix sort algorithm */
	test_lsd_radix();
	
	return 0;
}
