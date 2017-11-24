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

	printf("\nafter radix sorting : \n\n");
	for (auto it : vNames) {

		printf("%s\n", it.c_str());

	}


	return 0;
}