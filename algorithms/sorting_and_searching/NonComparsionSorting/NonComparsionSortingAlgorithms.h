#pragma once

#include<string> //std::string
#include<vector> //std::vector
#include<queue>
#include<algorithm>

/// Inplace counting sort 
/// good sides : O(n)
/// bad sides  : O((maxElem - minElem)) additional memory

//unsigned chars have values in [0 , 255]  
int const MAX_VAL = 255;
void countingSort(unsigned char* arr, int size) {

	//here we will count each number's frequency
	int freq[MAX_VAL + 1] = { 0 , };

	//counting step
	for (int i = 0; i < size; i++)
		freq[arr[i]]++;

	//pushing numbers back into the input array
	int j = 0;
	for (unsigned char i = 0; i < MAX_VAL; i++)
		while (freq[i]--)
			arr[j++] = i;


}

///
/// MSD Radix Sort
///

//alphabet + '\0' 
int const alphaCount = 27;

//building kind of radix tree...
//to sort the names

//going from the most significant 'digit'/char in our case/ (MSD)
//because we have a lexicographic sort
//args : the vector of names, low border, up border,current position in the strings 
void MSD_RadixSort(std::vector<std::string>& names, int low, int high, int pos){

	if (high <= low)
		return;

	//a queue for each letter and '\0' symbol
	std::queue <std::string> buckets[alphaCount];


	int bucketIndex;
	for (int j = low; j < high; ++j) {

		//index of the queue where we should add the current name
		bucketIndex = names[j][pos] ? names[j][pos] - 'a' + 1 : 0;
		buckets[bucketIndex].push(names[j]);
	}

	int start = low;
	int finish = low;

	for (int j = 0; j < alphaCount; ++j) {

		//making a new array of names from each queue
		while (!buckets[j].empty()) {

			names[finish++] = buckets[j].front();
			buckets[j].pop();
		}

		//sorting the new array
		if (finish > low + 1)
			MSD_RadixSort(names, start, finish, pos + 1);

		start = finish;
	}

}


typedef std::vector<int> vec;
void print_vec(const vec& arr)
{
	for (unsigned i = 0; i < arr.size(); ++i)
		printf("%d ", arr[i]);

}

///
/// LSD Radix Sort
///

const int BASE = 10;
// BASE of the numerical system, we use to split the numbers
// Example: BASE = 10: 15 = [1, 5]
// 			BASE = 2 : 10 = [1, 0, 1, 0]
// 			BASE = 8 : 85 = [1, 2, 5]



// Counting sort with additional memory
//-----------------------------------------------------------------
// It sorts the array by the 'i'-th digit, when 10^i == mask
// good sides : O(n + k)
// bad sides  : O(n + k) additional memory
void counting_sort(const vec& arr, vec& output, int mask)
{
	// Initialize counting array with 
	int count_arr[BASE] = { 0,};
	int size = arr.size();

	// Store count of occurrences in count_arr[]
	for (int i = 0; i < size; i++)
		count_arr[ (arr[i]/mask)%BASE ]++;

	// Change count_arr[i] so that count_arr[i] now contains actual
	// position of this digit in output[]
	for (int i = 1; i < BASE; i++)
		count_arr[i] += count_arr[i - 1];

	// Build the output array, instead of writing on top of arr
	// It is needed because otherwise we will loose the initial values in arr
	for (int i = size - 1; i >= 0; i--)
	{
		// Uncomment for debugging purposes:
		// std::cout << "Element: " << arr[i] << " -> " << count_arr[ (arr[i]/mask)%BASE ] - 1  << " index" << std::endl;
		output[ count_arr[ (arr[i]/mask)%BASE ] - 1 ] = arr[i];
		count_arr[ (arr[i]/mask)%BASE ]--;
	}
	//print_vec(output);
}

// LSD unsigned integer radix sort
void lsd_radix_sort(vec& arr)
{
	int max_el = *std::max_element(arr.begin(), arr.end());
	int size = arr.size();

	vec output_arr;
	output_arr.resize(size);

	// Mask is BASE^i; i <- [0, ..., count of digits in max_el]
	// Loops until the mask has the same digit count as the max element
	for (int mask = 1; max_el/mask > 0; mask *= BASE)
	{
		// Using the stable counting, we sort by each digit, preserving previous order
		counting_sort(arr, output_arr, mask);
		std::swap(output_arr, arr);
	}
}
