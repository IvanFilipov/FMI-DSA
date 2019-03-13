/*******************************************************************************
* This file is part of the "Data structures and algorithms" course. FMI 2018/19
*******************************************************************************/

/**
 * @file   trie.h
 * @author Vasilena Peycheva
 * @date   03.04.2019
 * @brief  Example implementation of Trie (Prefix tree).
 *
 * @see https://en.wikipedia.org/wiki/Trie
 * @see https://medium.com/basecs/trying-to-understand-tries-3ec6bede0014
 */

#pragma once

#include <string> // std::string

namespace dsa {
/**
 * @class trie
 * @brief A trie is a tree-like data structure whose nodes store the letters of an alphabet. 
 *				Provide fast string searching. It is used for autocomplete,
 *				matching algorithms, spell checkers, etc.
 *
 * Time complexity of searching, inserting and deleting from the tree
 * depends on the length of the word "a" : O(a).
 */
class trie {
private:
	/// length of English alphabet
	static const size_t ALPHABET_SIZE = 26;
	/**
	*  @struct node
	*  @brief  An inner representation of each trie's "node".
	*/
	struct node {
		node* alphabet[ALPHABET_SIZE]; //!< pointers to next symbols 
		bool is_word; 				   //!< is end of a word
		/** Creates an empty node. */
		node(): is_word(false) {

			for (size_t i = 0; i < ALPHABET_SIZE; i++)
				alphabet[i] = nullptr;
		}
	};

	/* private data members */
	node* root; //!<the root of the tree

public:
	/* object life cycle */
	/** Creates trie_tree with one node - root node */
	trie();
	/** Frees all memory allocated. */
	~trie();
	/**
	 *  @brief     trie_tree is non-copyable.
	 *  @see https://docs.microsoft.com/en-us/cpp/cpp/explicitly-defaulted-and-deleted-functions?view=vs-2017
	 */
	trie(const trie &)            = delete;
	/// trie_tree is non-copyable.
	trie& operator=(const trie &) = delete;

private:
	/* helpers */
	// methods with suffix _rec are recursive functions:
	/**
	 *  @brief     free the memory for a trie_tree recursively
	 *  @param[in] root: the root node of the trie_tree to be freed.
	 */
	void clean_rec(node* root);
	/**
	 * @brief     Check if a string contains only alpha characters.
	 * @param[in] str: string to be checked.
	 * @retval    true if the string is single-word, false otherwise.
	 */
	static bool is_word(const std::string& str);
	/**
	 * @brief     Calculate the index of a given char in an alphabetic array.
	 * @param[in] c: char to be calculated.
	 * @retval    position of the char in English alphabets starting from zero
	 *
	 * example:
	 *  'a' -> 0
	 *  'z' -> 25
	 */
	static int indexation(char c);

public:
	/**
	 * @brief     Insert word in the trie tree.
	 * @param[in] word: the word to be inserted.
	 * @retval    true if the word is successfully inserted, false otherwise.
	 */
	bool insert(const std::string& word);
	/**
	 * @brief     Search for a word into the trie tree.
	 * @param[in] word: the word to be searched.
 	 * @retval    true if word is in the tree, false otherwise.
	 */
	bool search(const std::string& word);
	/// Clean working tree.
	void clean();
};
} // namespace dsa
