/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   abstract_sorting.hpp
 * @author Ivan Filipov
 * @date   12.2019
 * @brief  An example with abstract implementation of some sorting algorithms.
 *
 * They depend only on iterators and comparators, no matter what the data structure below is.
 * 
 * @note The idea of this implementation is taken from @see https://en.cppreference.com
 */

#pragma once

#include <algorithm>  // std::swap(), std::rotate(), std::upper_bound()
                      // std::inplace_merge(), std::make_heap(), std::sort_heap()
 
namespace dsa {
/**
 * @brief STL like Insertion sort
 * @param[in] being: iterator to the beginning of the set
 * @param[in] iterator to the end of the set
 * @param[in] cmp: comparator to be used
 * @tparam Iterator: type of iterator - should provide random access 
 * @tparam Comparator: type of comparator
 *
 * for std::rotate @see https://en.cppreference.com/w/cpp/algorithm/rotate
 * for std::upper_bound @see https://en.cppreference.com/w/cpp/algorithm/upper_bound
 */
template <typename Iterator, typename Comparator>
void insertion_sort(Iterator begin, Iterator end, Comparator cmp) {
	
	for (Iterator i = begin; i != end; ++i) {
        std::rotate(std::upper_bound(begin, i, *i, cmp),
					i, i+1);
    }
}

/**
 * @brief STL like Merge sort
 * @param[in] being: iterator to the beginning of the set
 * @param[in] iterator to the end of the set
 * @param[in] cmp: comparator to be used
 * @tparam Iterator: type of iterator - should be at least bidirectional
 * @tparam Comparator: type of comparator
 *
 * for std::inplace_merge @see https://en.cppreference.com/w/cpp/algorithm/inplace_merge
 */
template <typename Iterator, typename Comparator>
void merge_sort(Iterator begin, Iterator end, Comparator cmp) {

    if (end - begin > 1) {
        Iterator middle = begin + (end - begin) / 2;
        merge_sort(begin, middle, cmp);
        merge_sort(middle, end, cmp);
        std::inplace_merge(begin, middle, end, cmp);
    }
}

/**
 * @brief STL like Heap sort
 * @param[in] being: iterator to the beginning of the set
 * @param[in] iterator to the end of the set
 * @param[in] cmp: comparator to be used
 * @tparam Iterator: type of iterator - should provide random access 
 * @tparam Comparator: type of comparator
 *
 * for std::make_heap @see https://en.cppreference.com/w/cpp/algorithm/make_heap
 * for std::sort_heap @see https://en.cppreference.com/w/cpp/algorithm/sort_heap
 */
template <typename Iterator, typename Comparator>
void heap_sort(Iterator begin, Iterator end, Comparator cmp) {

	std::make_heap(begin, end, cmp);
    std::sort_heap(begin, end, cmp);
}
} // namespace dsa
