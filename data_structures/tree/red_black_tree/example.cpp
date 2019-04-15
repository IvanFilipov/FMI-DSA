/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.cpp
 * @author Ivan Filipov
 * @date   03.2019
 * @brief  Example usage and some tests
 *         for our implementation of 
 *         the left-leaning red-black tree.
 */

#include <cstdlib> // rand(), srand()
#include <ctime>   // time()
#include <cstdio>  // std::printf()
#include <string>  // std::string

#include "llrb_tree.hpp" // dsa::llrb_tree

using dsa::llrb_tree;

/* test configuration constants */ 
const unsigned int N_INSERT = 16;  //!< how many elements to insert in our tree
const unsigned int MAX_KEY  = 51;  //!< the max value a key can have
const unsigned int MAX_DATA = 101; //!< data range is [-MAX_DATA;+MAX_DATA]
const unsigned int N_FIND   = 10;  //!< how many find test to be done
const unsigned int N_REMOVE = 10;  //!< number of remove tests

/// helper function for printing the sorted pairs,
/// stored into a %llrb_tree<int, int>
void print_key_values(const llrb_tree<int, int>& tree) {
	
	auto pairs = tree.get_sorted_pairs();
	for (auto p: pairs)
		std::printf("{ key: %d, value : %d }\n", p.first, p.second);
}

/// some insert-find-remove tests
/// on a randomly generated %llrb_tree
void run_basic_tests() {
	
	srand(time(NULL));
	
	std::printf("running tests on a randomly generated\n");
	std::printf("left leaning red - black tree\n");
	
	llrb_tree<int, int> tree;
	int cur_key, cur_val;
	
	// inserting N_INSERT elements into our tree
	std::printf("\n\n---------=insertion phase=---------\n\n");
	
	for (unsigned int i = 0; i < N_INSERT; ++i) {
		cur_key = rand() % MAX_KEY;
		cur_val = rand() % MAX_DATA;
		// positive or negative
		cur_val = ((rand() % 2) ? cur_val : -cur_val);

		printf("\ninserting element with key %d :\n", cur_key);

		try {
			tree.insert(cur_key, cur_val);
			std::printf("successfully inserted\n");
		} catch (std::logic_error& e) {
			std::printf("error : %s\n", e.what());
		}
	}

	print_llrb_tree(tree);
	std::printf("\n tree's height = %d \n", tree.get_height());
	print_key_values(tree);
	//
	
	// search for N_FIND keys
	printf("\n\n---------=search phase=---------\n\n");
	
	for (unsigned int i = 0; i < N_FIND; ++i) {
		cur_key = rand() % MAX_KEY;
		
		std::printf("\nsearching for element with key %d :\n", cur_key);

		try {
			cur_val = tree.find(cur_key);
			std::printf("element found! it's value is : %d\n", cur_val);
		} catch (std::logic_error& e) {
			std::printf("error : %s\n", e.what());
		}
	}
	//
	
	// removing N_REMOVE random keys
	printf("\n\n---------=remove phase=---------\n\n");
	
	for (unsigned int i = 0; i < N_REMOVE; ++i) {
		cur_key = rand() % MAX_KEY;

		std::printf("\nremoving element with key %d :\n", cur_key);

		try {
			tree.remove(cur_key);
			std::printf("successfully removed ! \n");
			print_llrb_tree(tree);
		} catch (std::logic_error& e) {
			std::printf("error : remove failed : %s\n", e.what());
		}
	}
	
	std::printf("\n tree's height = %d \n", tree.get_height());
	print_key_values(tree);
}

/// some custom tests and example usage
void run_custom_tests() {
	
	std::printf("\n\n\n");
	std::printf("running custom tests on a\n");
	std::printf("left leaning red - black tree\n");
	// create empty tree
	llrb_tree<int, std::string> tree;
	// add some elements
	tree.insert(40000, "Ivancho");
	tree.insert(25000, "Mariika");
	tree.insert(50001, "Gencho");
	tree.insert(20500, "Pencho");
	tree.insert(42000, "Genka");
	tree.insert(20050, "Penka");
	tree.insert(40004, "Kalin");
	tree.insert(20005, "Kalinka", true); // we can specify update

	std::printf("\ntree's height = %u\n", tree.get_height());
	auto pairs = tree.get_sorted_pairs();
	for (auto p: pairs) 
		std::printf("fn: %d, name: %s\n", p.first, p.second.c_str());
	
	print_llrb_tree(tree);
	
	std::printf("\n\nsearching for 40000 :\n");
	try {
		const std::string& s = tree.find(40000);
		std::printf("found! Paired name: %s\n", s.c_str());
	} catch (...) {
		std::printf("not found!\n");
	}
	
	std::printf("\n\ninserting {40000, \"Ivan\"} :\n");
	try {
		tree.insert(40000, "Ivan");
		std::printf("done!\n");
	} catch (std::logic_error& e) {
		std::printf("error: %s", e.what());
	}
	
	std::printf("\n\nupdating 40000 -> \"Ivan\"} :\n");
	try {
		tree.insert(40000, "Ivan", true);
		std::printf("done!\n");
	} catch (std::logic_error& e) {
		std::printf("error: %s", e.what());
	}
	
	std::printf("\n\nsearching for 40000 :\n");
	try {
		const std::string& s = tree.find(40000);
		std::printf("found! Paired name: %s\n", s.c_str());
	} catch (...) {
		std::printf("not found!\n");
	}
	
	std::printf("\nremoving 42000:");
	try {
		tree.remove(42000);
		std::printf("done!\n\n");
	} catch(...) {}
	
	pairs = tree.get_sorted_pairs();
	for (auto p: pairs) 
		std::printf("fn: %d, name: %s\n", p.first, p.second.c_str());
}



int main() {

	/* run the basic tests */
	run_basic_tests();
	
	/* run custom tests */
	run_custom_tests();	
	
	return 0;
}
