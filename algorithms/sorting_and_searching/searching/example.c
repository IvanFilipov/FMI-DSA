/*
 * An example usage of our searching implementations. 
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
#include <stdio.h>  // printf()
#include <stdlib.h> // qsort()
#include <math.h>   // sqrt()
#include "search_algorithms.h"

#define ARR_SIZE 12

void print_arr(int* arr, size_t size) {

	for (size_t i = 0; i < size; i++)
		printf("%d ", arr[i]);

	printf("\n\n");
}
// ugly syntax function for qsort
int cmp(const void* x, const void* y) {
	
	return *(int*)x - *(int*)y;
}

int main() {

	int arr[ARR_SIZE] = { -124, 5, 11, 2, 6, 7, -42, 13, 88, 21, 9, 8 };

	printf("Starting array : \n");
	print_arr(arr, ARR_SIZE);

	printf("after sorting with qsort : \n");
	qsort(arr, ARR_SIZE, sizeof(int), cmp);
	print_arr(arr, ARR_SIZE);

	int searched_elem = 11;
	printf("result of Linear searching for elem %d : %d \n",
		searched_elem, linear_search(arr, ARR_SIZE, searched_elem));
	
	printf("result of Binary searching for elem %d : %d \n",
		searched_elem, binary_search(arr, ARR_SIZE, searched_elem));

	printf("result of Jump searching for elem %d with step %d : %d \n",
		searched_elem, (int)sqrt(ARR_SIZE), jump_search(arr, ARR_SIZE, searched_elem));
	
	searched_elem = -11;
	printf("result of Linear searching for elem %d : %d \n",
		searched_elem, linear_search(arr, ARR_SIZE, searched_elem));
	
	printf("result of Binary searching for elem %d : %d \n",
		searched_elem, binary_search(arr, ARR_SIZE, searched_elem));

	printf("result of Jump searching for elem %d with step %d : %d \n",
		searched_elem, (int)sqrt(ARR_SIZE), jump_search(arr, ARR_SIZE, searched_elem));

	return 0;
}
