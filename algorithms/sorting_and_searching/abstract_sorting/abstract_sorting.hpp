/*
 * An example with abstract implementation of some sorting algorithms.
 * They depend only on iterators and comparators, no matter what the data structure below is.
 * The idea of this implementation is taken from https://en.cppreference.com
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once

#include <algorithm>  // std::swap, std::rotate, std::upper_bound
                      // std::inplace_merge, std::make_heap, std::sort_heap
 
namespace dsa {
// abstract implementation of selection sort algorithm
// uses random access iterator
template <typename Iterator, typename Comparator>
void insertion_sort(Iterator begin, Iterator end, Comparator cmp) {
	
	// for std::rotate see : https://en.cppreference.com/w/cpp/algorithm/rotate
	// for std::upper_bound see : https://en.cppreference.com/w/cpp/algorithm/upper_bound
	
	for (Iterator i = begin; i != end; ++i) {
        std::rotate(std::upper_bound(begin, i, *i, cmp),
					i, i+1);
    }
}

// abstract implementation of merge sort algorithm
template <typename Iterator, typename Comparator>
void merge_sort(Iterator begin, Iterator end, Comparator cmp) {
	
	// for std::inplace_merge see : https://en.cppreference.com/w/cpp/algorithm/inplace_merge
    if (end - begin > 1) {
        Iterator middle = begin + (end - begin) / 2;
        merge_sort(begin, middle, cmp);
        merge_sort(middle, end, cmp);
        std::inplace_merge(begin, middle, end, cmp);
    }
}

template <typename Iterator, typename Comparator>
void heap_sort(Iterator begin, Iterator end, Comparator cmp) {
	// find those algorithms at  https://en.cppreference.com/w/cpp/algorithm
	std::make_heap(begin, end, cmp);
    std::sort_heap(begin, end, cmp);
}
} // namespace dsa
