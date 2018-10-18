#include<stdio.h> //printf, putchar

const int SIZE = 4;
const unsigned int MAX = 1000;

unsigned int matrix[SIZE][SIZE] = {

   //A  B  C  D 
	{0, 0, 6, 2}, //A
	{0, 0, 0, 0}, //B
	{0, 1, 0, 0}, //C
	{0, 0, 2, 0} //D

};


void floyd() {


	for (size_t i = 0; i < SIZE; i++)
		for (size_t j = 0; j < SIZE; j++)
			if (matrix[i][j] == 0)
				matrix[i][j] = MAX;

	for (size_t k = 0; k < SIZE; k++)
		for (size_t i = 0; i < SIZE; i++)
			for (size_t j = 0; j < SIZE; j++)
				if (matrix[i][j] > (matrix[i][k] + matrix[k][j]))
					matrix[i][j] = matrix[i][k] + matrix[k][j];

}

void printPaths() {

	for (size_t i = 0; i < SIZE; i++) {
		printf("from %c ", 'A' + i);

		for (size_t j = 0; j < SIZE; j++)
			if (matrix[i][j] != MAX)
				printf("[ to %c : %u ]", 'A' + j, matrix[i][j]);

		putchar('\n');
	}
}


int main() {

	floyd();

	printPaths();

	return 0;

}