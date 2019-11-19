
/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   eratosthenes_sieve.c
 * @author Ivan Filipov
 * @date   09.2018
 * @brief  Example implementation of Eratosthenes algorithm
 *         for finding out prime numbers below N.
 *
 * @see https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 */

#include <stdio.h>    // printf()
#include <stdbool.h> // boolean type

/// marker for prime number
#define PRIME false
/// marker for composite number
#define COMPOSITE true
/// shorter name for "unsigned long long"
typedef unsigned long long ull_int;
/// up to which number to find primes
#define N 20000
/// sieve[i] = PRIME <=> i is a prime number,
/// otherwise sieve[i] = COMPOSITE
bool sieve[N] = { PRIME, };

/// just outputs all prime numbers
void print_primes() {

	for (ull_int i = 2; i < N; i++)
		if (sieve[i] == PRIME)
			printf("%llu is a prime!\n", i);
}

/// the algorithm is simple, for each prime number,
/// mark with COMPOSITE all numbers which have this number as a multiplier  
void eratosthenes_sieve() {

	for (ull_int i = 2; i < N; i++)
		if (sieve[i] == PRIME)
			for (ull_int j = i * i; j < N; j += i) // the start value and the step are important
				sieve[j] = COMPOSITE;

	print_primes();
}

int main() {

    /* run the algorithm and output all primes */
	eratosthenes_sieve();

	return 0;
}
