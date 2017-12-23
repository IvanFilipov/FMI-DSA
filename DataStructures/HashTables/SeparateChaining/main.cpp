#include "HashSeparateChaining.hpp"
#include "tests.h"


int main() {

	std::srand(time(nullptr));
	
	HashTable table;

	runTests(table);

	return 0;
}


