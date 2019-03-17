/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   llrb_tree.hpp
 * @author Ivan Filipov
 * @date   03.2019
 * @brief  Example implementation of Left-Leaning Red-Black tree.
 *
 * A variant of the original RB tree, created
 * by Robert Sedgewick to be easier to implement.
 * 
 * @see http://www.cs.princeton.edu/~rs/talks/LLRB/RedBlack.pdf
 * @see http://www.teachsolaisgames.com/articles/balanced_left_leaning.html
 * @note some implementation details are taken from those articles and from
 * @see  https://github.com/kevin-wayne/algs4/blob/master/src/main/java/edu/princeton/cs/algs4/RedBlackBST.java
 */

#pragma once

#include <stdexcept> // std::logic_error
#include <vector>    // std::vector
/* related to the debug print function */
#include <utility>   // std::pair
#include <cmath>     // log10()
#include <queue>     // std::queue
#include <cstdio>    // std::printf

namespace dsa {
/**
 * @class llrb_tree
 * @brief An associative container that holds key-value pairs. 
 *		  Elements are ordered by their keys.
 *		  Provides fast lookups, inserts and deletions by key.
 *  
 * @tparam K: Type of keys. Should be comparable.
 * @tparam V: Type of values.
 *
 * Due to the self balancing of this tree all operations
 * have O(logN) time complexity in best, worst and average case. 
 */
template<typename K, typename V>
class llrb_tree {
private:
	/**
	 * @enum color
	 * @brief marker for red or black node
	 */
	enum color: unsigned char {
		RED = 0, //!< red color
		BLACK    //!< black color
	};
	
	/**
	 *  @struct node
	 *  @brief  An inner representation of each %llrb_tree's "node".
	 */ 
	struct node {
		K key;           //!< key of the stored element
		V value;          //!< value of the stored element
		node* left_ptr;  //!< a pointer to left child
		node* right_ptr; //!< a pointer to right child
		color clr;       //!< the color of the incoming edge
		/** Creates an node by given pair of key and value. */
		node(const K& k, const V& v, color c = RED): 
			key(k), value(v),
			left_ptr(nullptr), 
			right_ptr(nullptr),
			clr(c) {}
	};
	
	/* private data members */
	node* root; //!<the root of the tree

public:
	/* object life cycle */
	/** Creates %llrb_tree with no elements */
	llrb_tree();
	
	/**
	  *  @brief     %llrb_tree copy constructor.
	  *  @param[in] rhs: A %llrb_tree of identical element type, from which to copy.
	  */
	llrb_tree(const llrb_tree& rhs);
	
	/**
	  *  @brief     %llrb_tree assignment operator.
	  *  @param[in] rhs: A %llrb_tree of identical element type, from which to copy.
	  */
	llrb_tree& operator=(const llrb_tree& rhs);
	
	/** Frees all memory allocated. */
	~llrb_tree();
	
private:
	/* helpers */
	/** 
	  *  @brief     copies all elements for another tree
	  *  @param[in] rhs: tree from which to copy.
	  */
	void copy_from(const llrb_tree&);
	
	// methods with suffix _rec are recursive functions:
	/**
	 *  @brief     free the memory for a %llrb_tree recursively
	 *  @param[in] root: the root node of the %llrb_tree to be freed.
	 */
	void destroy_tree_rec(node* root);
	
	/**
	  * @brief Helper for copy a %llrb_tree recursively.
	  * @see   copy_from()
	  */
	void copy_tree_rec(node*& dest_root, node* src_root);
	
	/**
	  * @brief Helper for searching a key in a %llrb_tree recursively.
	  * @see   find()
	  */
	const V& find_rec(node* root, const K& key) const;
	
	/**
	  * @brief Helper for inserting a key into a %llrb_tree recursively.
	  * @see   insert()
	  */
	node* insert_rec(node* root, const K& key, const V& value, bool update);
	
	/**
	  * @brief Helper for removing a key from a %llrb_tree recursively.
	  * @see   remove()
	  */
	node* remove_rec(node* root, const K& key);
	
