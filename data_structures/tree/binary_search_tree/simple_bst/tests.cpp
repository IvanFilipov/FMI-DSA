/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   tests.h
 * @author Ivan Filipov
 * @date   02.2019
 * @brief  Some tests for our custom BST.
 *
 * @see https://en.wikipedia.org/wiki/Binary_search_tree
 */

#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <stdexcept> // std::exception

#include "tests.h"
#include "bs_tree.h"

//@{
/** some constants, change them to customize the tests */
const unsigned int NELEM     = 16;  //!< how many elements to insert in our tree
const unsigned int MAX_KEY   = 51;  //!< the max value a key can have
const unsigned int MAX_DATA  = 101; //!< max data value is [-100;100]
const unsigned int NTRY      = 4;   //!< numbers of tries (search/remove)
//@}

/** fills a tree with random data by inserting NELEM elements */
static void init(bs_tree& tree) {

	data_type cur_data;
	key_type cur_key;

	for (unsigned int i = 0; i < NELEM; ++i) {
		cur_key  = rand() % MAX_KEY;
		cur_data = rand() % MAX_DATA;
		// positive or negative
		cur_data = ((rand() % 2) ? cur_data : -cur_data);
		printf("\ninserting element with key %d :\n", cur_key);

		try {
			tree.insert(cur_key, cur_data);
			printf("successfully inserted\n");
		} catch (std::logic_error& e) {
			printf("error : %s\n", e.what());
		}
	}
}

/** search some elements in a given tree */
static void search_test(const bs_tree& tree) {

	data_type value;
	key_type cur_key;

	for (unsigned int i = 0; i < NTRY; ++i) {
		cur_key = rand() % MAX_KEY;
		printf("\nsearching for element with key %d :\n", cur_key);

		try {
			value = tree.find(cur_key);
			printf("element found! it's value is : %d\n", value);
		} catch (std::logic_error& e) {
			printf("error : %s\n", e.what());
		}
	}
}

/** remove some elements from a given tree */
static void remove_test(bs_tree& tree) {

	key_type cur_key;

	for (unsigned int i = 0; i < NTRY; ++i) {
		cur_key = rand() % MAX_KEY;
		printf("\nremoving element with key %d :\n", cur_key);

		try {
			tree.remove(cur_key);
			printf("successfully removed ! \n");
		} catch (std::logic_error& e) {
			printf("error : %s\n", e.what());
		}
	}
}

void run_basic_tests() {
	// create empty tree
	bs_tree tree;
	// add some elements
	tree.insert(11, 1);
	tree.insert(9, 1);
	tree.insert(15, 1);
	tree.insert(12, 1);
	tree.insert(16, 1);
	tree.insert(10, 1);
	tree.insert(5, 1);
	tree.insert(3, 1);
	tree.insert(6, 1);
	tree.insert(13, 1);
	tree.print_tree();

	printf("\n tree's height = %d \n", tree.get_height());
	tree.print_sorted_keys();

	printf("\nremoving element with key 9\n");
	tree.remove(9);
	tree.print_tree();
	
	printf("\n tree's height = %d \n", tree.get_height());
	tree.print_sorted_keys();
}

void run_advanced_tests() {
	
	bs_tree tree;
	// seed the random generator
	srand(time(NULL));
	// create random tree
	init(tree);
	tree.print_tree();
	printf("\n tree's height = %d \n", tree.get_height());
	tree.print_sorted_keys();
	// search some random elements
	search_test(tree);
	// remove some random elements
	remove_test(tree);
	tree.print_tree();
	printf("\n tree's height = %d \n", tree.get_height());
	tree.print_sorted_keys();
}
