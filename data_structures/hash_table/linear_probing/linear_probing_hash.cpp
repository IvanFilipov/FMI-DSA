/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   linear_probing_hash.cpp
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Basic implementation of hash table, using
 *         closed hashing (opened address) strategy -
 *         linear probing. 
 *         Depends only on our custom dynamic array.
 * @see https://en.wikipedia.org/wiki/Hash_table
 * @see https://en.wikipedia.org/wiki/Open_addressing
 */

#include "linear_probing_hash.h"

// include only if debugging is ON
#if DEBUG_HASH == 1
#include <iostream> //std::cin, std::cout
#endif // DEBUG_HASH

// the hash function, it is the most critical zone,
// the implementation below is pretty simple, consider
// using better hash functions in your applications
size_t lin_pr_hash_table::hash_func(const key_type& key, const size_t size) {
	// get the size of the string
	size_t result = key.size();
	// add the ASCII code for each character
	for (unsigned char c: key)
		result += c;

	// return result % size;
	// but better in case the SIZE is a power of 2
	return result & (size - 1);
}

void lin_pr_hash_table::rehash() {
	// debug print
#if DEBUG_HASH == 1
	std::cout << "\n...rehashing ...\n";
#endif // DEBUG_HASH

	// create a new table with double the size
	lin_pr_hash_table new_table(table.size() * 2);
	
	// for each element form the old table ...
	for (const table_elem& el: table) {
		if (el.key != "")
			new_table.insert(el.key, el.data); // put it in the new table
		// which will lead to re-calculating the hash values
	} 
	// for O(1) swaps the tables
	new_table.table.swap_with(table); 
	// now our table has the new elements, the old content,
	// will be freed in the destructor of new_table
#if DEBUG_HASH == 1
	std::cout << ".............\n";
#endif // DEBUG_HASH
}

void lin_pr_hash_table::insert(const key_type& key, const data_type& data) {
	// calculate where to add the new element using the hash function
	size_t index = hash_func(key, table.size());
	// check if resizing is needed
	if (logic_fill * 2 >= table.size()) {
		rehash();
		// calculate the hash again, because the table now have different size
		index = hash_func(key, table.size());
	}
	// searching for the first free position, maximum number of tries is the size
	unsigned int trys = table.size();
	// skip all taken cells
	while (table[index].key != "" && --trys) {
		if (table[index].key == key)  // handling same keys
			throw std::logic_error("this key is taken");
		index = (index + STEP) % table.size(); // taking by mod(size) means, make cycles
	}
	//successfully found a free position
	if (table[index].key == "") { 
		table[index].key  = key;
		table[index].data = data;
		logic_fill++;
	}
#if DEBUG_HASH == 1
	std::cout << "stored at hash " << index << std::endl;
#endif // DEBUG_HASH
}

data_type lin_pr_hash_table::get(const key_type& key) const {
	// calculate from where to search element with "key"
	size_t index = hash_func(key, table.size());	
	// we need to make some "probes" to find the element with exactly same key
	// maximum number of tries is the size
	size_t trys = table.size();
	// search until "size" tries, or same key, or empty cell
	while (table[index].key != key && table[index].key != "" && --trys)
		index = (index + STEP) % table.size();
	// if found return it's data
	if (table[index].key == key)
		return table[index].data;
	// not found
	throw std::logic_error("there isn't element with such key");
}

void lin_pr_hash_table::erase(const key_type& key) {
	// calculate from where to search element with "key"
	size_t index = hash_func(key, table.size());

	// same searching as in "get"
	size_t trys = table.size();

	while (table[index].key != key && table[index].key != "" && --trys)
		index = (index + STEP) % table.size();
	// not found
	if (table[index].key != key)
		throw std::logic_error("there isn't element with such key");

	// at "index" there is the wanted element, we need to make him
	// the last element in the "clustered" elements

	// where the next elem could be
	size_t next_ind = (index + STEP) % table.size();
	// moving it down the cluster
	while (table[next_ind].key != "") {
		// swap the keys and data-s
		std::swap(table[next_ind], table[index]);
		// go to the next element
		next_ind = (next_ind + STEP) % table.size();
		// where the previous is
		index = (index + STEP) % table.size();
	}

	// now the wanted element is a the bottom of the cluster
	// we can remove it
	table[index].key.clear(); // = "";
	table[index].data = -1;   // clear for more complex data
	--logic_fill;	
}

void lin_pr_hash_table::print() const {
#if DEBUG_HASH == 1	
	for (size_t i = 0; i < table.size(); i++) {
		std::cout << "hash = " << i << " :"
		          << "{ key: " << table[i].key << ", "
		          << " data: " << table[i].data << " }"
		          << std::endl;
	}
#endif // DEBUG_HASH
}