	/**
	  * @brief Helper for getting a sorted vector of %llrb_tree key-value pairs.
	  * @see   get_sorted_pairs()
	  */
	void get_sorted_pairs_rec(node* root, std::vector<std::pair<K, V>>& pairs) const;
	
	/**
	  * @brief Helper for getting the height of a %llrb_tree recursively.
	  * @see   get_height()
	  */
	unsigned int get_height_rec(node* root) const;

	/* balancing helpers */
	/* for insertion */
	/**
	  * @brief     Check if a node has a red incoming edge.
	  * @param[in] n: node to be tested.
	  * @retval    true if the node is red colored.
	  */
	bool is_red(node* n_ptr);
	
	/**
	 * @brief     Makes a left rotation on a subtree.
	 * @param[in] n_ptr: the root of the subtree to be rotated.
	 * @retval    a pointer to root of the subtree after the rotation.
	 *
	 *
	 * example:
	 *      1                         2
	 *      F                         Q
	 *     / \ (r)                (r)/  \
	 *   A-E  Q          =>         F   R-Z
	 *    /\                       / \
	 *  G-P R-Z                  A-E  G-P
	 */
	node* left_rotate(node* n_ptr);
	
	/**
	 * @brief     Makes a right rotation on a subtree.
	 * @param[in] n_ptr: the root of the subtree to be rotated.
	 * @retval    a pointer to root of the subtree after the rotation.
	 *
	 *
	 * example:
	 *      2                         1
	 *      F                         Q 
	 *     / \ (r)                (r)/ \
	 *   A-E  Q          <=         F	R-Z
	 *   / \                       / \
	 *G-P   R-Z                  A-E  G-P
	 */
	node* right_rotate(node* n_ptr);
	
	/**
	 * @brief Returns the opposite color of a given one.
	 * @param[in] c: input color
	 * @retval @c RED, if   @p c == BLACK
	 * @retval @c BLACK, if @p c == RED
	 */
	color get_opposite_color(color c) {
		
		if (c == RED) return BLACK;
		else          return RED;
	}
	
	/**
	 * @brief     Changes the color of a node and it's two children.
	 * @param[in] n_ptr: the root to be color-flipped.
	 *
	 * example:
	 *
	 *     |           |(r)
	 *     M       =>  M
	 *(r) / \ (r)     / \
	 *   P   Q       P   Q
	 */
	void color_flip(node* n_ptr);

	/* deletion helpers */
	/**
	 * @brief fixes right-leaning reds and 
	 *		  eliminates 4-nodes on the way up.
	 * @param[in] n_ptr: root of a subtree to be fixed.
	 * @retval a pointer to the root of the result tree.
	 */
	node* fix_up(node* n_ptr);
	
	/**
	 * @brief Color flip and rotate on left if needed. 
	 * @param[in] n_ptr: root of a subtree to be fixed.
	 * @retval a pointer to the root of the result tree.
	 *
	 * @see http://www.cs.princeton.edu/~rs/talks/LLRB/RedBlack.pdf - page 61
	 */
	node* move_red_left(node* n_ptr);
	
	/**
	 * @brief Color flip and rotate on right if needed. 
	 * @param[in] n_ptr: root of a subtree to be fixed.
	 * @retval a pointer to the root of the result tree.
	 *
	 * @see http://www.cs.princeton.edu/~rs/talks/LLRB/RedBlack.pdf - page 56
	 */
	node* move_red_right(node* n_ptr);
	
	/**
	 * @brief Remove a node from the bottom level. 
	 * @param[in] n_ptr: root of the subtree, from which to remove.
	 * @retval a pointer to the root of the result tree.
	 *
	 * @note Due to the arrangement of an LLRB tree,
	 *	     the node cannot have a right child.
	 */
	node* delete_min(node* n_ptr);

public:
	/* interface */
	/**
	  * @brief     Search for a key into %llrb_tree, get the value for that key.
	  * @param[in] key: the key to be searched.
	  * @retval    read only reference to the value for that key.
	  * @throw     std::logic_error if there is no such key.
	  * 
	  */
	const V& find(const K& key) const;
	
