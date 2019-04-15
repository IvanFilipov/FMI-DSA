/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   newton_binomial.c
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  An example for calculating "n over k".
 *
 * @see    https://en.wikipedia.org/wiki/Binomial_coefficient
 *
 * If using the direct formula: N! / (K! *(N - K)!), the C/C++ types will overflow for a small N and K.
 * Calculates the binomial coefficient from Newton's binomial theorem:
 * ( n )
 * (   )  =  ?  
 * ( k ),
 * using Pascal's triangle.
 * @note the result is the k-th element of triangle's n-th line.
 * 
 */

#include <stdio.h> // printf()

/// the value of "N"
#define N 5
/// the value of "K"
#define K 2

/// an array to hold the last line from the triangle
int line[N + 1];

/**
 * @brief calculates @c N "over" @c K
 * @retval the result of the calculation
 */
int calc_n_over_k() {
	// first element of the line is  always 1 ... 
	line[0] = 1;
	// generate lines
	for (int i = 1; i <= N; i++) {
		// generate lines members
		line[i] = 1; //... last also

		for (int j = i - 1; j > 0; j--) {
			// every other element is a sum 
			// of the two numbers from the previous line 
			line[j] += line[j - 1]; 
		}
	}

	// the result is the k-th element in the n -th line 
	return line[K];
}

int main() {

	printf("( %d )\n", N);
	printf("(   ) = %d\n", calc_n_over_k());
	printf("( %d )\n", K);

	return 0;
}
