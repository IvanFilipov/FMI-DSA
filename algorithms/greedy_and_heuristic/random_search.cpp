/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   random_search.cpp
 * @author Ivan Filipov
 * @date   02.2019
 * @brief  Searching for an element in an array,
 *         with random probes,
 *         as an example of heuristic algorithm.
 */

#include <ctime>   // time()
#include <cstdlib> // rand(), srand()
#include <cstdio>  // printf()
#include <vector>  // vector


/**
 * @brief search for an element in an array,
 *        using random probes
 * @param[in] elem: the element to be searched 
 * @param[in] nums: the array to be tested
 * @retval    index of the element if found, -1 else
 * @note      O(n) best case time complexity, worst case complexity is unknown
 */

int random_search(int elem, const std::vector<int>& nums) {
	// used to end the algorithm if there is no such element
	std::vector<bool> tried(nums.size(), false);
	size_t tries = 0;
	size_t try_at;
	
	while (tries < nums.size()) {
		// get position
		try_at = rand() % nums.size();
		// if the searched element is on it
		if (nums[try_at] == elem)
			return try_at;
		// if we haven't tried this index
		if (!tried[try_at]) {
			// mark it as tried
			tried[try_at] = true;
			tries++;
		}
	}
	// not found
	return -1;
}

int main() {

	srand(time(NULL));
	
	std::vector<int> nums = { 1, 21, 11, 23, 105, -94, -28, 44 };
	int elem = 11;

	printf("searching for %d :\n", elem);

	int index = random_search(elem, nums);

	if (index == -1)
		printf("can't find such element\n");
	else
		printf("found at index %d\n", index);
									  

	return 0;
}
