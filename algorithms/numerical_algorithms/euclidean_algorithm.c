/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   euclidean_algorithm.c
 * @author Ivan Filipov
 * @date   09.2018
 * @brief  Finding out the greatest common deviser
 *         of two natural numbers using Euclid's algorithm. 
 *
 * @see https://en.wikipedia.org/wiki/Euclidean_algorithm
 */

#include <stdio.h>

/// find GCD of two numbers recursively
/// just following the mathematical definition
int gcd_rec(int a, int b) {

	return (b == 0) ? a : gcd_rec(b, a % b);
}

/// an iterative version of the same algorithm 
int gcd_itr(int a, int b) {

	int temp;
	while (b != 0) {
		temp = a % b;
		a = b;
		b = temp;
	}

	return a;
}

int main() {
	
	int a = 272, b = 64;
	
	printf("using recursive approach : GCD(%d, %d) = %d\n", a, b, gcd_rec(a, b));
	printf("using iterative approach : GCD(%d, %d) = %d\n", a, b, gcd_itr(a, b));
	
	return 0;
}
