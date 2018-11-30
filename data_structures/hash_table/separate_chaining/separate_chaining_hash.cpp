/*
 * Basic implementation of hash table, using opened hashing strategy -
 * separate chaining. Depends only on our custom dynamic array and custom doubly linked list.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include "separate_chaining_hash.h"
// include only if debugging is ON
#if DEBUG_HASH == 1
#include <iostream> //std::cin, std::cout
#endif // DEBUG_HASH

// the hash function, it is the most critical zone,
// the implementation below is pretty simple, consider
// using better hash functions in your applications
size_t sp_ch_hash_table::hash_func(const key_type& key, const size_t size) {
	// get the size of the string
	size_t result = key.size();
	// add the ASCII code for each character
	for (unsigned char c : key)
		result += c;

	// return result % size;
	
	// but better in case the SIZE is a power of 2
	return result & (size - 1);
}

void sp_ch_hash_table::rehash() {
// debug print
#if DEBUG_HASH == 1
	std::cout << "\n...rehashing ...\n";
#endif // DEBUG_HASH
	// create new table
	sp_ch_hash_table new_table(table.size() * 2);
	
	// for each chain ...
	for (dsa::dlinked_list<table_elem>& list : table)
		if (!list.empty())
			for(table_elem& el : list) // for each of its elements
				new_table.insert(el.key, el.data); // put it in the new table
	// which will lead to re-calculating the hash values
	
	new_table.table.swap_with(table);
#if DEBUG_HASH == 1
	std::cout << ".............\n";
#endif // DEBUG_HASH
}

sp_ch_hash_table::chain_iter sp_ch_hash_table::find(size_t index, const key_type& key) {
	
	chain_iter it = table[index].begin();
	while (it != table[index].end() && it->key != key)
		++it;
	return it;
}

void sp_ch_hash_table::insert(const key_type& key, const data_type& data) {
	// calculate where to add the new element using the hash function
	size_t index = hash_func(key, table.size());
	// check if resizing is needed
	if (table[index].size() >= MAX_CHAIN_SIZE) {
		rehash();
		// calculate the hash again, because the table now have different size
		index = hash_func(key, table.size());
	}
	// add the new elem as a first in the list for O(1)
	table[index].push_front({ key, data });
#if DEBUG_HASH == 1
	std::cout << "stored at hash " << index << std::endl;
#endif
}

data_type sp_ch_hash_table::get(const key_type& key) {
	// calculate where to add the new element using the hash function
	size_t index = hash_func(key, table.size());
	// iterate through the elements of the list
	// searching for exactly the same key
	chain_iter it = find(index, key);
	// there is not such element
	if (it == table[index].end())
		throw std::logic_error("there isn't element with such key\n");
		
	return it->data;
}

void sp_ch_hash_table::erase(const key_type& key) {
	// calculate where to add the new element using the hash function
	size_t index = hash_func(key, table.size());
	// find it and get a iterator to it
	chain_iter it = find(index, key);
	// can't find it
	if (it == table[index].end())
		throw std::logic_error("there isn't element with such key\n");
	// remove it for O(1)
	table[index].remove(it);
}

void sp_ch_hash_table::print() {
#if DEBUG_HASH == 1	
	for (size_t i = 0; i < table.size(); i++) {
		std::cout << "hash = " << i << " :";
		if (table[i].empty()) {
			std::cout << "{}" << std::endl;
			continue;
		}
		std::cout << "{ ";
		size_t j = 0;
		for (chain_iter it = table[i].begin(); it != table[i].end(); ++it) {
		    std::cout << "{ key: " << it->key << ", "
		              << " data: " << it->data << " }";
			if (j != table[i].size() -1) std::cout << ", ";
			j++;
		}
		std::cout << " }" << std::endl;
		
	}
#endif // DEBUG_HASH
}

