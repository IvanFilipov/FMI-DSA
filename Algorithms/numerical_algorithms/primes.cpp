//some general algorithms for prime number
#include<stdio.h>
#include<math.h>

int min(int a, int b) {
	
	return (a < b) ? a : b;
}

int max(int a, int b) {
	
	return (a > b) ? a : b;
}

//simple check if a number is a prime
bool is_prime(int n) {

	if (n < 2)
		return true;

	int sq = sqrt(n);

	for (int i = 2; i < sq; i++)
		if (n % i == 0)
			return false;

	return true;
}

//slower version ...
void primes_in_interval_slow(int a, int b) {

	for (int i = a; i < b; i++)
		if (is_prime(i))
			printf("%d ", i);

	putchar('\n');
}


//a bit smarter using some math...
//every single number can be presented as 30q + p , where p is in [0,29]
//30 = 2.3.5 , so potentially only 30q + 1; 30q + 7; 30q + 11; 30q + 13
								// 30q + 29 ; 30q + 23 ; 30q + 19; 30q + 17 
			                    //can be primes

const int INTERVAL_SIZE = 3000;
const int INTERVAL_STEP = 30;
const int N_STEPS = 8;
int steps[N_STEPS] = { 1, 7, 11, 13, 17, 19, 23, 29 };

void primes_in_interval_fast(int a_in, int b_in) {
	
	//if the parameters are passed in wrong order
	int a = min(a_in, b_in);
	int b = max(a_in, b_in);
	
	if (b - a < INTERVAL_SIZE) {
		primes_in_interval_slow(a, b);
		return;
	}

	//finding the first "30q" number
	int new_down;
	for (int i = a; i < a + INTERVAL_STEP; i++) {

		if (i % INTERVAL_STEP == 0) {
			new_down = i;
			break;
		}

		if(is_prime(i))
			printf("%d ", i);
	}
	
	int last_checked;
	for (int i = new_down; i < b - INTERVAL_STEP; i += INTERVAL_STEP)
		for (int j = 0; j < N_STEPS; j++)
			if(is_prime(i + steps[j])) {
				printf("%d ", i + steps[j]);
				last_checked = i + steps[j];
			}
	
	for (int i = last_checked + 1; i < b ; i++)
			if (is_prime(i))
				printf("%d ", i);

}


int main() {

	primes_in_interval_slow(50, 10000);

	printf("\n------------------------------------\n\n");

	primes_in_interval_fast(50, 10000);

	return 0;
}
