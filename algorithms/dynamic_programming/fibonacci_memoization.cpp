/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   fibonacci_memoization.cpp
 * @author Ivan Filipov
 * @date   02.2019
 * @brief  Finding Fibonacci N-th member,
 *		   using memoization
 *         as an example of dynamic programming.
 *
 * @see    http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/fibtable.html
 */

#include <iostream> // std::cout
#include <array>    // std::array

/// type for Fibonacci numbers 
typedef unsigned long long int fib_num;
/// maximum Fibonacci members that can be calculated
/// @note fib(50) = 12586269025, more values can be stored in
///       an unsigned long long int, but don't be too greedy.
const int MAX_N = 50;
/// cached (already calculated) Fibonacci members, 
/// value of 0 means still not calculated
std::array<fib_num, MAX_N> cached_members = { 0 };

/**
 *  @brief calculates N-th member of Fibonacci sequence, using
 *         cached values if possible, while calculating save all results for future use
 * @param[in] n: which member to be calculated
 * @retval the value of that member
 */
fib_num fib_memo(unsigned int n) {
	// get the cached value by reference, so writing to it will be possible
	fib_num& cached_val = cached_members[n];
	// first numbers are known constants
	if (n < 2)
		cached_val = n;
	else if (cached_val == 0) // not calculated
		cached_val = fib_memo(n - 1) + fib_memo(n -2); // calculate this value
	
	return cached_val;
}

int main() {
	
	/* run some tests */
	std::cout << fib_memo(20) << std::endl;
	
	std::cout << fib_memo(50) << std::endl;
	
	return 0;
}
