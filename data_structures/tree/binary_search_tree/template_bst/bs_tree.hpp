/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   bs_tree.hpp
 * @author Ivan Filipov
 * @date   02.2019
 * @brief  Example implementation of classic binary search tree.
 *
 * @see https://en.wikipedia.org/wiki/Binary_search_tree
 */

#pragma once

#include <stdexcept> // std::logic_error
#include <iosfwd>    // std::ostream

namespace dsa {
/**
 * @class bs_tree
 * @brief A container that holds items in order. Provides fast lookups.
 *  
 * @tparam T: Type of elements. Should be comparable.
 */
template<typename T>
class bs_tree {
private:
	/**
	 *  @struct node
	 *  @brief  An inner representation of each %bs_tree's "node".
	 */ 
	struct node {
		T     key;       //!< stored object used as a key
		node* left_ptr;  //!< a pointer to left child
		node* right_ptr; //!< a pointer to right child
		/** Creates an node by given key. By default tries to create an empty key. */
		node(const T& k = {}) : key(k),
			left_ptr(nullptr), right_ptr(nullptr) {}
	};
	
	/* private data members */
	node* root; //!<the root of the tree

public:
	/* object life cycle */
	/** Creates %bs_tree with no elements */
	bs_tree();
	/**
	  *  @brief     %bs_tree copy constructor.
	  *  @param[in] rhs: A %bs_tree of identical element type, from which to copy.
	  */
	bs_tree(const bs_tree& rhs);
	/**
	  *  @brief     %bs_tree assignment operator.
	  *  @param[in] rhs: A %bs_tree of identical element type, from which to copy.
	  */
	bs_tree& operator=(const bs_tree& rhs);
	/** Frees all memory allocated. */
	~bs_tree();

private:
	/* helpers */
	/** 
	  *  @brief     Copies all elements for another tree.
	  *  @param[in] rhs: tree from which to copy.
	  */
	void copy_from(const bs_tree& rhs);
	// methods with suffix _rec are recursive functions:
	/**
	 *  @brief     Frees the memory for a %bs_tree recursively.
	 *  @param[in] root: the root node of the %bs_tree to be freed.
	 */
	void destroy_tree_rec(node* root);
	/**
	  * @brief Helper for copy a %bs_tree recursively.
	  * @see   copy_from()
	  */
	void copy_tree_rec(node*& dest_root, node* src_root);
	/**
	  * @brief Helper for searching a key in a %bs_tree recursively.
	  * @see   find()
	  */
	const T& find_rec(node* root, const T& key) const;
	/**
	  * @brief Helper for inserting a key into a %bs_tree recursively.
	  * @see   insert()
	  */
	void insert_rec(node*& root, const T& key);
	/**
	  * @brief Helper for removing a key from a %bs_tree recursively.
	  * @see   remove()
	  */
	void remove_rec(node*& root, const T& key);
	/**
	  * @brief Helper for printing the contain of a %bs_tree recursively.
	  * @see   print_sorted_keys()
	  */
	void print_sorted_keys_rec(node* root, std::ostream& os) const;
	/**
	  * @brief Helper for getting the height of a %bs_tree recursively.
	  * @see   get_height()
	  */
	unsigned int get_height_rec(node* root) const;

public:
	/* interface */
	/**
	  * @brief     Search for a key into %bs_tree.
	  * @param[in] key: the key to be searched.
	  * @retval    read only reference to the element.
	  * @throw     std::logic_error if there is no such key.
	  * 
	  * @note time complexity in the best case: O(logn),
	  *       but linear in elements count in worst and average.
	  */
	const T& find(const T& key) const;
	/**
	  * @brief     Inserts a key into %bs_tree, if the key is not presenting.
	  * @param[in] key: the key to be inserted.
	  * @throw     std::logic_error if there is already such key inside the tree.
	  * 
	  * @note Time complexity in the best case: O(logn),
	  *       but linear in elements count in worst and average.
	  */
	void insert(const T& key);
	/**
	  * @brief     Removes a key from %bs_tree, if the key is presenting.
	  * @param[in] key: the key to be removed.
	  * @throw     std::logic_error if there is not a such key inside the tree.
	  * 
	  * @note Time complexity in the best case: O(logn),
	  *       but linear in elements count in worst and average.
	  */
	void remove(const T& key);
	/** Get the maximum height of a tree */
	unsigned int get_height() const;
	/** 
	 * @brief  Get the maximum key of elements stored in the %bs_tree.
	 * @retval a copy of the key.
	 * @throw  std::logic_error if the tree is empty.
	 */
	T get_max_key() const;
	/** 
	 * @brief  Outputs all keys stored in the %bs_tree in order.
	 * @param[in] os: output stream to write to.
	 * @retval a copy of the key.
	 * @throw  std::logic_error if the tree is empty.
	 *
	 * Iterate left-root-right through the tree gives the elements in order.
	 */
	void print_sorted_keys(std::ostream& os) const;
};

template<typename T>
bs_tree<T>::bs_tree(): root(nullptr) {
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
		destroy_tree_rec(root->left_ptr);  // go left
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
	// we have found a leaf, create the new element
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
const T& bs_tree<T>::find_rec(typename bs_tree<T>::node* root, 
								const T& key) const {
	// can't find it...
	if (root == nullptr)
		throw std::logic_error("no element with such key!");
	// is on this node
	if (key == root->key)
		return key;
	// search right sub tree
	if (key > root->key)
		return find_rec(root->right_ptr, key);
	// search left sub tree
	if (key < root->key)
		return find_rec(root->left_ptr, key);
	// won't get here, but stops compiler's warnings/errors(*errors on clang)
	//* possibly get here when using double/float
	throw std::logic_error("no element with such key!");
}

// node*& because we have pointer redirections
template<typename T>
void bs_tree<T>::remove_rec(typename bs_tree<T>::node*& root, const T& key) {
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
		else // have only right child
			root = root->right_ptr;
		
		delete destroyer; // release wanted node
	}
	//
}

template<typename T>
void bs_tree<T>::print_sorted_keys_rec(typename bs_tree<T>::node* root,
									   std::ostream& os) const {

	if (root) { // root != nullptr
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
	unsigned int left_height  = get_height_rec(root->left_ptr);
	unsigned int right_height = get_height_rec(root->right_ptr);
	// return the height including this node
	return 1 + ((left_height > right_height) ? left_height : right_height);
}

template<typename T> 
void bs_tree<T>::insert(const T& key) {

	insert_rec(root, key);
}

template<typename T>
const T& bs_tree<T>::find(const T& key) const {

	return find_rec(root, key);
}

template<typename T>
unsigned int bs_tree<T>::get_height() const {

	return get_height_rec(root);
}

template<typename T>
T bs_tree<T>::get_max_key() const {

	if (root == nullptr)
		throw std::logic_error("empty tree!");

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
