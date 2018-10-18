#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<vector>

size_t getRandom(size_t max) {

	return rand() % max;

}


std::vector<int> nums = { 1, 21, 11, 23, 105, -94, -28, 44 };

//returns index if found, -1 else
int randomSearch(int elem) {

	//used to end the algorithm if there is no such element
	bool tried[24] = { false };
	size_t tries = 0;

	size_t curIndex;


	while (tries < nums.size()) {

		curIndex = getRandom(nums.size());

		if (nums[curIndex] == elem)
			return curIndex;

		if (!tried[curIndex]) {

			tried[curIndex] = true;
			tries++;
		}

	}
	
	return -1;
}



int main() {

	srand(time(NULL));

	int elem = 11;

	printf("searching for %d :\n", elem);

	int index = randomSearch(elem);

	if (index == -1)
		printf("can't find such element\n");
	else
		printf("found at index %d", index);
									  

	return 0;
}
