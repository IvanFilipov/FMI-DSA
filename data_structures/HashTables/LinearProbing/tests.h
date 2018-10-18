#pragma once

#include<array>
#include<iomanip> //std::quoted

#include "HashLinearProbing.hpp"

const size_t N_ELEMS = 10;

using keySet = std::array<std::string, N_ELEMS>;
using dataSet = std::vector<data_type>;

void putTest(HashTable& table,const keySet& keys,const dataSet& data) {

	for (size_t i = 0; i < N_ELEMS; i++) {

		std::cout << "putting element with key "
			<< std::quoted(keys[i]) << " and data "
			<< data[i] << " ... ";

		try {

			table.put(keys[i], data[i]);
		}
		catch(std::exception& e){

			std::cerr << "put error : " << e.what();
		}
	}


}

void getTest(HashTable& table, const keySet& keys) {

	const size_t N_GETS = 5;

	size_t which;
	for (size_t i = 0; i < N_GETS; i++) {

		which = std::rand() % keys.size();

		std::cout << "getting element with key "
			<< std::quoted(keys[which])
			<< " ... ";

		try {

			std::cout << "data is " <<
				table.get(keys[which]) << std::endl;
		}
		catch (std::exception& e) {

			std::cerr << "get error : " << e.what();
		}
	}


	std::string randomTest = "Pleven";

	std::cout << "getting element with key "
		<< std::quoted(randomTest)
		<< " ... ";

	try {

		std::cout << "data is " <<
			table.get(randomTest) << std::endl;
	}
	catch (std::exception& e) {

		std::cerr << "get error : " << e.what() << std::endl;
	}


}

void eraseTest(HashTable& table, const keySet& keys) {

	const size_t N_DELETES = 5;

	size_t which;
	for (size_t i = 0; i < N_DELETES; i++) {

		which = std::rand() % keys.size();

		std::cout << "removing element with key "
			<< std::quoted(keys[which])
			<< " ... ";

		try {

			table.erase(keys[which]);
			std::cout << " removed !\n";
		}
		catch (std::exception& e) {

			std::cerr << "remove error : " << e.what();
		}
	}


	std::string randomTest = "Pleven";

	std::cout << "erasing element with key "
		<< std::quoted(randomTest)
		<< " ... ";

	try {

		table.erase(randomTest);
		std::cout << " erased !\n";
	}
	catch (std::exception& e) {

		std::cerr << "remove error : " << e.what() << std::endl;
	}


}



void runTests(HashTable& table) {

	
	keySet keys = {

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

	 dataSet data;


	for (size_t i = 0; i < N_ELEMS; i++)
		data.push_back(std::rand() % 100);


	std::cout << "\n\n>>>>>> PUT TESTS <<<<<<<\n\n";

	putTest(table, keys, data);

	std::cout << "\n\n>>>>>> DELETE TESTS <<<<<<<\n\n";

	eraseTest(table, keys);

	std::cout << "\n\n>>>>>> GET TESTS <<<<<<<\n\n";

	getTest(table, keys);

}

