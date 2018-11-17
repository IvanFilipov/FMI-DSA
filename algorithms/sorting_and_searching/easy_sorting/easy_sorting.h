/*
 * The most basic sorting algorithms implemented in plain C. Theory in easy_sorting.h, implementation details in easy_sorting.c 
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
#pragma once
#include <stddef.h> // size_t type definition

void swap(int* f, int* s);

/*
  For each sorting algorithm the following factors are considered :
  - time complexity (how much time does the algorithm takes)
  - space complexity (how much additional memory is used)
  - # of swaps (how many elements are substituted)
  - # of comparisons (how many times < or > is used)
  - stability (maintaining the relative order between equal elements)
  - adaptability (is the algorithm faster when data is nearly (fully) sorted) 
  - known use cases
*/


/// Bubble sort 
/// + good sides : easy to implement , STABLE , adaptive (fast when data is nearly sorted ~ O(n)
/// + no additional memory is needed
/// - bad sides : difficulty ~ O(n^2) in worst and average case, too much compare and swap operations 
/// ! usage : only as academical example 

void bubble_sort(int arr[], size_t size);


/// Selection sort
/// + good sides : the easiest to implement, no additional memory is needed
/// + less swaps than bubble and insertion sorts
/// - bad sides : NOT STABLE ( in basic implementation on array )
/// - difficulty O(n^2) in best, worst and average case -> non-adaptive
/// ! usage : when in hurry, and the elements to be sorted are very few

void selection_sort(int arr[], size_t size);

/// InsertionSort
/// + good sides : easy to implement, STABLE, adaptive - fast when data is nearly sorted ~ O(n),
/// + no additional memory is needed, in average case less swaps then bubble, comparisons are fewer, except the worst case
/// - bad sides : difficulty ~ O(n^2) in worst ( data is sorted in the opposite way ), average case
/// ! usage : as a part of some "fast" sorting algorithms, applicable on linked list

void insertion_sort(int arr[], size_t size);
