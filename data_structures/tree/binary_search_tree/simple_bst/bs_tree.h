/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   bs_tree.h
 * @author Ivan Filipov
 * @date   02.2019
 * @brief  Example implementation of classic binary search tree.
 *
 * @see https://en.wikipedia.org/wiki/Binary_search_tree
 */

#pragma once

//@{
/** for each element we have a key and some data */
typedef int key_type;
typedef int data_type;
//@}

/**
 * @class bs_tree
 * @brief A container that holds key-value pairs.
 *        Ordered by keys. Provides fast lookups.
 */
class bs_tree {
private:
	/**
	 *  @struct node
	 *  @brief  An inner representation of each %bs_tree's "node".
	 */ 
	struct node {
		key_type  key;       //!< the key for comparing
		data_type data;      //!< the data 
		node*     left_ptr;  //!< a pointer to left child
		node*     right_ptr; //!< a pointer to right child
		/** Creates an node by given key and data. */
		node(key_type k = 0, data_type d = 0) : key(k), data(d),
			left_ptr(nullptr), right_ptr(nullptr) {
			//...
		}
	};
	
	/* private data members */
	node* root; //!< the root of the tree

public:
	/* object life cycle */
	/** Creates %bs_tree with no elements */
	bs_tree();
	
	/**
	  *  @brief     %bs_tree copy constructor.
	  *  @param[in] rhs: A %bs_tree, from which to copy.
	  */
	bs_tree(const bs_tree& rhs);
	
	/**
	  *  @brief     %bs_tree assignment operator.
	  *  @param[in] rhs: A %bs_tree, from which to copy.
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
	data_type find_rec(node* root, const key_type& key) const;
	
	/**
	  * @brief Helper for inserting a key-value pair into a %bs_tree recursively.
	  * @see   insert()
	  */
	void insert_rec(node*& root, const key_type& key, const data_type& data);
	
	/**
	  * @brief Helper for removing a key from a %bs_tree recursively.
	  * @see   remove()
	  */
	void remove_rec(node*& root, const key_type& key);
	
	/**
	  * @brief Helper for printing the contain of a %bs_tree recursively.
	  * @see   print_sorted_keys()
	  */
	void print_sorted_keys_rec(node* root) const;
	
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
	  * @retval    data for that key.
	  * @throw     std::logic_error if there is no such key.
	  * 
	  * @note time complexity in the best case: O(logn),
	  *       but linear in elements count in worst and average.
	  */
	data_type find(const key_type& key) const;
	
	/**
	  * @brief     Inserts a key-value pair into %bs_tree, if the key is not presenting.
	  * @param[in] key: the key to be inserted.
	  * @param[in] data: data to be inserted.
	  * @throw     std::logic_error if there is already such key inside the tree.
	  * 
	  * @note Time complexity in the best case: O(logn),
	  *       but linear in elements count in worst and average.
	  */
	void insert(const key_type& key, const data_type& data);
	
	/**
	  * @brief     Removes a pair by key from %bs_tree, if the key is presenting.
	  * @param[in] key: the key of the pair to be removed.
	  * @throw     std::logic_error if there is not a such key inside the tree.
	  * 
	  * @note Time complexity in the best case: O(logn),
	  *       but linear in elements count in worst and average.
	  */
	void remove(const key_type& key);
	
	/** Get the maximum height of a tree */
	unsigned int get_height() const;
	
	/** 
	 * @brief  Get the maximum key of elements stored in the %bs_tree.
	 * @retval the value of that key.
	 * @throw  std::logic_error if the tree is empty.
	 */
	key_type get_max_key() const;
	
	/** Check if the tree is empty */
	bool empty() const { return root == nullptr; }
	
	/** Frees the resources for the tree */
	void clear() { destroy_tree_rec(root); }
	
	/** 
	 * @brief  Outputs all keys stored in the %bs_tree in order.
	 *
	 * Iterate left-root-right through the tree gives the elements in order.
	 */
	void print_sorted_keys() const;
	
	/** Beautifully prints a %bs_tree in the console. */
	void print_tree() const;
};
