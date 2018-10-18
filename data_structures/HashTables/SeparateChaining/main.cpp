#include "HashSeparateChaining.hpp"
#include "tests.h"


int main() {

	
	std::cout << "######## SEPARATE CHAINING HASH TABLES #########";

	std::srand(time(nullptr));
	
	HashTable table;

	runTests(table);

	return 0;
}


