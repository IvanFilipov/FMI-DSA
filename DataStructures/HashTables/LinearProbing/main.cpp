#include "tests.h"


int main() {

	std::cout << "######## LINEAR PROBING HASH TABLES #########";

	std::srand(time(nullptr));
	
	HashTable table(4);

	runTests(table);

	return 0;
}


