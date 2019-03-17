/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   bs_tree.cpp
 * @author Ivan Filipov
 * @date   02.2019
 * @brief  Example implementation of classic binary search tree.
 *
 * @see https://en.wikipedia.org/wiki/Binary_search_tree
 */

#include <stdexcept> // std::logic_error
#include <cstdio>    // printf()
#include <cmath>     // log10()
// needed for printing tree nice looking in the console
#include <queue>   // std::queue
#include <utility> // std::pair

#include "bs_tree.h"

bs_tree::bs_tree(): root(nullptr) {
	//...
}

bs_tree::~bs_tree() {

	destroy_tree_rec(root);
}

bs_tree::bs_tree(const bs_tree& rhs) {

	copy_from(rhs);
}

bs_tree& bs_tree::operator=(const bs_tree& rhs) {

	if (this != &rhs) {
		destroy_tree_rec(root);
		root = nullptr;
		copy_from(rhs);
	}

	return *this;
}

void bs_tree::destroy_tree_rec(node* root) {

	if (root != nullptr) {
		destroy_tree_rec(root->left_ptr); // go left
		destroy_tree_rec(root->right_ptr); // then go right
		// after that free the memory
		delete root;
	}
}

void bs_tree::copy_from(const bs_tree& other) {

	copy_tree_rec(root, other.root);
}

void bs_tree::copy_tree_rec(node*& dest_root, node* src_root) {

	if (src_root == nullptr) {
		dest_root = nullptr;
		return;
	}
	// copy the root
	dest_root = new node(src_root->key, src_root->data);
	// copy first left sub-tree, then the right
	copy_tree_rec(dest_root->left_ptr,  src_root->left_ptr);
	copy_tree_rec(dest_root->right_ptr, src_root->right_ptr);
}

void bs_tree::insert_rec(node*& root, const key_type& key, const data_type& data) {
	// we have found a leaf
	if (root == nullptr) {
		root = new node(key, data);
		return;
	}
	// already exists
	if (key == root->key)
		throw std::logic_error("insertion fail : elem with this key already exists!\n");
	// try to insert in the right
	if (key > root->key) {
		insert_rec(root->right_ptr, key, data);
		return;
	}
	// try to insert in the left
	if (key < root->key) {
		insert_rec(root->left_ptr, key, data);
		return;
	}
}

data_type bs_tree::find_rec(node* root, const key_type& key) const {
	// can't find it...
	if (root == nullptr)
		throw std::logic_error("no element with such key!");
	// is on this node
	if (key == root->key)
		return root->data;
	// search right sub tree
	if (key > root->key)
		return find_rec(root->right_ptr, key);
	// search left sub tree
	if (key < root->key)
		return find_rec(root->left_ptr, key);
	// won't get here, but stops compiler's warnings/errors(*errors on clang)
	throw std::logic_error("no element with such key!");
}

// node*& because we have pointer redirections
void bs_tree::remove_rec(node*& root, const key_type& key) {
	// search phase:
	// there isn't elem with key "key"
	if (root == nullptr)
		throw std::logic_error("no element with such key!");
	// search right sub-tree
	if (key > root->key) {
		remove_rec(root->right_ptr, key);
		return;
	}
	// search left sub-tree
	if (key < root->key) {
		remove_rec(root->left_ptr, key);
		return;
	}
	//

	// remove phase :
	// simple leaf
	if (!root->left_ptr && !root->right_ptr) {
		delete root;
		root = nullptr;
		return;
	}
	// have two children
	if (root->left_ptr != nullptr && root->right_ptr != nullptr) {
		// finding the max elem in the left sub-tree
		// and copy it's properties
		node* tmp = root->left_ptr;

		while (tmp->right_ptr != nullptr)
			tmp = tmp->right_ptr;
		
		root->data = tmp->data;
		root->key = tmp->key;

		// removing the switched elem
		// which is a leaf or node with one child
		// and the removal will be a trivial operation
		remove_rec(root->left_ptr, root->key);
	} else {  // the root have only one child
		node* destroyer = root;
		// have only left child
		if (root->left_ptr)
			root = root->left_ptr;
		else //have only right child
			root = root->right_ptr;
		
		delete destroyer; //release wanted node
	}
	//
}

