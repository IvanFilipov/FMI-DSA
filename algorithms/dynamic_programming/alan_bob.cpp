/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   alan_bob.cpp
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Solution to "alan & bob" problem,
 *         as an example of dynamic programming.
 *
 * @see README.md
 */

#include <cstdio> // std::printf()

/// count of all presents
const size_t NUM_PRE = 10;
/// maximum cost of a single present
const unsigned int MAXVAL = 200;
/// all presents values
const unsigned int values[NUM_PRE] = { 3, 2, 3, 2, 2, 
                                      77, 89, 23, 90, 11 };
/// maximum different presents sum,
/// if all presents have @p MAXVAL
const unsigned long int ALL_SUMS = NUM_PRE * MAXVAL;
/// markers for achievable sums, if sum "i" is possible, then
/// is_sum_possible[i] will be marked as true  
bool is_sum_possible[ALL_SUMS] = { false };

/// the solution to the task
void solve() {

	// the sum of all presents' values
	unsigned long long sum_total = 0;
	//sum all the values of the presents
	for (size_t i = 0; i < NUM_PRE; i++)
		sum_total += values[i];
	// sum 0 is always achievable
	is_sum_possible[0] = true; 
	// creating all the possible sums
	for (size_t i = 0; i < NUM_PRE; i++)
		for (size_t j = sum_total; j + 1 > 0; j--)
			if (is_sum_possible[j]) // if this sum is possible
				is_sum_possible[j + values[i]] = true; // the sum + current present is also possible

	// the closest sum to sum_total / 2 is the searched one
	for (size_t i = sum_total / 2; i + 1 > 0; i--)
		if (is_sum_possible[i]) {
			printf("sum for Alan %u, sum for Bob %llu", i, sum_total - i);
			printf("\n");
			return;
		}
}

int main() {

	solve();
	
	return 0;
}
