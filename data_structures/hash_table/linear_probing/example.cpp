/*
 * Example usage of linear probing hash table.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
#include <iostream>
#include "linear_probing_hash.h"
#include "../hash_table_tests.hpp"

int main() {

	std::cout << "######## LINEAR PROBING HASH TABLE #########\n\n";
	
	lin_pr_hash_table table;

	run_tests(table);

	return 0;
}


