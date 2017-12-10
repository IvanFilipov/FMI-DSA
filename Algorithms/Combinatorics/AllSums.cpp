//all possible ways of presenting a number as a sum of other positive numbers

#include<iostream>

int const MAXN = 100;

int addends[MAXN];

void print(unsigned int len){


	for (unsigned int i = 1; i < len; i++)
		std::cout << addends[i] << '+' ;

	std::cout << addends[len] << '\n';

}

void creatSum(unsigned int n, int pos){

	if (n == 0){
		print(pos - 1);
		return;
	}

	for (int k = n; k >= 1; k--){

		addends[pos] = k;

		if (addends[pos] <= addends[pos - 1])
			creatSum(n - k, pos + 1);
		
	}
}


int main(){

	unsigned int n = 7;

	addends[0] = n + 1;

	creatSum(n, 1);

	return 0;
}
