/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   hash_map.hpp
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Advanced implementation of hash table, using
 *         opened hashing (closed address) strategy -
 *         separate chaining. 
 *         Depends on some STL stuff as described below.
 * @see https://en.wikipedia.org/wiki/Hash_table
 */

#pragma once

/// toggles debug output. Value of 1 means print debug info, 0 - opposite
#define DEBUG_HASH 0

// include only if debugging is ON
#if DEBUG_HASH == 1
#include <iostream> // std::cout
#endif // DEBUG_HASH

#include <vector>      // std::vector
#include <list>        // std::list
#include <functional>  // std::hash
#include <utility>     // std::pair

namespace dsa {	
/**
 * @class hash_map
 * @brief An associative container that holds key-value pairs.
 *        Provides fast lookups, additions and removals - log(n) in average case.
 * @tparam Key: type of keys
 * @tparam Data: type of values
 * @tparam Hasher: hash function to be used, by default std::hash<Key>
 */
template<typename Key,
         typename Data,
		 typename Hasher = std::hash<Key>>
class hash_map {
private:
	/// each table element is a pair of key and data
	using table_elem = std::pair<Key, Data>;
	/// the table itself is a vector of lists, each list contains pairs -> key and data
	using hash_table = std::vector<std::list<table_elem>>;
	/// helper define for chain iterator
	using chain_iter = typename std::list<table_elem>::iterator;
	
private:	
	/* private data members */
	hash_table table;      //!< the whole table
	Hasher     hash_func; //!< the hash function object
	static const size_t BASE_SIZE = 256;     //!< initial size to be allocated
	static const size_t MAX_CHAIN_SIZE = 16; //!< what is the maximum size of each chain
	
public:
	/* object life cycle */
	/** Creates table with @c BASE_SIZE # of empty chains */
	hash_map(): table(BASE_SIZE) {}
	
	/** Creates table with @c BASE_SIZE # of empty chains and sets custom hash function */
	hash_map(const Hasher& hasher):
		table(BASE_SIZE), hash_func(hasher) {}
	// big 4?
	// - > the ones generated by the compiler himself will do the trick
private:
	/* helpers */
	/**
	 * @brief Calculates the hash for a key.
	 * @param[in] key: compute the hash of that key
	 * @retval index in the table in which that key should belong to
	 */
	size_t calc_hash(const Key& key);
	
	/** helper for re-sizing the hash table */
	void rehash();
	
public:
	/* interface */
	/**
	  * @brief     Get an element's data by key.
	  * @param[in] key: the key to be searched.
	  * @retval    data for that key.
	  * @throw     std::logic_error if there is no such key.
	  * 
	  * Time complexity in the best case: O(1),
	  * but linear in @c MAX_CHAIN_SIZE in the worst case.
	  */
	Data& find(const Key& key);
	
	/**
	  * @brief     Inserts a key-value pair into %hash_map, if the key is not presenting.
	  * @param[in] new_elem: element to be inserted.
	  * @throw     std::logic_error if there is already such key inside the hash table.
	  * 
	  * Time complexity in the best case: O(1),
	  * but linear in @c MAX_CHAIN_SIZE in the worst case.
	  */
	void insert(const table_elem& new_elem);
	
	/**
	  * @brief     Removes a pair by key from %hash_map, if the key is presenting.
	  * @param[in] key: the key of the pair to be removed.
	  * @throw     std::logic_error if there is not a such key inside the hash table.
	  * 
	  * Time complexity in the best case: O(1),
	  * but linear in elements count in the worst case.
	  */
	void erase(const Key& key);
	
	/** Access the data for a key. Insert the pair, if the key is missing. */
	Data& operator[](const Key& key);
	
	/** 
	 * @brief Get a vector from all elements stored into the hash map.
	 * 
	 * The easiest way to have an "observer"
	 * of our hash table is to provide a method
	 * which creates a vector from all of pairs stored
	 * into the hash map
	 * This "observer" can be used in print functions, accumulators and etc
	 * Complexity - linear in the count of stored pairs.
	 */
	std::vector<table_elem> to_vector() const; 
	
	/** Get the number of elements in the chain on a given index */
	size_t chain_size(size_t index) const { return table.at(index).size(); }
	
