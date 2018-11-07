/*
 * An example for Eratosthenes algorithm : finds out the prime numbers below N -> [2, N] 
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include<stdio.h>

#define PRIME false
#define COMPOSITE true

typedef unsigned long long ull_int;
const ull_int N = 20000;
//by default all other values will be 0 ( false <=> PRIME )
bool sieve[N] = { PRIME, };

//just outputs all prime numbers
void print_primes() {

	for (ull_int i = 2; i < N; i++)
		if (sieve[i] == PRIME)
			printf("%d is a prime!\n", i);
}
//the algorithm is simple, for each prime number,
//mark all numbers which have this number as a multiplier  
void eratosthenes_sieve() {

	for (ull_int i = 2; i <= N; i++)
		if (sieve[i] == PRIME)
			for (ull_int j = i * i; j <= N; j += i) //the start value and the step are important
				sieve[j] = COMPOSITE;

	print_primes();
}

int main() {

	eratosthenes_sieve();

	return 0;
}
