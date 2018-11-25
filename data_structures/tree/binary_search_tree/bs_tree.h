/*
 * Example implementation of classic binary search tree.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once

// for each element we have a key and some data
typedef int key_type;
typedef int data_type;

class bs_tree {

private:
	// each node have two pointer for it's children
	struct node {

		key_type  key;       // the key for comparing
		data_type data;      // the data 
		node*     left_ptr;  // a pointer to left child
		node*     right_ptr; // a pointer to right child

		node(key_type k = 0, data_type d = 0) : key(k), data(d),
			left_ptr(nullptr), right_ptr(nullptr) {
			//...
		}
	};
	/* private data members */
	//the root of the tree
	node* root;

public:
	/* object life cycle */
	bs_tree();
	bs_tree(const bs_tree& rhs);
	bs_tree& operator=(const bs_tree& rhs);
	~bs_tree();

private:

	/* helpers */
	// copies all elements for another tree
	void copy_from(const bs_tree& rhs);

	/// methods with suffix _rec are recursive functions :
	// destroy a tree with root "root" recursively
	void destroy_tree_rec(node* root);
	// copy a tree recursively
	void copy_tree_rec(node*& dest_root, node* src_root);
	// searching elem with key from tree with root "root"
	data_type search_rec(node* root, const key_type& key) const;
	// add new elem with "key" and "data" into tree with "root" 
	void insert_rec(node*& root, const key_type& key, const data_type& data);
	// remove elem with "key" from tree with "root" 
	void remove_rec(node*& root, const key_type& key);
	// iterate left-root-right through the tree and output the elements
	void print_sorted_keys_rec(node* root) const;
	// get the maximum height of a tree with "root"
	unsigned int get_height_rec(node* root) const;

public:
	/* interface */
	// search for element with key, returns data if founded, throws an exception else
	// time complexity : O(logn) best case, O(n) avg and worst
	data_type search(const key_type& key) const;
	// insert an element with key and data if not presenting
	// time complexity : O(logn) best case, O(n) avg and worst
	void insert(const key_type& key, const data_type& data);
	// remove an element by key if presenting
	// time complexity : O(logn) best case, O(n) avg and worst
	void remove(const key_type& key);
	// get the maximum height of a tree
	unsigned int get_height() const;
	// get the maximum key of elements stored in the tree
	key_type get_max_key() const;
	// iterate left-root-right through the tree and output the elements
	void print_sorted_keys() const;
	// beautifully prints the tree in the console
	void print_tree() const;
};
