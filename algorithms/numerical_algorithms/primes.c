/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   primes.c
 * @author Ivan Filipov
 * @date   09.2018
 * @brief  Some general algorithms for prime numbers - 
 *         check if a number is a prime,
 *         find all primes in an interval [a, b].
 *
 * @see https://en.wikipedia.org/wiki/Prime_number
 */

#include <stdio.h>   // printf(), putchar()
#include <math.h>    // sqrt()
#include <stdbool.h> // boolean type

/// simple check if a number is a prime
bool is_prime(int n) {

	if (n < 2)
		return false;

	int sq = sqrt(n);

	for (int i = 2; i <= sq; i++)
		if (n % i == 0)
			return false;

	return true;
}

/// slower version for finding all prime number in
/// an interval [a, b]
void primes_in_interval_slow(int a, int b) {

	for (int i = a; i < b; i++)
		if (is_prime(i))
			printf("%d ", i);

	putchar('\n');
}

//@{
/// constants related with the faster algorithm
const int INTERVAL_SIZE = 3000; //!< below this value the difference between the faster and the slower algo is insignificant 
const int INTERVAL_STEP = 30;   //!< math's interval
#define N_STEPS 8               //!< number of prime multipliers
int steps[N_STEPS] = { 1, 7, 11, 13, 17, 19, 23, 29 }; //!< prime multipliers
//@}

/// a bit smarter version of the algorithm for finding all primes in the interval [a, b]
/// by using some math...
/// every single number can be presented as 30q + p , where p is in [0,29]
/// 30 = 2.3.5 , so potentially only 30q + 1; 30q + 7; 30q + 11; 30q + 13
///                                  30q + 29 ; 30q + 23 ; 30q + 19; 30q + 17 
/// can be primes
void primes_in_interval_fast(int a_in, int b_in) {
	
	// if the parameters are passed in wrong order
	int a = (a_in < b_in) ? a_in : b_in; // min
	int b = (a_in > b_in) ? a_in : b_in; // max
	
	if (b - a < INTERVAL_SIZE) {
		primes_in_interval_slow(a, b);
		return;
	}

	// finding the first "30q" number
	int new_down = a;
	for (int i = a; i < a + INTERVAL_STEP; i++) {
		if (i % INTERVAL_STEP == 0) {
			new_down = i;
			break;
		}
		
		if (is_prime(i)) printf("%d ", i);
	}
	//
	
	// filter all number 30 by 30
	int last_checked = 0;
	for (int i = new_down; i < b - INTERVAL_STEP; i += INTERVAL_STEP)
		for (int j = 0; j < N_STEPS; j++)
			if (is_prime(i + steps[j])) {
				printf("%d ", i + steps[j]);
				last_checked = i + steps[j];
			}
	//
	
	// filter the rest with the slower algorithm
	for (int i = last_checked + 1; i < b ; i++)
			if (is_prime(i))
				printf("%d ", i);
}


int main() {

	/* run the slower version of the algorithm */
	primes_in_interval_slow(50, 10000);

	printf("\n------------------------------------\n\n");
	
	/* run the faster version of the algorithm */
	primes_in_interval_fast(50, 10000);

	return 0;
}
