/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   splay_tree.hpp
 * @author Ivan Filipov
 * @date   03.2019
 * @brief  Example implementation of Splay tree.
 *
 * @see  https://en.wikipedia.org/wiki/Splay_tree
 * @note the code is actually an rework for the given one in the link.
 */

#pragma once

namespace dsa {
/**
 * @class splay_tree
 * @brief A container that holds keys in order.
 *		  Provides fast lookups, inserts and deletions by key.
 *  
 * @tparam K: Type of keys. Should be comparable.
 *
 * A splay tree is a self-adjusting binary search tree
 * with the additional property that recently accessed elements are quick to access again.
 * All operations have O(log n) amortized time complexity.
 */
template<typename T>
class splay_tree {
private:
	/**
	 *  @struct node
	 *  @brief  An inner representation of each %splay_tree's "node".
	 */ 
	struct node {
		T key;            //!< key of the stored element
		node* left_ptr;   //!< a pointer to left child
		node* right_ptr;  //!< a pointer to right child
		node* parent_ptr; //!< a pointer to the parent node
		/** Creates an node by a given key. */
		node(const T& k):
			key(k), 
			left_ptr(nullptr),
			right_ptr(nullptr),
			parent_ptr( nullptr) {}
	};
	
	/* private data members */
	node*         root;   //!< the root of the tree
	unsigned long p_size; //!< number of stored elements
  
public:
	/* object life cycle */
	/** Creates %splay_tree with no elements */
	splay_tree();
	/** Copy constructor is forbidden */
	splay_tree(const splay_tree& rhs)            = delete;
	/** Assignment operator is forbidden */
	splay_tree& operator=(const splay_tree& rhs) = delete;
	/** Frees all memory allocated. */
	~splay_tree();
	
private:
	/* Helpers */
	/**
	 *  @brief     free the memory for a %splay_tree recursively.
	 *  @param[in] root: the root node of the %splay_tree to be freed.
	 */
	void destroy_tree_rec(node* root);
	
	/**
	  * @brief Helper for printing the contain of a %splay_tree recursively.
	  * @see   print_sorted_keys()
	  */
	void print_sorted_keys_rec(node* root, std::ostream& os) const;
	
	/* balancing helpers */
	/**
	 * @brief     Makes a left rotation on a subtree.
	 * @param[in] n_ptr: the root of the subtree to be rotated.
	 * @see https://en.wikipedia.org/wiki/Tree_rotation
	 *
	 * example:
	 *      1                         2
	 *      P                         Q
	 *     / \                       / \
	 *    A   Q          =>         P   C
	 *        /\                   / \
	 *       B  C                 A   B
	 */
	void left_rotate(node* n_ptr);
	
   /**
	 * @brief     Preforms a right rotation on a subtree.
	 * @param[in] n_ptr: the root of the subtree to be rotated.
	 * @see https://en.wikipedia.org/wiki/Tree_rotation
	 *
	 * example:
	 *      1                         2
	 *      Q                         P
	 *     / \                       / \
	 *    P   C          =>         A   Q
	 *   / \                           / \
	 *  A   B                         B   C 
	 */
	void right_rotate(node* n_ptr);
	
	/**
	 * @brief     Preforms "splaying" a node, moving it as closer
     *            as possible to the root of the tree.
	 * @param[in] n_ptr: the node to be moved.
	 */
	void splay(node* n_ptr);
	
	/**
	 * @brief     Puts a node in the place of other node.
	 * @param[in] to_replace_ptr:   the node to be replaced.
	 * @param[in] replace_with_ptr: the node to be placed.
	 */
	void replace(node* to_replace_ptr, node* replace_with_ptr);
	
	/**
	  * @brief Finds the minimum of all keys in a %splay_tree recursively.
	  * @param root_ptr: root of the tree
	  * @retval Pointer to the smallest element
	  */
	node* find_min_rec(node* root_ptr);
	
	/**
	  * @brief Finds the maximum of all keys in a %splay_tree recursively.
	  * @param root_ptr: root of the tree
	  * @retval Pointer to the largest element
	  */
	node* find_max_rec(node* root_ptr);
	
public:
	/* Interface */
	/**
	  * @brief     Search for a key into %splay_tree.
	  * @param[in] key: the key to be searched.
	  * @retval    read only reference to the element.
	  * @throw     std::logic_error if there is no such key.
	  * 
	  * @note Time complexity in the best and average case: O(logn),
	  *       but linear in elements count in the worst.
	  */
	const T& find(const T& key);
	
    /**
	  * @brief     Inserts a key into %splay_tree, if the key is not presenting.
	  * @param[in] key: the key to be inserted.
	  * @throw     std::logic_error if there is already such key inside the tree.
	  * 
	  * @note Time complexity in the best and average case: O(logn),
	  *       but linear in elements count in the worst.
	  * Attempts to move the key upward, so could it could be easily find. 
	  */
	void insert(const T& key);
	
