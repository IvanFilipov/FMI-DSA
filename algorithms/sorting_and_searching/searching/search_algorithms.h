/*
 * Some searching algorithms implemented in plain C. Theory in searching_algorithms.h, implementation details in searching_algorithms.c 
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once

#include <stddef.h> // size_t

/// Linear search
/// - slow O(n)
/// + works always
// return elements index if found, -1 else
int linear_search(int* arr, size_t size, int elem);

/// Binary search
/// - the array must be sorted 
/// + O(logn) time complexity
int binary_search(int* arr, size_t size, int elem);

/// K - step search (Jump search)
/// - only for sorted array
/// + time complexity of Jump search is between Linear search and Binary search
/// ! best results when step = sqrt(size)
int jump_search(int* arr, size_t size, int elem);



