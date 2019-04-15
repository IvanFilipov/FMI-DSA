/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.cpp
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Example usage and test of our custom separate chaining hash table. 
 */

#include <iostream> // std::cout

#include "separate_chaining_hash.h" // sp_ch_hash_table
#include "../hash_table_tests.hpp"  // run_tests() 

int main() {

	std::cout << "######## SEPARATE CHAINING HASH TABLES #########\n\n";
		
	sp_ch_hash_table table;

	run_tests(table);

	return 0;
}