	/**
	  * @brief     Removes a key from %splay_tree, if the key is presenting.
	  * @param[in] key: the key to be removed.
	  * @throw     std::logic_error if there is not a such key inside the tree.
	  * 
	  * @note Time complexity in the best and average case: O(logn),
	  *       but linear in elements count in the worst.
	  */
	void remove(const T& key);
		
	/** 
	 * @brief  Get the maximum key of elements stored in the %splay_tree.
	 * @retval a copy of the key.
	 * @throw  std::logic_error if the tree is empty.
	 */
	T get_max_key() {
		
		if (!root) throw std::logic_error("empty tree!");
		return find_max_rec(root)->key; 
	}
	
	/** 
	 * @brief  Get the minimum key of elements stored in the %splay_tree.
	 * @retval a copy of the key.
	 * @throw  std::logic_error if the tree is empty.
	 */
	T get_min_key() {
		
		if (!root) throw std::logic_error("empty tree!");
		return find_min_rec(root)->key; 
	}
	
	/** Check if the tree is empty */
	bool empty() const { return root == nullptr; }
	
	/** Gets the count of stored elements */
	unsigned long size() const { return p_size; }
	
	/** Frees the resources for the tree */
	void clear() { 
		
		destroy_tree_rec(root);
		p_size = 0;
	}
	
