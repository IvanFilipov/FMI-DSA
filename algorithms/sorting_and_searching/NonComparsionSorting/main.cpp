#include<cstdio>

#include "NonComparsionSortingAlgorithms.h"

void printArr(unsigned char* arr, int size) {

	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);

	printf("\n\n");

}

const int Size = 12;

int main() {

	unsigned char arr[Size] = { 124 ,5 , 11, 2, 6, 7 , 42 , 13 , 88 , 21 ,9 , 8 };

	printf("given array : \n");
	printArr(arr, Size);

	printf("result of counting sort : \n");
	countingSort(arr, Size);
	printArr(arr, Size);


	std::vector<std::string> vNames;

	vNames.push_back("pesho");
	vNames.push_back("gosho");
	vNames.push_back("katrin");
	vNames.push_back("jean");
	vNames.push_back("claude");
	vNames.push_back("van");
	vNames.push_back("damme");


	printf("given names : \n\n");

	for (auto it : vNames) {

		printf("%s\n", it.c_str());

	}

	MSD_RadixSort(vNames, 0, vNames.size(), 0);

	printf("\nafter MSD radix sorting : \n\n");
	for (auto it : vNames) {

		printf("%s\n", it.c_str());

	}

	vec v { 22211, 555, 444, 1223, 1000, 322, 245, 231, 3, 23 };
	printf("\nUnordered input:\n");
	print_vec(v);
	lsd_radix_sort(v);
	printf("\n\nSorted output from MSD radix sorting: \n");
	print_vec(v);

	return 0;
}
