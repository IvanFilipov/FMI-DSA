#include<cstdio>

#include "AdvancedSortingAlgorithms.h"

void printArr(int* arr, int size) {

	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);

	printf("\n\n");

}

const int Size = 12;

int main() {

	int arr[Size] = { -124,5, 11, 2, 6, 7 , -42 , 13 , 88 , 21 ,9 , 8 };
	int arr1[Size]{ -124,5, 11, 2, 6, 7 , -42 , 13 , 88 , 21 ,9 , 8 };
	int arr2[Size]{ -124,5, 11, 2, 6, 7 , -42 , 13 , 88 , 21 ,9 , 8 };

	printf("Starting array : \n");
	printArr(arr, Size);

	printf("result of merge sort : \n");
	mergeSort(arr, Size);
	printArr(arr, Size);

	printf("result of quick sort : \n");
	quickSort(arr1, Size);
	printArr(arr1, Size);

	printf("result of heap sort : \n");
	heapSort(arr2, Size);
	printArr(arr2, Size);

	return 0;
}