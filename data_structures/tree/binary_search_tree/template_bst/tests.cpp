/*
 * Some tests for our custom BST.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>
 
#include "tests.h"
#include "bs_tree.hpp"
#include "../../../../utils/student.h"

void run_basic_tests() {
	// create empty tree
	dsa::bs_tree<dsa::student> tree;
	// add some elements
	tree.insert({ "Ivancho", 40000 });
	tree.insert({ "Mariika", 25000 });
	tree.insert({ "Gencho", 50001 });
	tree.insert({ "Pencho", 25000 });
	tree.insert({ "Genka", 42000 });
	tree.insert({ "Penka", 25000 });
	tree.insert({ "Kalin", 40000 });
	tree.insert({ "Kalinka", 25000 });

	std::cout << "\ntree's height = " << tree.get_height() << std::endl;
	tree.print_sorted_keys(std::cout);
	
	std::cout << "\n\nsearching for Ivancho :" << std::endl;
	try {
		const dsa::student& s = tree.search({ "Ivancho", 40000 });
		std::cout << "found! His fn is : " << s.fn << std::endl;
	} catch (...) {
		std::cout << "not found!" << std::endl;
	}
	
	std::cout << "\n\nsearching for Ivan :" << std::endl;
	try {
		const dsa::student& s = tree.search({ "Ivan", 200 });
		std::cout << "found! His fn is : " << s.fn << std::endl;
	} catch (...) {
		std::cout << "not found!" << std::endl;
	}

	std::cout << "\nremoving \"Genka\"...";
	try {
		tree.remove({ "Genka", 42000 });
		std::cout << "done!" << std::endl;
	} catch(...) {}
	tree.print_sorted_keys(std::cout);
	std::cout << std::endl;
}
