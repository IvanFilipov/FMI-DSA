// EratostenAlgorithm : finds out the prime numberes below n 
//
#include<iostream>

#define PRIME false
#define COMPOSITE true

typedef unsigned long long ull_int;


const ull_int N = 20000;
bool sieve[N] = { PRIME , };

void PrintPrimes() {

	for (ull_int i = 2; i < N; i++)
		if (sieve[i] == PRIME)
			std::cout << i << " is a prime ! \n";



}


void eratosten(){

	for (ull_int i = 2; i <= N; i++)
		if (!sieve[i])
			for (ull_int j = i * i; j <= N; j += i)
				sieve[j] = COMPOSITE;

	PrintPrimes();

}





int main(){

	eratosten();

	return 0;
}
