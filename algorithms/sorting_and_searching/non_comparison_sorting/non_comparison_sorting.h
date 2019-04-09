/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   non_comparison_sorting.h
 * @author Ivan Filipov
 * @author Nikolay Babulkov	
 * @date   12.2019
 * @brief  Some sorting algorithms, than use NO comparison operations.
 *
 * @see https://en.wikipedia.org/wiki/Sorting_algorithm#Non-comparison_sorts
 * @note Theory in non_comparison_sorting.h, implementation details in non_comparison_sorting.cpp 
 */

#pragma once

#include <string> // std::string
#include <vector> // std::vector

/**
 * @brief Sorts an array of positive numbers using Counting sort.
 * @param[in,out] arr: array to be sorted.
 * 
 * Counting sort : n is number of elements, k is range size ( k = max_elem - min_elem )
 * + good sides : O(n + k) time complexity, easy to implement 
 * - bad sides  : O(k) additional memory, the range should be small
 *
 * @note could be easily modified to sort natural numbers.
 */
void counting_sort(std::vector<unsigned char>& arr);

/**
 * @brief Recursively sorts an array of strings using MSD radix sort.
 * @param[in,out] strings: array of strings to be sorted.
 * @param[in]     low: left index cut into the array.
 * @param[in]     high: right index cut.
 * @param[in]     pos:  current letter in strings. 
 * 
 * MSD Radix sort (variant) : n is number of strings to be sorted
 *                            c is count of all symbols
 *                            k is the length of the longest word
 * MSD strings radix sort
 * + good sides : O(n.k) time complexity in the worst case, but average is much better ~O(n+k)
 * - bad sides  : using additional memory O(1), but not the be ignored
 * ! better than classical algorithms for strings, because, the compare operation is much expensive
 *   when comparing strings
 */
void msd_strings_radix_sort(std::vector<std::string>& strings, int low, int high, int pos);

/**
 * @brief Sorts an array of strings using LSD radix sort.
 * @param[in,out] arr: array to be sorted.
 * LSD Radix Sort (variant) : n is number of integers to sort,
 *                            w is number of bits per each integer
 * LSD unsigned integer radix sort
 * + good sides O(n.w) time complexity
 * - bad sides  O(n + w) space complexity
 */
void lsd_radix_sort(std::vector<int>& arr);
