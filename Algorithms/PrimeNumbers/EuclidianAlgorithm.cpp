#include<stdio.h>

int gcd_rec(int a, int b) {

	return (b == 0) ? a : gcd_rec(b, a % b);
}

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

	printf("%d\n", gcd_rec(272, 64));
	printf("%d\n", gcd_itr(272, 64));

	return 0;

}