#include<stdio.h>

double fastPow(double x, unsigned n) {

	if (n == 0)
		return 1;

	if (n & 1) //odd 
		return x * fastPow(x, n - 1);
	else       //even
		return fastPow(x * x, n / 2);

}


int main() {

	double base = 2.0;
	unsigned power = 11;

	printf("power(%lf, %u) = %lf\n",base, power, fastPow(base, power));


	return 0;
}