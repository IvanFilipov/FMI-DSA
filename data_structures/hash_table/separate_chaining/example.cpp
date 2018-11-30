/*
 * Example usage of separate chaining hash table.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>
#include "separate_chaining_hash.h"
#include "../hash_table_tests.hpp"

int main() {

	std::cout << "######## SEPARATE CHAINING HASH TABLES #########\n\n";
		
	sp_ch_hash_table table;

	run_tests(table);

	return 0;
}


