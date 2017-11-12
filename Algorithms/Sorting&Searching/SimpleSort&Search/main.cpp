#include<cstdio>

#include "./ConsoleApplication1\SimpleSortingAlgorithms.h"
#include "./ConsoleApplication1/SearchAlgorithms.h"

void PrintArr(int* arr, int size) {

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
	PrintArr(arr, Size);

	printf("result of Insertion sort : \n");
	InsertionSort(arr, Size);
	PrintArr(arr,Size);

	printf("result of Bubble sort : \n");
	BubbleSort(arr1, Size);
	PrintArr(arr1, Size);

	printf("result of Selection sort : \n");
	SelectionSort(arr2, Size);
	PrintArr(arr2, Size);


	int searchElem = 11;

	printf("result of LinearSearching for elem %d : %d \n",
		searchElem,LinearSearch(arr2, Size,searchElem));
	
	printf("result of BinarySearching for elem %d : %d \n",
		searchElem,BinarySearch(arr2,0, Size, searchElem));

	int step = 3;
	printf("result of JumpSearching for elem %d with step %d : %d \n",
		searchElem,step,JumpSearch(arr2, Size,step, searchElem));

	step = sqrt(Size);
	printf("result of JumpSearching for elem %d with step %d : %d \n",
		searchElem, step, JumpSearch(arr2, Size, step, searchElem));



	return 0;
}