	/** Get the number of chains */
	size_t chain_count() const { return table.size(); }
	
	/** Get the maximum number of elements per chain. */
	size_t chain_max_size() const { return MAX_CHAIN_SIZE; }
};

template<typename Key, typename Data,
		 typename Hasher>
inline 
size_t hash_map<Key, Data, Hasher>::
	calc_hash(const Key& key) {
	
	return hash_func(key) % table.size();
}

template<typename Key, typename Data,
		 typename Hasher> 
void hash_map<Key, Data, Hasher>::
	rehash() {
#if DEBUG_HASH == 1
	// debug reasons
	std::cout << "\n...rehashing ...\n";
#endif // DEBUG_HASH
 	// taking all old elements
	hash_table old_table = std::move(table);
 	// in this line our table is empty object
 	// allocate enough memory
	table.resize(old_table.size() * 2, {});
	// copy elements, by re-calculating the hash values
	using chain = std::list<table_elem>;
	size_t index;
	for (const chain& list: old_table)         // for each chain ...
			for(const table_elem& el: list) {  // for each of its elements
				index = calc_hash(el.first);   // put it in the now table
				table[index].push_front(el);
			}        
#if DEBUG_HASH == 1
	// debug reasons
	std::cout << ".............\n";
#endif // DEBUG_HASH
}

template<typename Key, typename Data,
		 typename Hasher>
void hash_map<Key, Data, Hasher>::
	insert(const table_elem& new_elem) {
	// calculate where to add the new element using the hash function
	size_t index = calc_hash(new_elem.first);
	// first of all, check if the key already exists
	// searching for the exact same key
	chain_iter it = table[index].begin();
	for (; it != table[index].end(); ++it)
		if ((*it).first == new_elem.first)
			throw std::logic_error("this key is already taken!");
	// check if resizing is needed
	if (table[index].size() >= MAX_CHAIN_SIZE) {
		rehash();
		// calculate the hash again, because the table now have different size
		index = calc_hash(new_elem.first);
	}
	// add the new elem as a first in the list for O(1)
	table[index].push_front(new_elem);
#if DEBUG_HASH == 1
	std::cout << "stored at hash " << index << std::endl;
#endif
}

template<typename Key, typename Data,
		 typename Hasher>
Data& hash_map<Key, Data, Hasher>::
	find(const Key& key) {
	// calculate where to search for the element
	size_t index = calc_hash(key);
	// first of all, check if the key already exists
	// searching for the exact same key
	chain_iter it = table[index].begin();
	for (; it != table[index].end(); ++it)
		if ((*it).first == key)
			return (*it).second; 
	// haven't found it
	throw std::logic_error("no such key!");
}

template<typename Key, typename Data,
		 typename Hasher>
void hash_map<Key, Data, Hasher>::
	erase(const Key& key) {
	// calculate where to search for the element
	size_t index = calc_hash(key);
	// first of all, check if the key already exists
	// searching for the exact same key
	chain_iter it = table[index].begin();
	for (; it != table[index].end(); ++it) {
		if ((*it).first == key) {
			table[index].erase(it); // remove it for O(1)
			return;
		}
	}
	// haven't found it
	if (it == table[index].end())
		throw std::logic_error("no such key!");
}

template<typename Key, typename Data,
		 typename Hasher>
Data& hash_map<Key, Data, Hasher>::
	operator[](const Key& key) {
	// could be written much better, 
	// for example calc_hash(key) can be called
	// times here, but reusing other methods is easier...
	
	// try to get the data if key exists
	try {
		return find(key);
	} catch(...) {}
	// got here only if find fails
	insert(std::make_pair(key, Data{}));
	// return it
	return table[calc_hash(key)].front().second;
}

template<typename Key, typename Data,
		 typename Hasher>
std::vector<std::pair<Key, Data>> hash_map<Key, Data, Hasher>::
	to_vector() const {
	
	std::vector<std::pair<Key, Data>> res;
	
	using chain = std::list<table_elem>;
	for (const chain& list: table) 	 // for each chain ...
		for(const table_elem& el: list) // for each of its elements
			res.push_back(el);           // put it in result
	
	return res;
}
} // namespace dsa
