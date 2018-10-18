#include"LLRB.h"
#include"tests.h"

int main() {
	
	LLRB Tree;

	printf("running tests on a randomly generated\n"
		"left leaning red - black tree\n");

	srand(time(NULL));

	runTests(Tree);

	return 0;

}