	/**
	  * @brief     Inserts a key-value pair into %llrb_tree.
	  * @param[in] key: the key to be inserted
	  * @param[in] val: the value to be inserted
	  * @param[in] update: if set to true, an existing %value of @p key will be set to @p val.
	  * @param[in] update: if set to false(default value), the function tries to insert a new pair. 
	  * @throw     std::logic_error if @p update=false and there is already such key inside the tree.
	  */
	void insert(const K& key, const V& val, bool update = false);
	
	/**
	  * @brief     Removes a pair from %llrb_tree by key.
	  * @param[in] key: the key for removing.
	  * @throw     std::logic_error if there is not a such key inside the tree
	  */
	void remove(const K& key);
	
	/** Get the maximum height of a tree */
	unsigned int get_height() const;
	
	/** 
	 * @brief  Get the maximum key of elements stored in the %llrb_tree.
	 * @retval a copy of the key.
	 * @throw  std::logic_error if the tree is empty.
	 */
	K get_max_key() const;
	
	/** 
	 * @brief  Get a sorted vector of all pairs stored in the %llrb_tree.
	 * @retval vector of sorted keys.
	 *
	 * Iterate left-root-right through the tree gives the keys in order.
	 */
	std::vector<std::pair<K, V>> get_sorted_pairs() const;
	
	/** Check if the tree is empty */
	bool empty() const { return root == nullptr; }
		
