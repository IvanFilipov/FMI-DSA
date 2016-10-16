// EratostenAlgorithm : finds out the prime numberes below n 
//
#include<iostream>
using std::cout;

long long const N = 2000000;

void eratosten(bool *arr)
{
	unsigned long long i = 2;
	long long int sum = 0;

	while (i <= N)
	{
		if (arr[i] == 0)
		{
              
			sum += i;

			unsigned long long j = i * i;

			while (j <= N)
			{
				arr[j] = 1;
				j += i;
			}
			
		}

		i++;
	}

	std::cout << sum;
}

int main()
{
	bool *sieve = new bool[N];

	for (size_t i = 0; i < N; i++)
		sieve[i] = 0;

	eratosten(sieve);
     

	
	return 0;
}

