/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.cpp
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Example usage and test of our custom liner probing hash table. 
 */
 
#include <iostream> // std::cout

#include "linear_probing_hash.h"   // lin_pr_hash_table
#include "../hash_table_tests.hpp" // run_tests()

int main() {

	std::cout << "######## LINEAR PROBING HASH TABLE #########\n\n";
	
	lin_pr_hash_table table;

	run_tests(table);

	return 0;
}


