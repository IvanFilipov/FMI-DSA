/*
 * Example usage of our custom BST.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <cstdio>
#include "tests.h"

int main() {
	
	printf("running basic tests on given binary search tree\n");
	run_basic_tests();

	printf("\n\nnow something unexpected ... \n");
	printf("completely random tree!\n\n");
	run_advanced_tests();

	return 0;
}
