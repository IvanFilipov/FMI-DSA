#include "tests.h"

//inserts NELEM elements into our tree
void init(BST& tree) {

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

void searchTest(const BST& tree) {


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

void removeTest(BST& tree) {

	key_type curkey;

	for (unsigned int i = 0; i < NTRY; ++i) {

		curkey = rand() % MAX_KEY;

		printf("\nremoving element with key %d :\n", curkey);

		try {
			tree.remove(curkey);

			printf("successfully removed ! \n");
		}
		catch (std::logic_error& e) {

			printf("error : %s\n", e.what());

		}

	}
}


void runBasicTests(BST& tree) {

	tree.insert(11, 1);
	tree.insert(9, 1);
	tree.insert(15, 1);
	tree.insert(12, 1);
	tree.insert(16, 1);
	tree.insert(10, 1);
	tree.insert(5, 1);
	tree.insert(3, 1);
	tree.insert(6, 1);
	tree.insert(13, 1);

	tree.printTree();

	printf("\n tree's height = %d \n", tree.getHeight());

	tree.printSortedKeys();

	printf("\nremoving element with key 9\n");

	tree.remove(9);

	tree.printTree();

	printf("\n tree's height = %d \n", tree.getHeight());

	tree.printSortedKeys();

}

void runAdvancedTests(BST& tree) {

	init(tree);

	tree.printTree();

	printf("\n tree's height = %d \n", tree.getHeight());

	tree.printSortedKeys();

	searchTest(tree);

	removeTest(tree);

	tree.printTree();

	printf("\n tree's height = %d \n", tree.getHeight());

	tree.printSortedKeys();

}