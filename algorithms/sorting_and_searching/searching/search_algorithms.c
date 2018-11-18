/*
 * Some searching algorithms implemented in plain C. Theory in searching_algorithms.h, implementation details in searching_algorithms.c 
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
#include <math.h> // sqrt()
#include "search_algorithms.h"
 
int linear_search(int* arr, size_t size, int elem) {

	for (size_t i = 0; i < size; i++)
		if (arr[i] == elem)
			return i;
			
	return -1;
}

// binary search helper
// array - left bound - right bound - searched element
static int binary_search_rec(int *arr, int L, int R, int elem) {

	//there is no such element
	if (L > R)
		return -1;
	// a bug source, because L + R can easily overflow
	// int med = (L + R) / 2;
	// solution is
	int med = L + (R - L) / 2;
	// or even better int med = ((unsigned int)R - (unsigned int)L) >> 1;

	if (arr[med] == elem)
		return med;

	if (arr[med] > elem)
		return binary_search_rec(arr, L, med - 1, elem);

	if (arr[med] < elem)
		return binary_search_rec(arr, med + 1, R, elem);
	
	return -1;
}
// binary search wrapper
int binary_search(int* arr, size_t size, int elem) {
	
	return binary_search_rec(arr, 0, size, elem);
}

// jump search helper
static int jump_search_it(int* arr, int size, int step, int elem) {

	int ind = 0;
	// skip blocks with elements less the searched
	for (;ind < size && arr[ind] < elem; ind += step)
		;
	if (arr[ind] == elem) return ind; // are we on this element? 
	// size of this block
	int blk_size  = (ind + step > size) ? size - ind : step;
	// search from the beginning of the block, for block size elements
	int res_ind = linear_search(arr + ind - step, blk_size, elem);
	if (res_ind != -1) res_ind += (ind - step);
	return res_ind;
}

// binary search wrapper
int jump_search(int* arr, size_t size, int elem) {
	
	return jump_search_it(arr, size, sqrt(size), elem);
}
