/*
 * Some sorting algorithms, than use NO compare operations.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Authors : Ivan Filipov, Nikolay Babulkov	
 */

#include <queue> // std::queue
#include <array> // std::array
#include <algorithm> // std::swap(), 
#include "non_comparison_sorting.h"

// unsigned chars have values in [0 , 255]  
const size_t MAX_VAL = 256;
void counting_sort(std::vector<unsigned char>& arr) {

	//here we will count each number's frequency
	//int freq[MAX_VAL + 1] = { 0 , };
	std::array<unsigned char, MAX_VAL> freq;
	freq.fill(0);
	// counting step
	for (size_t i = 0; i < arr.size(); i++)
		freq[arr[i]]++;

	// pushing numbers back into the input array
	size_t j = 0;
	for (size_t i = 0; i < MAX_VAL; i++)
		while (freq[i]--)
			arr[j++] = i;
}



// English alphabet + '\0' 
int const ALPHA_COUNT = 27;
// building kind of radix tree...
// to sort the strings
// going from the most significant 'digit'/char in our case/ (MSD)
// because we have a lexicographic sort
// args : the vector of strings, 
// low - high cuts a slice in the vector, pos - current position in the strings 
void msd_strings_radix_sort(std::vector<std::string>& strings, int low, int high, int pos){

	if (high <= low)
		return;
	//a queue for each letter and '\0' symbol
	std::queue <std::string> buckets[ALPHA_COUNT];
	// placement index
	int bucket_ind;
	for (int j = low; j < high; ++j) {
		// index of the queue where we should add the current name
		bucket_ind = strings[j][pos] ? strings[j][pos] - 'a' + 1 : 0;
		buckets[bucket_ind].push(strings[j]);
	}
	// indexes of the sorted part
	int start_ind = low;
	int finish_ind = low;
	// for each bucket
	for (int j = 0; j < ALPHA_COUNT; ++j) {
		// put back all strings sorted by first letter
		while (!buckets[j].empty()) {

			strings[finish_ind++] = buckets[j].front();
			buckets[j].pop();
		}
		// sort all from current bucket
		// based on second letter
		if (finish_ind > low + 1)
			msd_strings_radix_sort(strings, start_ind, finish_ind, pos + 1);
		// for the next iteration	
		start_ind = finish_ind;
	}
}



// BASE of the numerical system, we use to split the numbers
// Example: BASE = 10: 15 = [1, 5]
// 			BASE = 2 : 10 = [1, 0, 1, 0]
// 			BASE = 8 : 85 = [1, 2, 5]
const int BASE = 10;

/// Counting sort with additional memory, a helper step for LSD radix
///-----------------------------------------------------------------
/// It sorts the array by the 'i'-th digit, when 10^i == mask
/// + good sides : O(n + k)
/// - bad sides  : O(n + k) additional memory
void lsd_counting_sort(const std::vector<int>& arr, std::vector<int>& output, int mask) {
	// initialize counting array with 
	std::array<unsigned char, BASE> count_arr;
	count_arr.fill(0);
	int size = arr.size();
	// store count of occurrences in count_arr[]
	for (int i = 0; i < size; i++)
		count_arr[(arr[i] / mask) % BASE]++;
	// change count_arr[i] so that count_arr[i] now contains actual
	// position of this digit in output[]
	for (int i = 1; i < BASE; i++)
		count_arr[i] += count_arr[i - 1];
	// build the output array, instead of writing on top of arr
	// it is needed because otherwise we will loose the initial values in arr
	for (int i = size - 1; i >= 0; i--) {
		// Uncomment for debugging purposes:
		// std::cout << "Element: " << arr[i] << " -> " << count_arr[ (arr[i]/mask)%BASE ] - 1  << " index" << std::endl;
		output[count_arr[(arr[i] / mask) % BASE] - 1] = arr[i];
		count_arr[(arr[i] / mask) % BASE]--;
	}
}

// LSD unsigned integer radix sort
void lsd_radix_sort(std::vector<int>& arr) {
	// find maximum
	int max_el = *std::max_element(arr.begin(), arr.end());
	int size = arr.size();
	// result array
	std::vector<int> output_arr;
	output_arr.resize(size);
	// Mask is BASE^i; i <- [0, ..., count of digits in max_el]
	// Loops until the mask has the same digit count as the max element
	for (int mask = 1; max_el / mask > 0; mask *= BASE) {
		// using the stable counting, we sort by each digit, preserving previous order
		lsd_counting_sort(arr, output_arr, mask);
		std::swap(output_arr, arr);
	}
}
