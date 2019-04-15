
/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   example.c
 * @author Ivan Filipov
 * @date   12.2019
 * @brief  An example usage of our sorting implementations. 
 */
 
#include <stdio.h>  // printf()
#include <string.h> // memcpy()

#include "advanced_sorting.h"

/// a simple macro to get the # of elements in C array
#define sizeof_arr(arr) (size_t)(sizeof(arr) / sizeof(int))

/// simply output the array's contain
void print_arr(int arr[], size_t size) {

	for (size_t i = 0; i < size; i++)
		printf("%d ", arr[i]);
		
	printf("\n\n");
}

int main() {

	int arr[] = { 255, -124, 5, 11, 2, 6, 7 , -42, 13, 88, 21, 9, 8 };
	// copy arrays
	int arr_copy_f[sizeof_arr(arr)];
	int arr_copy_s[sizeof_arr(arr)]; 
	// actual copy the data
	memcpy(arr_copy_f, arr, sizeof(arr));
	memcpy(arr_copy_s, arr, sizeof(arr));

	printf("Starting array: \n");
	print_arr(arr, sizeof_arr(arr));

	printf("result of Merge sort: \n");
	merge_sort(arr, sizeof_arr(arr));
	print_arr(arr,  sizeof_arr(arr));

	printf("result of Quick sort: \n");
	quick_sort(arr_copy_f, sizeof_arr(arr_copy_f));
	print_arr(arr_copy_f,  sizeof_arr(arr_copy_f));

	printf("result of Heap sort: \n");
	heap_sort(arr_copy_s, sizeof_arr(arr_copy_s));
	print_arr(arr_copy_s, sizeof_arr(arr_copy_s));

	return 0;
}
