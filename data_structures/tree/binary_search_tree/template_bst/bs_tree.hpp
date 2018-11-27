/*
 * Example implementation of classic binary search tree.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once

#include <stdexcept> // std::logic_error
#include <iosfwd>    // std::ostream

namespace dsa {
template<typename T>
class bs_tree {

private:
	// each node have two pointer for it's children
	struct node {

		T key;               // stored object used as a key
		node*     left_ptr;  // a pointer to left child
		node*     right_ptr; // a pointer to right child

		node(const T& k = {}) : key(k),
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
	const T& search_rec(node* root, const T& key) const;
	// add new elem with "key" and "data" into tree with "root" 
	void insert_rec(node*& root, const T& key);
	// remove elem with "key" from tree with "root" 
	void remove_rec(node*& root, const T& key);
	// iterate left-root-right through the tree and output the elements
	void print_sorted_keys_rec(node* root, std::ostream& os) const;
	// get the maximum height of a tree with "root"
	unsigned int get_height_rec(node* root) const;

public:
	/* interface */
	// search for element with key, returns data if founded, throws an exception else
	// time complexity : O(logn) best case, O(n) avg and worst
	const T& search(const T& key) const;
	// insert an element with key and data if not presenting
	// time complexity : O(logn) best case, O(n) avg and worst
	void insert(const T& key);
	// remove an element by key if presenting
	// time complexity : O(logn) best case, O(n) avg and worst
	void remove(const T& key);
	// get the maximum height of a tree
	unsigned int get_height() const;
	// get the maximum key of elements stored in the tree
	T get_max_key() const;
	// iterate left-root-right through the tree and output the elements
	void print_sorted_keys(std::ostream& os) const;
};

template<typename T>
bs_tree<T>::bs_tree() : root(nullptr) {
	//...
}

template<typename T>
bs_tree<T>::~bs_tree() {

	destroy_tree_rec(root);
}

template<typename T>
bs_tree<T>::bs_tree(const bs_tree& rhs) {

	copy_from(rhs);
}

template<typename T>
bs_tree<T>& bs_tree<T>::operator=(const bs_tree& rhs) {

	if (this != &rhs) {
		destroy_tree_rec(root);
		root = nullptr;
		copy_from(rhs);
	}

	return *this;
}

template<typename T>
void bs_tree<T>::destroy_tree_rec(typename bs_tree<T>::node* root) {

	if (root != nullptr) {
		destroy_tree_rec(root->left_ptr); // go left
		destroy_tree_rec(root->right_ptr); // then go right
		// after that free the memory
		delete root;
	}
}

template<typename T>
void bs_tree<T>::copy_from(const bs_tree& other) {

	copy_tree_rec(root, other.root);
}

template<typename T>
void bs_tree<T>::copy_tree_rec(typename bs_tree<T>::node*& dest_root,
							   typename bs_tree<T>::node* src_root) {

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

template<typename T>
void bs_tree<T>::insert_rec(typename bs_tree<T>::node*& root, const T& key) {
	// we have found a leaf
	if (root == nullptr) {
		root = new node(key);
		return;
	}
	// already exists
	if (key == root->key)
		throw std::logic_error("insertion fail : elem with this key already exists!\n");
	// try to insert in the right
	if (key > root->key) {
		insert_rec(root->right_ptr, key);
		return;
	}
	// try to insert in the left
	if (key < root->key) {
		insert_rec(root->left_ptr, key);
		return;
	}
}

template<typename T>
const T& bs_tree<T>::search_rec(typename bs_tree<T>::node* root, 
								const T& key) const {
	// can't find it...
	if (root == nullptr)
		throw std::logic_error("no element with such key!");
	// is on this node
	if (key == root->key)
		return key;
	// search right sub tree
	if (key > root->key)
		return search_rec(root->right_ptr, key);
	// search left sub tree
	if (key < root->key)
		return search_rec(root->left_ptr, key);
	// won't get here, but stops compiler's warnings/errors(*errors on clang)
	//* possibly get here when using double/float
	throw std::logic_error("no element with such key!");
}

// node*& because we have pointer redirections
template<typename T>
void bs_tree<T>::remove_rec(typename bs_tree<T>::node*& root, const T& key) {
	// search phase :
	
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
}

// using left - root - right tree iteration
template<typename T>
void bs_tree<T>::print_sorted_keys_rec(typename bs_tree<T>::node* root,
									   std::ostream& os) const {
	// root != nullptr
	if (root) {
		print_sorted_keys_rec(root->left_ptr, os);
		os << root->key;
		print_sorted_keys_rec(root->right_ptr, os);
	}
}

template<typename T>
unsigned int bs_tree<T>::get_height_rec(typename bs_tree<T>::node* root) const {

	if (root == nullptr)
		return 0;
	// left and right sub-tree's height 
	unsigned int left_height = get_height_rec(root->left_ptr);
	unsigned int right_height = get_height_rec(root->right_ptr);
	// return the height including this node
	return 1 + ((left_height > right_height) ? left_height : right_height);
}

// the interface realizations are just callers to the recursive helpers 

template<typename T> 
void bs_tree<T>::insert(const T& key) {

	insert_rec(root, key);
}

// searches for a specific key, if there is
// such key, returns a copy of its data
// else throws logic_error exception
template<typename T>
const T& bs_tree<T>::search(const T& key) const {

	return search_rec(root, key);
}

template<typename T>
unsigned int bs_tree<T>::get_height() const {

	return get_height_rec(root);
}

template<typename T>
T bs_tree<T>::get_max_key() const {

	if (root == nullptr)
		return 0;

	node* it = root;

	while (it->right_ptr)
		it = it->right_ptr;

	return it->key;
}

template<typename T>
void bs_tree<T>::remove(const T& key) {

	remove_rec(root,key);
}

template<typename T>
void bs_tree<T>::print_sorted_keys(std::ostream& os) const {

	os << "\niterating the tree left - root - right looks like : \n\n";
	print_sorted_keys_rec(root, os);
}
} // namespace dsa
