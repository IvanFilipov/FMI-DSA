/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   advanced_sorting.h
 * @author Ivan Filipov
 * @date   12.2019
 * @brief  The most basic sorting algorithms implemented in plain C.
 *
 * @see https://en.wikipedia.org/wiki/Sorting_algorithm
 * @note Theory in advanced_sorting.h, implementation details in advanced_sorting.c 
 */

#pragma once

#include <stddef.h> // size_t type definition

/**
 * @brief a simple swap function
 * @note in C there are no references, so using pointers
 * is the only approach
 */
void swap(int* f, int* s);

/**
 * @brief Sorts an array of numbers using Merge sort.
 * @param[in,out] arr: array to be sorted.
 * @param[in]     size: number of element in the array.
 * 
 * + good sides : STABLE , difficulty in best , worst and average case : ~ O(nlogn)
 *   does not require random access to data, therefore it is
 *   applicable to linked lists (only O(logn) additional memory for recursions)
 * - bad sides : requires additional memory ~ O(n), not adaptive ( when elements are nearly sorted,
 *   the difficulty is still O(nlogn) )
 * ! notice : an linear in-place merge exists, but it is both expensive and complex 
 */
void merge_sort(int arr[], size_t size);

/**
 * @brief Sorts an array of numbers using Quick sort.
 * @param[in,out] arr: array to be sorted.
 * @param[in]     size: number of element in the array.
 * 
 * + good sides : maybe the fastest one in average case : O(nlogn) 
 * - bad sides: worst case : O(n^2), NOT STABLE, 
 *   additional memory for recursion calls O(logn)
 *   pivot point choice could be critical to algorithm's performance
 * ! notice : an even faster algorithm based on the same logic exists : it is called
 *            "Three way quick sort"
 */
void quick_sort(int arr[], size_t size);

/**
 * @brief Sorts an array of numbers using Heap sort.
 * @param[in,out] arr: array to be sorted.
 * @param[in]     size: number of element in the array.
 * 
 * + good sides : O(nlogn) difficulty in every case,
 *   in-place (no additional memory needed) 
 * - bad sides : not stable, not really adaptive
 */
void heap_sort(int arr[], size_t size);
