#include<stdio.h>
#include<string.h>

const size_t NUM_PRE = 10;
const unsigned int MAXVAL = 200;

const unsigned int values[NUM_PRE] = { 3, 2, 3, 2, 2, 77,
										  89, 23, 90, 11 };

const unsigned long int ALL_SUMS = NUM_PRE * MAXVAL;

bool possibleSum[ALL_SUMS]; // can we have such a sum

void solve() {

	//the sum of all presents' values
	unsigned long long sumPre = 0;

	//sum all the values of the presents
	for (size_t i = 0; i < NUM_PRE; i++)
		sumPre += values[i];

	//mark all as unreachable
	memset(possibleSum, false, ALL_SUMS * sizeof(bool));

	possibleSum[0] = true; //sum 0 is always achievable

	//creating all the possible sums
	for (size_t i = 0; i < NUM_PRE; i++)
		for (size_t j = sumPre; j + 1 > 0; j--)
			if (possibleSum[j]) //if this sum is possible
				possibleSum[j + values[i]] = true; //this sum also

	//the closest sum to sumPre / 2 is the searched one
	for (size_t i = sumPre / 2; i + 1 > 0; i--)
		if (possibleSum[i]) {

			printf("sum for Alan %ld, sum for Bob %ld", i, sumPre - i);
			return;
		}

}


int main() {

	solve();

	return 0;
}