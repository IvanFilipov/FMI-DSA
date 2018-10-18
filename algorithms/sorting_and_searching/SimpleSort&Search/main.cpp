#include<cstdio>

#include "SimpleSortingAlgorithms.h"
#include "SearchAlgorithms.h"

void printArr(int* arr, int size) {

	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);

	printf("\n\n");

}

const int Size = 12;

int main() {

	int arr[Size] = { -124,5, 11, 2, 6, 7 , -42 , 13 , 88 , 21 ,9 , 8 };
	int arr1[Size]{ -124,5, 11, 2, 6, 7 , -42 , 13 , 88 , 21 ,9 , 8 };
	int arr2[Size] = { -124,5, 11, 2, 6, 7 , -42 , 13 , 88 , 21 ,9 , 8 };

	printf("Starting array : \n");
	printArr(arr, Size);

	printf("result of Insertion sort : \n");
	insertionSort(arr, Size);
	printArr(arr,Size);

	printf("result of Bubble sort : \n");
	bubbleSort(arr1, Size);
	printArr(arr1, Size);

	printf("result of Selection sort : \n");
	selectionSort(arr2, Size);
	printArr(arr2, Size);


	int searchElem = 11;

	printf("result of LinearSearching for elem %d : %d \n",
		searchElem,linearSearch(arr2, Size,searchElem));
	
	printf("result of BinarySearching for elem %d : %d \n",
		searchElem,binarySearch(arr2,0, Size, searchElem));

	int step = 3;
	printf("result of JumpSearching for elem %d with step %d : %d \n",
		searchElem,step,jumpSearch(arr2, Size,step, searchElem));

	step = sqrt(Size);
	printf("result of JumpSearching for elem %d with step %d : %d \n",
		searchElem, step, jumpSearch(arr2, Size, step, searchElem));



	return 0;
}
