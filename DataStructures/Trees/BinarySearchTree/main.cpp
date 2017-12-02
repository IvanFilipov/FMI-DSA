#include"BST.h"
#include"tests.h"


int main() {
	
	BST firstTree;

	printf("running basic tests on given binary search tree\n");

	runBasicTests(firstTree);

	printf("\n\nnow something unexpected ... \n");
	printf("completely random tree!\n\n");

	srand(time(NULL));
	
	BST secondTree;

	runAdvancedTests(secondTree);

	return 0;

}