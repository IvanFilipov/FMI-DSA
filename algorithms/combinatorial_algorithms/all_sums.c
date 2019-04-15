/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   all_sums.c
 * @author Ivan Filipov
 * @date   10.2018
 * @brief  An example for generating all possible ways of
 *         presenting a natural number as a sum of other natural numbers.
 *
 * Example 4 =
 * = 3 + 1
 * = 2 + 2
 * = 2 + 1 + 1
 * = 1 + 1 + 1 + 1
 */

#include <stdio.h> // printf

/// maximum number of addends
#define MAXN 100

/// all addends -> addends[i] contains the "i" summand
int addends[MAXN];

/// simple result output
void print_sum(unsigned int len) {
	
	for (unsigned int i = 1; i < len; i++)
		printf("%d + ", addends[i]);

	printf("%d\n", addends[len]);
}

/**
 * @brief recursive algorithms for generating all sums
 * @param[in] n: the number to be broke up into summands
 * @param[in] pos: which is the current summand's position
 *
 * The idea is simple: just using that recursive definition -
 * sum(0) = {}
 * sum(n) = {k} + sum(n-k), k = n, n-1,..., 1.
 */
void creat_next_sum(unsigned int n, int pos) {
	
	if (n == 0) {
		// bottom case
		print_sum(pos - 1);
		return;
	}

	for (unsigned int k = n; k >= 1; k--) {
		// get a smaller number
		addends[pos] = k;
		// represent the smaller number as sum, too.
		if (addends[pos] <= addends[pos - 1])
			creat_next_sum(n - k, pos + 1);
	}
}

int main() {
	
	/* number to be split */
	unsigned int n = 4;
	
	/* initialize step */
	addends[0] = n + 1;
	
	/* run the algorithm */
	creat_next_sum(n, 1);

	return 0;
}
