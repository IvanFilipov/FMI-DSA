/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   fast_power.c
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Fast power algorithm as 
 *         "Divide and conquer" example
 * @see https://en.wikipedia.org/wiki/Exponentiation_by_squaring
 */

#include <stdio.h>

/**
 * @brief calculates x ^ n, with fewer
 *        multiplications than the regular algorithm
 * @param[in] x: the base 
 * @param[in] n: the exponent
 */
double fast_pow(double x, unsigned int n) {
	
	printf("calculating %.5lf ^ %u...\n", x, n);
	
	if (n == 0)
		return 1;
	if (n == 1)
		return x;
	if (n & 1) // odd 
		return x * fast_pow(x, n - 1);
	else       // even
		return fast_pow(x * x, n / 2);
}

int main() {

	double base = 2.0;
	unsigned int power = 15;

	printf("power(%lf, %u) = %lf\n", base, power, fast_pow(base, power));

	return 0;
}
