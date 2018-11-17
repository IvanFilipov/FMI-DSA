/*
 * Finding out the greatest common deviser of two natural numbers using Euclid's algorithm. 
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <cstdio>

//following the recursive definition
int gcd_rec(int a, int b) {

	return (b == 0) ? a : gcd_rec(b, a % b);
}

//an iterative version of the same algorithm 
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
	
	std::printf("using recursive approach : GCD(%d, %d) = %d\n", a, b, gcd_rec(272, 64));
	std::printf("using iterative approach : GCD(%d, %d) = %d\n", a, b, gcd_itr(272, 64));
	
	return 0;
	return 0;
}
