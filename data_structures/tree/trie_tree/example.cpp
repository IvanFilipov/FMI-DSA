/*******************************************************************************
* This file is part of the "Data structures and algorithms" course. FMI 2018/19
*******************************************************************************/

/**
 * @file   example.cpp
 * @author Vasilena Peycheva
 * @date   03.2019
 * @brief  Example usage of
 *         the trie tree.
 */


#include <iostream>
#include <fstream>
#include "trie.h"

using dsa::trie;

/// create dictionary from a given file with words
void create_dictionary(trie& tree, const std::string& filename) {

	std::ifstream in(filename);
	if (!in.is_open()) return;
	
	std::string word;
	while (true) {
		std::getline(in, word);
		
		if (!in) return;
			
		if (tree.insert(word))
			std::cout << "Successfully added <" + word + "> \n";
		else
			std::cout << "Failed to add <" + word + "> \n";
	}
}

/// create dictionary
/// search for words from the dictionary
void test() {

	trie trie;
	create_dictionary(trie, "dictionary.txt");
	std::string word;
		
	while (true) {
		std::cin >> word;
		
		if (word == "exit") break;

		if (trie.search(word))
			std::cout << " <" + word + "> is in the dictionary \n";
		else
			std::cout << "no match \n";
	} 
}

int main() {
	
	/* run the test */
	test();
	
	return 0;
}
