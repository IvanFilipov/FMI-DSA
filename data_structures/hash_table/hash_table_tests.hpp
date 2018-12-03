/*
 * Some basic test written as template functions, so they can be ran with both our
 * linear probing hash table and separate chaining hash table implementations.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once

#include <array>   // std::array
#include <vector>  // std::vector
#include <iostream>// std::cout
#include <iomanip> // std::quoted(), may need C++14
#include <cstdlib> // std::srand(), std::rand()
#include <ctime>   // std::time()

// how many elements
const size_t N_ELEMS = 10;
// some typedefs for easier writing
using key_set  = std::array<std::string, N_ELEMS>;
using data_set = std::vector<data_type>;

template<typename HashTable>
void put_test(HashTable& table, const key_set& keys, const data_set& data) {

	for (size_t i = 0; i < N_ELEMS; i++) {
		std::cout << "putting element with key "
			      << std::quoted(keys[i]) 
			      << " and data "
			      << data[i] << " ... ";
		try {
			table.insert(keys[i], data[i]);
		} catch(const std::exception& e){
			std::cerr << "insert error : " << e.what();
		}
	}
	std::cout << "\ntrying to insert taken key:" << std::endl;
	try {
		table.insert(keys[0], data[0]);
	} catch(const std::exception& e){
		std::cerr << "insert error : " << e.what();
	}
	
	std::cout << std::endl
	          << "\nAfter the test the table looks like :"
	          << std::endl << std::endl;
	table.print();
}

template<typename HashTable>
void get_test(HashTable& table, const key_set& keys) {

	const size_t N_GETS = 3;

	size_t which;
	for (size_t i = 0; i < N_GETS; i++) {
		which = std::rand() % keys.size();

		std::cout << "getting element with key "
			      << std::quoted(keys[which])
			      << " ... ";
		try {
			std::cout << "data is " 
				      << table.get(keys[which]) 
				      << std::endl;
		} catch (std::exception& e) {
			std::cerr << "get error : " << e.what();
		}
	}

	std::string random_test = "Pleven";

	std::cout << "getting element with key "
		<< std::quoted(random_test)
		<< " ... ";

	try {
		std::cout << "data is " 
			      << table.get(random_test) 
				  << std::endl;
	} catch (std::exception& e) {
		std::cerr << "get error : " << e.what() << std::endl;
	}
}

template<typename HashTable>
void erase_test(HashTable& table, const key_set& keys) {

	const size_t N_DELETES = 3;

	size_t which;
	for (size_t i = 0; i < N_DELETES; i++) {
		which = std::rand() % keys.size();

		std::cout << "removing element with key "
			      << std::quoted(keys[which])
			      << " ... ";

		try {
			table.erase(keys[which]);
			std::cout << " removed !\n";
		} catch (std::exception& e) {
			std::cerr << "remove error : " << e.what();
		}
	}


	std::string random_test = "Pleven";

	std::cout << "erasing element with key "
			  << std::quoted(random_test)
		      << " ... ";
	try {
		table.erase(random_test);
		std::cout << " erased !\n";
	} catch (std::exception& e) {
		std::cerr << "remove error : " << e.what() << std::endl;
	}
	
	std::cout << std::endl
	          << "After the test the table looks like :"
	          << std::endl << std::endl;
	table.print();
}

template<typename HashTable>
void run_tests(HashTable& table) {
	
	std::srand(time(nullptr));
	// some keys
	key_set keys = {
		"Sofia",
		"Montana",
		"Stara Zagora",
		"Dobrich",
		"Sliven",
		"Haskovo",
		"Varna",
		"Burgas",
		"Veliko Turnovo",
		"Ruse"
	};
	// some data
	data_set data;
	data.reserve(N_ELEMS);
	for (size_t i = 0; i < N_ELEMS; i++)
		data.push_back(std::rand() % 100);
	
	table.print();
	
	std::cout << "\n\n>>>>>> PUT TESTS <<<<<<<\n\n";
	put_test(table, keys, data);

	std::cout << "\n\n>>>>>> DELETE TESTS <<<<<<<\n\n";
	erase_test(table, keys);

	std::cout << "\n\n>>>>>> GET TESTS <<<<<<<\n\n";
	get_test(table, keys);
}
