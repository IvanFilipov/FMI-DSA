/*
 * The most basic sorting algorithms implemented in plain C. Theory in easy_sorting.h, implementation details in easy_sorting.c 
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <stdbool.h> // C declaration of boolean type
#include "easy_sorting.h"
 
// a simple swap function,
// in C there are no references, so using pointers
// is the only approach
void swap(int* f, int* s) {
	int t = *f;
	*f = *s;
	*s = t;
}

void bubble_sort(int arr[], size_t size) {
    // an optimization to make the algorithm a bit faster and adaptive
	bool change_made = true;
	// iterating over the whole array, until there weren't any changes
	for (size_t i = 0; i < size - 1 && change_made; i++) {

		change_made = false; // flip the flag
		// iterating in the opposite direction, making the lightest element
		// "bubble" up to the top of sorted part
		for (size_t j = size - 1; j > i; j--) {
			// if two consecutive elements are in wrong order, then swap them
			if (arr[j - 1] > arr[j]) {
				swap(&arr[j - 1], &arr[j]); // the addresses are passed
				change_made = true; // raise the flag
			}
		}
	}
}

void selection_sort(int arr[], size_t size) {
	// the index of the current smallest element
	size_t index;
	// iterate through the whole array 
	for (size_t i = 0; i < size - 1; i++) {

		index = i; // thing the current element as smallest

		for (size_t j = i + 1; j < size; j++) // for the elements in the non-sorted part
			if (arr[index] > arr[j]) // check if a smaller element than the current smallest is present
				index = j; // update the smallest element index
		// on each step the smallest element "joins" the sorted part
		swap(&arr[i], &arr[index]);
	}
}

void insertion_sort(int arr[], size_t size) {
	// shortest sorting algorithm, beat those three lines ;)
	for (size_t i = 1; i < size; i++) // for each element after the first
		for (size_t j = i ; j > 0 && arr[j] < arr[j-1]; j--) // go back until elements in the sorted part are smaller then the current 
			swap(&arr[j], &arr[j-1]); // rotate the elements
}
