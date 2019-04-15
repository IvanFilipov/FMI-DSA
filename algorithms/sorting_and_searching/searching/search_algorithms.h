/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   search_algorithms.h
 * @author Ivan Filipov
 * @date   12.2019
 * @brief  Some searching algorithms implemented in plain C.
 *
 * @see https://en.wikipedia.org/wiki/Search_algorithm
 * @note Theory in searching_algorithms.h, implementation details in searching_algorithms.c 
 */
 
#pragma once

#include <stddef.h> // size_t

/** 
 * @brief Linear searching for an element.
 * @param[in] arr: array of elements, in which to search
 * @param[in] size: size of the array
 * @param[in] elem: element to be searched for
 * @retval    >0 element's index if found
 * @retval    -1 if there is no such element
 *
 * Advantages/disadvantages:
 * - slow O(n)
 * + works always
 */
int linear_search(int arr[], size_t size, int elem);


/** 
 * @brief Searching for an element using binary search algorithm.
 * @param[in] arr: array of elements, in which to search, should be sorted
 * @param[in] size: size of the array
 * @param[in] elem: element to be searched for
 * @retval    >0 element's index if found
 * @retval    -1 if there is no such element
 *
 * Advantages/disadvantages:
 * - the array must be sorted 
 *  O(logn) time complexity
 */
int binary_search(int arr[], size_t size, int elem);


/** 
 * @brief Searching for an element using K - step search (Jump search).
 * @param[in] arr: array of elements, in which to search, should be sorted
 * @param[in] size: size of the array
 * @param[in] elem: element to be searched for
 * @retval    >0 element's index if found
 * @retval    -1 if there is no such element
 *
 * @see https://en.wikipedia.org/wiki/Jump_search
 * Advantages/disadvantages:
 * - only for sorted array
 * + time complexity of Jump search is between Linear search and Binary search
 * ! best results when step = sqrt(size)
 */
/// K - step search (Jump search)
/// - only for sorted array
/// + time complexity of Jump search is between Linear search and Binary search
/// best results when step = sqrt(size)
int jump_search(int* arr, size_t size, int elem);