	/** Frees the resources for the tree */
	void clear() { destroy_tree_rec(root); }
	/** 
	 * @brief  Beautifully prints a %llrb_tree<int, V> in the console.
	 * @param[in] tree: the tree to be outputted.
	 *
	 * This visualizer is a debug only function.
	 */
	template<typename D>
	friend void print_llrb_tree(llrb_tree<int, D>& tree);
};

template<typename K, typename V>
llrb_tree<K, V>::llrb_tree(): root(nullptr) {
	//...
}

template<typename K, typename V>
llrb_tree<K, V>::~llrb_tree() {

	destroy_tree_rec(root);
}

template<typename K, typename V>
llrb_tree<K, V>::llrb_tree(const llrb_tree& other) {

	copy_from(other);
}

template<typename K, typename V>
llrb_tree<K, V>& llrb_tree<K, V>::operator=(const llrb_tree& other) {

	if (this != &other) {
		destroy_tree_rec(root);
		root = nullptr;
		copy_from(other);
	}

	return *this;
}

template<typename K, typename V>
void llrb_tree<K, V>::copy_from(const llrb_tree& other) {

	copy_from_rec(root, other.root);
}

template<typename K, typename V>
void llrb_tree<K, V>::destroy_tree_rec(typename llrb_tree<K, V>::node* root) {

	if (root != nullptr) {
		destroy_tree_rec(root->left_ptr);  // go left
		destroy_tree_rec(root->right_ptr); // then go right
		// after that free the memory
		delete root;
	}
}

template<typename K, typename V>
void llrb_tree<K, V>::
	copy_tree_rec(typename llrb_tree<K, V>::node*& dest_root,
                  typename llrb_tree<K, V>::node* src_root) {

	if (src_root == nullptr) {
		dest_root = nullptr;
		return;
	}
	// copy the root
	dest_root = new node(src_root->key, src_root->value, src_root->clr);
	// copy first left sub-tree, then the right
	copy_tree_rec(dest_root->left_ptr,  src_root->left_ptr);
	copy_tree_rec(dest_root->right_ptr, src_root->right_ptr);
}

template<typename K, typename V>
const V& llrb_tree<K, V>::
	find_rec(typename llrb_tree<K, V>::node* root, 
             const K& key) const {
	// can't find it...
	if (root == nullptr)
		throw std::logic_error("no element with such key!");
	// is on this node
	if (key == root->key)
		return root->value;
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

template<typename K, typename V>
typename llrb_tree<K, V>::node* llrb_tree<K, V>
	::insert_rec(typename llrb_tree<K, V>::node* root,
				 const K& key, const V& val, bool update) {
	// insert red colored leaf
	if (root == nullptr) {
		root = new node(key, val, RED); 
		return root;
	}
	//

	// already exists
	if (key == root->key) {
		// update the value if wanted
		if (update) {
			root->value = val;
			throw update; // a tricky throw for faster return to the wrapper call
		}
	    // else, we don't support multi-keys
		throw std::logic_error("insertion fail : elem with this key already exists!\n");
	}
	//
	
	// inserting into a sub-tree
	if (key > root->key) {
		// insert in the right sub-tree
		root->right_ptr =
			insert_rec(root->right_ptr, key, val, update);		
	} else { // key < root->key (and edge cases on doubles, floats)
		// into the left sub-tree
		root->left_ptr =
			insert_rec(root->left_ptr, key, val, update);
	}
	//

	/* 
	 * So far everything is just like in an ordinary BST, but 
	 * after returning from the recursion we've got a work to do,
	 * in order to balance the tree.
	 */
	
	// fixes a right-leaning red node: this will assure,
	// that a 3-node is the left child
	if (is_red(root->right_ptr))
		 root = left_rotate(root);
	//
	
	// fixes two "reds" in a row: this will re-balance a 4-node
	if (is_red(root->left_ptr) && is_red(root->left_ptr->left_ptr))
		root = right_rotate(root);
	//

	// a map to a 2-3 tree,
	// splitting 4-nodes on the way up
	if (is_red(root->left_ptr) && is_red(root->right_ptr)) 
		color_flip(root);
	//

	// return the new root of the subtree that was just updated,
	// since rotations may have changed the value of the pointer.
	return root;
}


template<typename K, typename V>
typename llrb_tree<K, V>::node* llrb_tree<K, V>::
	remove_rec(node* root, const K& key) {

	// delete in the left sub-tree
	if (key < root->key) {
		// there is a left sub-tree
		if (root->left_ptr != nullptr) {
			// move red left if necessary
			if (!is_red(root->left_ptr) && !is_red(root->left_ptr->left_ptr)) 
				root = move_red_left(root);
			//
			
			//	move down(left)
			root->left_ptr =
				remove_rec(root->left_ptr, key); 
		}
	} else { // key >= root->key
		// if the left child is red, apply a rotation
		// to make the right child red
		if (is_red(root->left_ptr))
			root = right_rotate(root);
		//

		// equal key at the bottom level => deletion of a leaf
		if ((root->key == key) && (root->right_ptr == nullptr)) {
			delete root;
			return nullptr;
		}
		//

		// there is a right sub-tree =>
		// delete in it
		if (root->right_ptr != nullptr) {
			// move red right if necessary
			if ((!is_red(root->right_ptr)) && (!is_red(root->right_ptr->left_ptr)))
				root = move_red_right(root);
			//
			
			// equal not but not at the bottom level
			if (key == root->key) { 
				node* it = root->right_ptr;
				while (it->left_ptr)
					it = it->left_ptr;

				// copy the data and the key
				root->key  = it->key;
				root->value = it->value;
				// delete successor
				root->right_ptr = delete_min(root->right_ptr); 
			} else {
				//continue with the searching down
				root->right_ptr = remove_rec(root->right_ptr, key);
			}
			//
		}
	}

	// fix right-leaning red links
	// and eliminate 4-nodes on the way up
	return fix_up(root);
}

template<typename K, typename V>
void llrb_tree<K, V>::
	get_sorted_pairs_rec(typename llrb_tree<K, V>::node* root,
						std::vector<std::pair<K, V>>& pairs) const {
							
	if (root) {
		get_sorted_pairs_rec(root->left_ptr, pairs);
		pairs.emplace_back(root->key, root->value);
		get_sorted_pairs_rec(root->right_ptr, pairs);
	}
}

template<typename K, typename V>
unsigned int llrb_tree<K, V>::
	get_height_rec(typename llrb_tree<K, V>::node* root) const {

	if (root == nullptr)
		return 0;
	// left and right sub-tree's height 
	unsigned int left_height  = get_height_rec(root->left_ptr);
	unsigned int right_height = get_height_rec(root->right_ptr);
	// return the height including this node
	return 1 + ((left_height > right_height) ? left_height : right_height);
}


/* -------balancing helpers----------- */

template<typename K, typename V>
inline
bool llrb_tree<K, V>::is_red(node* n_ptr) {

	return ((n_ptr != nullptr) && (n_ptr->clr == RED));
}

template<typename K, typename V>
typename llrb_tree<K, V>::node* llrb_tree<K, V>::
	left_rotate(typename llrb_tree<K, V>::node* n_ptr) {

	node* t_ptr = n_ptr->right_ptr;
	n_ptr->right_ptr = t_ptr->left_ptr;
	t_ptr->left_ptr = n_ptr;

	t_ptr->clr = t_ptr->left_ptr->clr;
	t_ptr->left_ptr->clr = RED;

	return t_ptr;
}

template<typename K, typename V>
typename llrb_tree<K, V>::node* llrb_tree<K, V>::
	right_rotate(typename llrb_tree<K, V>::node* n_ptr) {
	
	node* t_ptr = n_ptr->left_ptr;
	n_ptr->left_ptr = t_ptr->right_ptr;
	t_ptr->right_ptr = n_ptr;

	t_ptr->clr = t_ptr->right_ptr->clr;
	t_ptr->right_ptr->clr = RED;

	return t_ptr;
}

template<typename K, typename V>
void llrb_tree<K, V>::
	color_flip(typename llrb_tree<K, V>::node* n_ptr) {

	n_ptr->clr = get_opposite_color(n_ptr->clr);

	if (n_ptr->left_ptr) {
		n_ptr->left_ptr->clr = 
			get_opposite_color(n_ptr->left_ptr->clr);
	}
	
	if (n_ptr->right_ptr) {
		n_ptr->right_ptr->clr = 
			get_opposite_color(n_ptr->right_ptr->clr);
	}
}

template<typename K, typename V>
typename llrb_tree<K, V>::node* llrb_tree<K, V>::
	fix_up(typename llrb_tree<K, V>::node* n_ptr) {
	// rotate-left right-leaning reds
	if (is_red(n_ptr->right_ptr)) 
		n_ptr = left_rotate(n_ptr);
	//
	// rotate-right red-red pairs
	if (is_red(n_ptr->left_ptr) && is_red(n_ptr->left_ptr->left_ptr))
		n_ptr = right_rotate(n_ptr);
	//
	// split 4 - nodes
	if (is_red(n_ptr->left_ptr) && is_red(n_ptr->right_ptr))
		color_flip(n_ptr);
	//
	return n_ptr;
}

template<typename K, typename V>
typename llrb_tree<K, V>::node* llrb_tree<K, V>::
	move_red_left(typename llrb_tree<K, V>::node* n_ptr) {
	
	color_flip(n_ptr);

	if (n_ptr->left_ptr && is_red(n_ptr->left_ptr->left_ptr)) {
		n_ptr = right_rotate(n_ptr);
		color_flip(n_ptr);
	}

	return n_ptr;
}

template<typename K, typename V>
typename llrb_tree<K, V>::node* llrb_tree<K, V>::
	move_red_right(typename llrb_tree<K, V>::node* n_ptr) {

	color_flip(n_ptr);

	if (n_ptr->right_ptr && is_red(n_ptr->right_ptr->left_ptr)) {
		n_ptr->right_ptr = right_rotate(n_ptr->right_ptr);
		n_ptr = left_rotate(n_ptr);
		color_flip(n_ptr);
	}

	return n_ptr;
}

template<typename K, typename V>
typename llrb_tree<K, V>::node* llrb_tree<K, V>::
	delete_min(typename llrb_tree<K, V>::node* n_ptr) {
	
	// remove node on bottom level
	// due to the arrangement of an LLRB tree, the node cannot have a
	// right child
	if (!n_ptr->left_ptr) {
		delete n_ptr;   // there is no such thing in JAVA code from the example
		return nullptr;	// because JAVA runtime has it's own garbage collector
	}

	// if these nodes are black, we need to rearrange this subtree to
	// force the left child to be red.
	if (!is_red(n_ptr->left_ptr) && !is_red(n_ptr->left_ptr->left_ptr))
		n_ptr = move_red_left(n_ptr);

	// continue recursing to locate the node to delete.
	n_ptr->left_ptr = delete_min(n_ptr->left_ptr);

	// fix right-leaning red nodes and eliminate 4-nodes on the way up.
	// need to avoid allowing search operations to terminate on 4-nodes,
	// or searching may not locate intended key.
	return fix_up(n_ptr);
}

/* ------- interface ----------- */

template<typename K, typename V>
const V& llrb_tree<K, V>::find(const K& key) const {

	return find_rec(root, key);
}

template<typename K, typename V>
void llrb_tree<K, V>::insert(const K& key, const V& val, bool update) {
	
	try {
		root = insert_rec(root, key, val, update);
	} catch (bool) {} // everything is ok on update
	
	// the root is always black
	root->clr = BLACK; 
}

template<typename K, typename V>
void llrb_tree<K, V>::remove(const K& key) {

	// will throw std::logic_error 
	// if there isn't such element
	// maybe reasonable only for debugging
	find_rec(root, key);

	// if not empty tree
	if (root) { 
		root = remove_rec(root, key);
		 // the color of the root is always black
		if (root) 
			root->clr = BLACK;
	}
}

template<typename K, typename V>
unsigned int llrb_tree<K, V>::get_height() const {

	return get_height_rec(root);
}

template<typename K, typename V>
K llrb_tree<K, V>::get_max_key() const {

	if (root == nullptr)
		throw std::logic_error("empty tree");

	node* it = root;
	while (it->right_ptr)
		it = it->right_ptr;

	return it->key;
}

template<typename K, typename V>
std::vector<std::pair<K, V>> llrb_tree<K, V>
	::get_sorted_pairs() const {
	
	std::vector<std::pair<K, V>> pairs;
	// pre-allocate enough memory
	unsigned int max_elems_count = 1 << (get_height() - 1);
	pairs.reserve(max_elems_count);
	
	get_sorted_pairs_rec(root, pairs);
	
	return pairs;
}

/* Debug helper */

template<typename V>
void print_llrb_tree(llrb_tree<int, V>& tree) {
	
	printf("\nthe tree looks something like this :\n\n");
	
	unsigned int height = tree.get_height();
	unsigned int cur_lvl = 0;
	// how many spaces between the elements : 
	// the maximum value of children in a binary tree
	// with height h is 2 ^ ( h - 1) why?
	unsigned int max_childern = 1 << (height - 1);
	// we will have at least one space between each children
	max_childern <<= 1; // *= 2
	// which is the longest number
	unsigned int max_key = tree.get_max_key();
	// how many digits it has
	unsigned int max_digits = static_cast<unsigned int>(std::log10(max_key) + 1);
	// how many cells do we need in each line
	unsigned int indent = max_childern * (max_digits + 1) - 1;
	// preforming BFS - pushing nodes form the tree and
	// empty ones in order to make the "drawing" easier
	// key - level of node
	using node_ptr = typename llrb_tree<int, V>::node*;
	std::queue<std::pair<node_ptr, unsigned int>> wave;
	wave.push(std::make_pair(tree.root, cur_lvl + 1)); // adding the root and level to the front of the wave

	while (cur_lvl <= height) { // until end is reached
			
		if (cur_lvl < wave.front().second) {
			cur_lvl = wave.front().second;
			std::putchar('\n');
	
			if (cur_lvl > height)
				return;
			// on each line below indent will be index / 2
			indent >>= 1;
		}
		
		for (unsigned int i = 0; i < indent; i++)
			putchar(' ');

		if (wave.front().first != nullptr)
			std::printf("%*d", max_digits, wave.front().first->key);
		else
			std::putchar(' '); // empty node

		for (unsigned int i = 0; i <= indent; i++)
			std::putchar(' ');

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
} // namespace dsa
