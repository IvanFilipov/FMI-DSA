/*
 * An example for generating all possible ways of presenting a natural number as a sum of other natural numbers.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <cstdio>

using std::printf;

unsigned int const MAXN = 100;
int addends[MAXN];

void print_sum(unsigned int len) {


	for (unsigned int i = 1; i < len; i++)
		printf("%d + ", addends[i]);

	printf("%d\n", addends[len]);
}

void creat_next_sum(unsigned int n, int pos) {

	if (n == 0) {
		print_sum(pos - 1);
		return;
	}

	for (unsigned int k = n; k >= 1; k--){

		addends[pos] = k;

		if (addends[pos] <= addends[pos - 1])
			creat_next_sum(n - k, pos + 1);
	}
}


int main(){

	unsigned int n = 7;

	addends[0] = n + 1;

	creat_next_sum(n, 1);

	return 0;
}
