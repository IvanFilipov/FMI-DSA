#include<stdio.h>
#include<math.h>

bool isPrime(int n) {

	if (n < 2)
		return true;

	int sq = sqrt(n);

	for (int i = 2; i < sq; i++)
		if (n % i == 0)
			return false;

	return true;

}


//slower version ...
void PrimesInIntervalSlow(int a, int b) {

	for (int i = a; i < b; i++)
		if (isPrime(i))
			printf("%d ", i);

	printf("\n");

}


//a bit smarter using some math...
//every single number can be present as 30q + p , where p is in [0,29]
//30 = 2.3.5 , so potentially only 30q + 1; 30q + 7; 30q + 11; 30q + 13
								// 30q + 29 ; 30q + 23 ; 30q + 19; 30q + 17 
			//can be prime

const int intervalSize = 3000;
const int nSteps = 8;
int steps[nSteps] = { 1,7,11,13,17,19,23,29 };

void PrimesInInterval(int a, int b) {
	
	if ( b - a < intervalSize) {
		PrimesInIntervalSlow(a, b);
		return;
	}

	//finding the first "30q" number
	int newDown;
	for (int i = a; i < a + 30; i++) {

		if (i % 30 == 0) {
			newDown = i;
			break;
		}

		if(isPrime(i))
			printf("%d ", i);
	}

	for (int i = newDown; i < b - 30; i += 30)
		for (int j = 0; j < nSteps; j++)
			if(isPrime(i + steps[j]))
				printf("%d ", i + steps[j]);

	for (int i = b - 30; i < b ; i ++)
			if (isPrime(i))
				printf("%d ", i);

}


int main() {

	PrimesInIntervalSlow(50, 1000);

	printf("\n------------------------------------\n");

	PrimesInInterval(50, 10000);

	return 0;
}