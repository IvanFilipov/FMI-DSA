/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   main.cpp
 * @author Ivan Filipov
 * @date   02.2019
 * @brief  Main for example usage
 *         and running some tests 
 *         for our custom splay tree.
 */

#include <cstdio>
#include "tests.h"

int main() {
	
	std::printf("running basic tests on given binary search tree\n");
	run_basic_tests();

	std::printf("\n\nnow something unexpected ... \n");
	std::printf("completely random tree!\n\n");
	run_advanced_tests();

	return 0;
}
