/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   search_algorithms.c
 * @author Ivan Filipov
 * @date   12.2019
 * @brief  Some searching algorithms implemented in plain C.
 *
 * @see https://en.wikipedia.org/wiki/Search_algorithm
 * @note Theory in searching_algorithms.h, implementation details in searching_algorithms.c 
 */
 
#include <math.h> // sqrt()

#include "search_algorithms.h"
 
int linear_search(int arr[], size_t size, int elem) {
	// simply traverse all elements 
	for (size_t i = 0; i < size; i++)
		if (arr[i] == elem)
			return i;
			
	return -1;
}

/**
 * @brief binary search recursive helper
 * @param[in] arr: array in which to search
 * @param[in] L: index of the left border
 * @param[in] R: index of the right border
 * @param[in] elem: element to be searched
 * @note in each call only [L; R] interval of the array is used.
 */
static int binary_search_rec(int arr[], int L, int R, int elem) {
	//there is no such element
	if (L > R)
		return -1;
	//
	// calculate the middle index
	// int med = (L + R) / 2; // <- a bug source, because L + R can easily overflow
	// solution is
	int med = L + (R - L) / 2;
	// or even better int med = L + (((unsigned int)R - (unsigned int)L) >> 1);
	//
	// is the search element on that index?
	if (arr[med] == elem)
		return med;
	//
	// grater than the middle element -> search in right
	if (arr[med] > elem)
		return binary_search_rec(arr, L, med - 1, elem);
	//
	// less than the middle element -> search in the left
	if (arr[med] < elem)
		return binary_search_rec(arr, med + 1, R, elem);
	//
	// won't reach here
	return -1;
}

int binary_search(int arr[], size_t size, int elem) {
	// binary search wrapper
	return binary_search_rec(arr, 0, size, elem);
}

/**
 * @brief jump search helper
 * @param[in] step: how many elements to "jump"
 * @see jump_search()
 */
static int jump_search_it(int arr[], int size, int step, int elem) {

	int ind = 0;
	// skip blocks with elements less than the searched
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

int jump_search(int arr[], size_t size, int elem) {
	// jump search wrapper
	return jump_search_it(arr, size, sqrt(size), elem);
}
