#include "tests.h"

//inserts NELEM elements into our tree
void init(LLRB& tree) {

	data_type curData;
	key_type curkey;

	for (unsigned int i = 0; i < NELEM; ++i) {

		curkey = rand() % MAX_KEY;
		curData = rand() % MAX_DATA;

		//positive or negative
		curData = ((rand() % 2) ? curData : -curData);

		printf("\ninserting element with key %d :\n", curkey);

		try {

			tree.insert(curkey, curData);
			printf("successfully inserted\n");
		}
		catch (std::logic_error& e) {

			printf("error : %s\n", e.what());

		}
	}
}

void searchTest(const LLRB& tree) {


	key_type curkey;
	data_type value;

	for (unsigned int i = 0; i < NTRY; ++i) {

		curkey = rand() % MAX_KEY;

		printf("\nsearching for element with key %d :\n", curkey);

		try {
			value = tree.search(curkey);

			printf("element found! it's value is : %d\n", value);
		}
		catch (std::logic_error& e) {

			printf("error : %s\n", e.what());

		}

	}
}

void removeTest(LLRB& tree) {

	key_type curkey;

	for (unsigned int i = 0; i < NTRY; ++i) {

		curkey = rand() % MAX_KEY;

		printf("\nremoving element with key %d :\n", curkey);

		try {
			tree.remove(curkey);

			printf("successfully removed ! \n");
			//tree.printTree();
		}
		catch (std::logic_error& e) {

			printf("error : remove failed : %s\n", e.what());

		}

	}
}

void runTests(LLRB& tree) {

	printf("\n\n---------=insertion phase=---------\n\n");

	init(tree);

	tree.printTree();

	printf("\n tree's height = %d \n", tree.getHeight());

	tree.printSortedKeys();

	printf("\n\n---------=search phase=---------\n\n");

	searchTest(tree);

	printf("\n\n---------=remove phase=---------\n\n");

	removeTest(tree);

	tree.printTree();

	printf("\n tree's height = %d \n", tree.getHeight());

	tree.printSortedKeys();

}