	/** 
	 * @brief  Outputs all keys stored in the %splay_tree in order.
	 * @param[in] os: output stream to write to.
	 * @retval a copy of the key.
	 * @throw  std::logic_error if the tree is empty.
	 *
	 * Iterate left-root-right through the tree gives the elements in order.
	 */
	void print_sorted_keys(std::ostream& os) const;
};

template<typename T>
splay_tree<T>::splay_tree(): 
	root(nullptr), p_size(0) { 
	//...
}

template<typename T>
splay_tree<T>::~splay_tree() {
	
	destroy_tree_rec(root);
}

template<typename T>
void splay_tree<T>::destroy_tree_rec(typename splay_tree<T>::node* root) {

	if (root != nullptr) {
		destroy_tree_rec(root->left_ptr);  // go left
		destroy_tree_rec(root->right_ptr); // then go right
		// after that free the memory
		delete root;
	}
}

template<typename T>
void splay_tree<T>::print_sorted_keys_rec(typename splay_tree<T>::node* root,
									      std::ostream& os) const {

	if (root) { // root != nullptr
		print_sorted_keys_rec(root->left_ptr, os);
		os << root->key;
		print_sorted_keys_rec(root->right_ptr, os);
	}
}

template<typename T>
void splay_tree<T>::left_rotate(typename splay_tree<T>::node* n_ptr) {
	
	node* right_sub_tree = n_ptr->right_ptr;
	// if we got a right sub tree, rotate it
    if (right_sub_tree) {
		n_ptr->right_ptr = right_sub_tree->left_ptr;
		if (right_sub_tree->left_ptr) 
			right_sub_tree->left_ptr->parent_ptr = n_ptr;
		right_sub_tree->parent_ptr = n_ptr->parent_ptr;
    }
    //
    // fix the parent of the subtree
    if (!n_ptr->parent_ptr) { 
		root = right_sub_tree;
    } else if (n_ptr == n_ptr->parent_ptr->left_ptr) { 
		n_ptr->parent_ptr->left_ptr = right_sub_tree;
    } else { 
		n_ptr->parent_ptr->right_ptr = right_sub_tree;
    }
    
    if (right_sub_tree) right_sub_tree->left_ptr = n_ptr;
    n_ptr->parent_ptr = right_sub_tree;
    //
}

template<typename T>
void splay_tree<T>::right_rotate(typename splay_tree<T>::node* n_ptr) {
	
    node* left_sub_tree = n_ptr->left_ptr;
    // if we got a left sub tree, rotate it
    if (left_sub_tree) {
      n_ptr->left_ptr = left_sub_tree->right_ptr;
      if (left_sub_tree->right_ptr) 
		left_sub_tree->right_ptr->parent_ptr = n_ptr;
      left_sub_tree->parent_ptr = n_ptr->parent_ptr;
    }
    //
	// fix the parent of the subtree
    if (!n_ptr->parent_ptr) {
		root = left_sub_tree;
    } else if (n_ptr == n_ptr->parent_ptr->left_ptr) {
    	n_ptr->parent_ptr->left_ptr = left_sub_tree;
    } else {
    	n_ptr->parent_ptr->right_ptr = left_sub_tree;
    }
    
    if(left_sub_tree) left_sub_tree->right_ptr = n_ptr;
    n_ptr->parent_ptr = left_sub_tree;
    //
}

template<typename T>
void splay_tree<T>::splay(typename splay_tree<T>::node* n_ptr) {
	// move the node up
    while (n_ptr->parent_ptr) {
		if (!n_ptr->parent_ptr->parent_ptr) {
			if (n_ptr->parent_ptr->left_ptr == n_ptr) {
				// right "Zig"
				right_rotate(n_ptr->parent_ptr);
			} else {
				// left "Zig"
				left_rotate(n_ptr->parent_ptr);
			}
		} else if (n_ptr->parent_ptr->left_ptr == n_ptr && 
				   n_ptr->parent_ptr->parent_ptr->left_ptr == n_ptr->parent_ptr) {
			// right "Zig-Zig"
			right_rotate(n_ptr->parent_ptr->parent_ptr);
			right_rotate(n_ptr->parent_ptr);
		} else if (n_ptr->parent_ptr->right_ptr == n_ptr && 
				   n_ptr->parent_ptr->parent_ptr->right_ptr == n_ptr->parent_ptr) {
			// left "Zig-Zig"
			left_rotate(n_ptr->parent_ptr->parent_ptr);
			left_rotate(n_ptr->parent_ptr);
		} else if (n_ptr->parent_ptr->left_ptr == n_ptr && 
				   n_ptr->parent_ptr->parent_ptr->right_ptr == n_ptr->parent_ptr) {
			// "Zig-Zag"
			right_rotate(n_ptr->parent_ptr);
			left_rotate(n_ptr->parent_ptr);
		} else {
			// "Zig-Zag"
			left_rotate(n_ptr->parent_ptr);
			right_rotate(n_ptr->parent_ptr);
		}
	}
}

template<typename T>
void splay_tree<T>::replace(typename splay_tree<T>::node* to_replace_ptr,
							typename splay_tree<T>::node* replace_with_ptr) {
	
	if (!to_replace_ptr->parent_ptr) {
		// change with the root
		root = replace_with_ptr;
	} else if (to_replace_ptr == to_replace_ptr->parent_ptr->left_ptr) {
		// change with left child
		to_replace_ptr->parent_ptr->left_ptr = replace_with_ptr;
	} else {
		// change with right child
		to_replace_ptr->parent_ptr->right_ptr = replace_with_ptr;
	}

	if (replace_with_ptr) {
		// change the parent
		replace_with_ptr->parent_ptr = to_replace_ptr->parent_ptr;
	}
}

template<typename T>
typename splay_tree<T>::node* splay_tree<T>::
	find_min_rec(typename splay_tree<T>::node* root_ptr) {
		
    while (root_ptr->left_ptr) 
		root_ptr = root_ptr->left_ptr;
	
    return root_ptr;
}

template<typename T>
typename splay_tree<T>::node* splay_tree<T>::
	find_max_rec(typename splay_tree<T>::node* root_ptr) {
		
    while (root_ptr->right_ptr) 
		root_ptr = root_ptr->right_ptr;
	
    return root_ptr;
}
  
template<typename T>
const T& splay_tree<T>::find(const T& key) {
	// as same as in an ordinary binary search tree
	node* it = root;
    while (it) {
		if (it->key > key) {
			it = it->right_ptr;
		} else if (it->key < key) {
			it = it->left_ptr;
		} else return it->key;
    }
    throw std::logic_error("no element with such key!");
}

template<typename T>
void splay_tree<T>::insert(const T& key) {
	
    node* it = root;
    node* p_ptr = nullptr;
    
	while (it) {
		p_ptr = it;
		// already exists
		if (it->key == key)
			throw std::logic_error("insertion fail : elem with this key already exists!\n");
			
		if (it->key > key) {
			// try to insert in the right
			it = it->right_ptr;
		} else {
			// try to insert in the left 
			it = it->left_ptr;
		}
	}
    // add a new leaf
    it = new node(key);
    it->parent_ptr = p_ptr;
    //
    
    // fix the parent
    if (!p_ptr) {
		root = it;
    } else if (p_ptr->key > it->key) { 
		p_ptr->right_ptr = it;
    } else { 
		p_ptr->left_ptr = it;
	}    
	//
    
    // move the new element upward
    splay(it);
    p_size++;
}

template<typename T>
void splay_tree<T>::remove(const T& key) {
  	// search phase
  	node* it = root;
    while (it) {
		if (it->key > key) {
			it = it->right_ptr;
		} else if (it->key < key) {
			it = it->left_ptr;
		} else break;
    }
    
	if (!it) throw std::logic_error("no element with such key!");
	//
    
    // move the element upwards
    splay(it);
    
    // fix the tree
    if (!it->left_ptr) {
		// if we have only right sub-tree
    	// place it on our place
		replace(it, it->right_ptr);
    } else if (!it->right_ptr) {
    	// same logic if only left sub tree
    	replace(it, it->left_ptr );
    } else {
		// if both sub-trees are there
		// get the smallest element
		node* smallest = find_min_rec(it->right_ptr);
		// fix it's parent
		if (smallest->parent_ptr != it) {
			replace(smallest, smallest->right_ptr);
			smallest->right_ptr = it->right_ptr;
			smallest->right_ptr->parent_ptr = smallest;
		}
		
		replace(it,smallest );
		smallest->left_ptr = it->left_ptr;
		smallest->left_ptr->parent_ptr = smallest;
    }
    //
    
    // free the element
    delete it;
    p_size--;
    //
}

template<typename T>
void splay_tree<T>::print_sorted_keys(std::ostream& os) const {

	os << "\niterating the tree left - root - right looks like : \n\n";
	print_sorted_keys_rec(root, os);
}

} // namespace dsa
