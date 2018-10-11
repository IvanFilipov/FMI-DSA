// calculates the binomial coefficient from Newton's binomial theorem 
// ( n )
// (   )  =  ?  
// ( k )
//using Pascal's triangle
//the result is the k-th element of triangle's n-th line 

#include<stdio.h>

const int N = 5;
const int K = 2;

//the last line form the triangle
int line[N + 1] ;

int calc_N_over_K() {
    
	//first element of the line is  always 1 ... 
	line[0] = 1;

	for (int i = 1; i <= N; i++) {
		
		line[i] = 1; //... last also

		for (int j = i - 1; j > 0; j--)
			line[j] += line[j - 1]; // every other element is a sum 
		                            // of the two numbers from the previous line 
	}

	//the result is the k-th element in the n -th line 
	return line[K];
}

int main() {

	printf("( %d )\n", N);
	printf("(   ) = %d\n", calc_N_over_K());
	printf("( %d )\n", K);

	return 0;
}
