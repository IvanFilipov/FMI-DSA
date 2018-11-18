/*
 * Some advanced sorting algorithms implemented in plain C. Theory in advanced_sorting.h, implementation details in advanced_sorting.c 
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
#include <stdlib.h> // malloc(), free()
#include <string.h> // memcpy()
#include "advanced_sorting.h"

// min max functions
int max(int x, int y) { return (x > y) ? x : y; }
int min(int x, int y) { return (x < y) ? x : y; }

// a simple swap function,
// in C there are no references, so using pointers
// is the only approach
void swap(int* f, int* s) {
	int t = *f;
	*f = *s;
	*s = t;
}

// a "merge" step from the merge sort algorithm
static void merge(int* arr, size_t left, size_t right) {
	// additional memory for merging, notice that
	// only one allocation can be made for a faster running. See at 
	// https://github.com/semerdzhiev/sdp-samples/blob/master/Sorting/Sorting/Sorting.cpp 
	int* copy = malloc(sizeof(int) * (left + right));
	// indexes of the first half , second and copied
	int left_ind = 0, right_ind = left, copy_ind = 0;
	//iterating both left and right parts
	//in each step we
	//take the smaller element form each part
	//and copy it in 'copy' array
	//in order to have sorted sequence in the copy array at the end
	while (left_ind < left && right_ind < left + right)
		copy[copy_ind++] = (arr[left_ind] < arr[right_ind]) 
						    ? arr[left_ind++] 
						    : arr[right_ind++];

	// we have elements left in the first half
	// just copy them in the sorted array 'copy'
	while (left_ind < left)
		copy[copy_ind++] = arr[left_ind++];
	// elements left from the second part
	while (right_ind < left + right)
		copy[copy_ind++] = arr[right_ind++];
	//copy the memory back into the given array
	memcpy(arr, copy, sizeof(int) * (left + right));
	//release the memory used
	free(copy);
};

void merge_sort(int* arr, size_t size) {
	// bottom cases
	if (size <= 1 )
		return;

	if (size == 2) {
		if (arr[0] > arr[1]) {
			swap(&arr[0], &arr[1]);
		}
		return;
	}
	// determinate middle
	size_t mid = size / 2;
	// dividing in two parts
	// call the same algorithm in each part
	merge_sort(arr, mid);
	merge_sort(arr + mid, size - mid);
	// merging the two sorted parts into one array
	merge(arr, mid, size - mid);
}

void quick_sort(int* arr, size_t size) {
	// basic cases
	if (size <= 1)
		return;

	if (size == 2) {
		if (arr[0] > arr[1]) {
			swap(&arr[0], &arr[1]);
		}
		return;
	}
	// partition phase
	int left = 0, right = size - 1;
	// not the smartest way to choose the pivot element
	// but the easiest to implement and to debug with
	// int pivot = arr[size / 2];
	
	// better : median-of- three
	int pivot = max(min(arr[size / 2], arr[size - 1]),
					min(max(arr[size / 2], arr[size - 1]),
						arr[0]));
	while (left <= right) {
		// finding the first available 
		// element in the left half
		while (arr[left] < pivot)
			left++;
		// in the right half
		while (arr[right] > pivot)
			right--;
		//swap them
		if (left <= right) {
			swap(&arr[left], &arr[right]);
			left++;
			right--;
		}
	}
	// recursive calls
	// sorting left half
	if (left < size)
		quick_sort(arr + left, size - left);

	// sorting right half
	if (right > 0)
		quick_sort(arr, right + 1);
}

// sifts down an element on position 'pos' into 
// a valid heap (arr)
static void sift(int* arr, size_t pos, size_t size) {
	// which is the element we should sift
	int moved_elem = arr[pos];
	size_t moved_ind = pos;
	// where the first child is
	size_t child_ind = pos + pos;
	//going down the heap
	//until the moved element
	//finds its own position
	while (child_ind < size) {
		// which child is the bigger one
		if (child_ind < size - 1 && arr[child_ind] < arr[child_ind + 1])
			child_ind++;
		// we should stop sift the elem down, because it is on its position
		// both children are less than him
		if (moved_elem > arr[child_ind])
			break;
		//swapping the elem with it's greater child 
		arr[moved_ind] = arr[child_ind];
		// next step
		moved_ind = child_ind;
		child_ind *= 2;
	}
	//the elem have finally on it's position
	arr[moved_ind] = moved_elem;
}

void heap_sort(int* arr, size_t size) {
	// creating a dummy element, for easier implementation h -> h(2*i), h(2*i + 1) 
	--arr;  // go back one address, now it is dangerous to access arr[0], but we wouldn't 
	++size; // mark end
	// building the heap
	// notice that all elems after arr[size/2] are
	// actually leaves in the heap
	for (size_t i = size / 2 + 1; i > 1; i--)
		sift(arr, i - 1, size);
	// swapping the first elem with the last
	// then restore the heap
	for (size_t i = size - 1; i > 1; i--) {
		swap(&arr[1], &arr[i]);
		// restore heap phase
		sift(arr, 1, i);
	}
}