// using left - root - right tree iteration
void bs_tree::print_sorted_keys_rec(node* root) const {
	// root != nullptr
	if (root) {
		print_sorted_keys_rec(root->left_ptr);
		printf("{ key: %d , data : %d }\n",root->key,root->data);
		print_sorted_keys_rec(root->right_ptr);
	}
}

unsigned int bs_tree::get_height_rec(node* root) const {

	if (root == nullptr)
		return 0;
	// left and right sub-tree's height 
	unsigned int left_height = get_height_rec(root->left_ptr);
	unsigned int right_height = get_height_rec(root->right_ptr);
	// return the height including this node
	return 1 + ((left_height > right_height) ? left_height : right_height);
}
 
void bs_tree::insert(const key_type& key, const data_type& data) {

	insert_rec(root, key, data);
}

data_type bs_tree::find(const key_type& key) const {

	return find_rec(root, key);
}

unsigned int bs_tree::get_height() const {

	return get_height_rec(root);
}

key_type bs_tree::get_max_key() const {

	if (root == nullptr)
		return 0;

	node* it = root;

	while (it->right_ptr)
		it = it->right_ptr;

	return it->key;
}

void bs_tree::remove(const key_type& key) {

	remove_rec(root,key);
}

void bs_tree::print_sorted_keys() const {

	printf("\niterating the tree left - root - right looks like : \n\n");
	print_sorted_keys_rec(root);
}


void bs_tree::print_tree() const {

	printf("\nthe tree looks something like this :\n\n");
	
	unsigned int height = get_height();
	unsigned int cur_lvl = 0;
	// how many spaces between the elements : 
	// the maximum value of children in a binary tree
	// with height h is 2 ^ ( h - 1) why?
	unsigned int max_childern = 1 << (height - 1);
	// we will have at least one space between each children
	max_childern <<= 1; // *= 2
	// which is the longest number
	unsigned int max_key = get_max_key();
	// how many digits it has
	unsigned int max_digits = static_cast<unsigned int>(log10(max_key) + 1);
	// how many cells do we need in each line
	unsigned int indent = max_childern * (max_digits + 1) - 1;
	// preforming BFS - pushing nodes form the tree and
	// empty ones in order to make the "drawing" easier
	// key - level of node
	std::queue<std::pair<node*, unsigned int>> wave;
	wave.push(std::make_pair(root, cur_lvl + 1)); // adding the root and level to the front of the wave

	while (cur_lvl <= height) { // until end is reached
		if (cur_lvl < wave.front().second) {
			cur_lvl = wave.front().second;
			printf("\n");
	
			if (cur_lvl > height)
				return;
			// on each line below indent will be index / 2
			indent >>= 1;
		}
		
		for (unsigned int i = 0; i < indent; i++)
			putchar(' ');

		if (wave.front().first != nullptr)
			printf("%u", wave.front().first->key);
		else
			putchar(' '); // empty node

		for (unsigned int i = 0; i <= indent; i++)
			putchar(' ');

		// if real node, pushing its children into the wave
		if (wave.front().first != nullptr) {
			if (wave.front().first->left_ptr != nullptr)
				wave.push(std::make_pair(wave.front().first->left_ptr, wave.front().second + 1));
			else
				wave.push(std::make_pair(nullptr, wave.front().second + 1));

			if (wave.front().first->right_ptr != nullptr)
				wave.push(std::make_pair(wave.front().first->right_ptr, wave.front().second + 1));
			else
				wave.push(std::make_pair(nullptr, wave.front().second + 1));
		} else { //fake node
			// pushing two fake children
			wave.push(std::make_pair(nullptr, wave.front().second + 1));
			wave.push(std::make_pair(nullptr, wave.front().second + 1));
		}
		wave.pop();
	}
}
