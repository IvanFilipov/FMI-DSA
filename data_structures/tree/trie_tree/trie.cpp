/*******************************************************************************
* This file is part of the "Data structures and algorithms" course. FMI 2018/19
*******************************************************************************/

/**
 * @file   trie.cpp
 * @author Vasilena Peycheva
 * @date   03.04.2019
 * @brief  Example implementation of Trie (Prefix tree).
 *
 * @see https://en.wikipedia.org/wiki/Trie
 * @see https://medium.com/basecs/trying-to-understand-tries-3ec6bede0014
 */

#include "trie.h"

using dsa::trie;

trie::trie(): root(new node) {
	//...
}

trie::~trie() {

	clean_rec(root);
}

bool trie::insert(const std::string& word) {

	if (!is_word(word))
		return false;

	if (!root) // if the trie was cleaned
		root = new node(); // create root node (starting point)

	node* current = root; // starting point
	size_t index = 0;
	for (size_t i = 0; i < word.size(); i++) {
		// get the current letter index in node alphabet array
		index = indexation(word[i]);
		// if the letter is not already created (used with another word)
		if (!current->alphabet[index])
			//create new node from the current node alphabet[letter index]
			current->alphabet[index] = new node(); 
		current = current->alphabet[index];
	}
	// mark the last node as end of a word
	current->is_word = true;
	return true;
}

bool trie::search(const std::string & word) {

	if (!is_word(word) || !root)
		return false;

	node* current = root; // starting point
	size_t index = 0;
	for (size_t i = 0; i < word.size(); i++) {
		// get the current letter index in node alphabet array
		index = indexation(word[i]);
		// if the current letter is not created, then the word is not in the trie
		if (!current->alphabet[index])
			return false;
		current = current->alphabet[index];
	}
	// check if the last node is marked as word
	return current->is_word;
}

void dsa::trie::clean()
{
	clean_rec(root);
	root = nullptr;
}

void trie::clean_rec(node* root) {

	if (!root)
		return;

	// standard tree deletion
	for (size_t i = 0; i < ALPHABET_SIZE; i++) {
		if (root->alphabet[i])
			clean_rec(root->alphabet[i]);
	}
	
	delete root;
}

int trie::indexation(char c) {

	if (islower(c))
		return c - 'a';
	if (isupper(c))
		return c - 'A';

	return -1;
}

bool trie::is_word(const std::string& word) {

	for (char c: word) {
		if (!isalpha(c))
			return false;
	}
	
	return true;
}
