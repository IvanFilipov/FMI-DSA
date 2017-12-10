#include <stdlib.h>
#include <stdio.h>

#define NON_VISITED 0

#define BOARD_MAX_SIZE  10

#define N_MOVERULES  8


unsigned int board[BOARD_MAX_SIZE][BOARD_MAX_SIZE];

//'HACKING' the lack of bool type in C
typedef enum {

	FALSE,
	TRUE
	

} BOOL;

// x + diffX[i] , y + diffY[i] defines the new position
int const diffX[N_MOVERULES] = { 1, 1, -1, -1, 2, -2, 2, -2 };
int const diffY[N_MOVERULES] = { 2, -2, 2, -2, 1, 1, -1, -1 };


void init(unsigned boardSize){

	for (unsigned i = 0; i < boardSize; ++i)
		for (unsigned j = 0; j < boardSize; ++j)
			board[i][j] = NON_VISITED;

}

void printBoard(unsigned boardSize){

	printf("\nthe knight movement looks like :\n");

	for (unsigned i = 0; i < boardSize; ++i) {
		for (unsigned j = 0; j < boardSize; ++j)
			printf("%3u", board[i][j]);

		putchar('\n');
	}

}


//currX , currY where the knight is
//i which step
BOOL nextMove(unsigned currX, unsigned currY, unsigned i, unsigned boardSize){

	//marking the current cell as visited
	board[currX][currY] = i;

	//we have found a solution
	if (i == boardSize * boardSize) {

		printBoard(boardSize);
		return TRUE;
		//exit(0); alternative approach is to make the function
		//void and just to exit the program when we find solution
	}

	unsigned newX,newY;

	//trying each direction
	for (unsigned k = 0; k < N_MOVERULES; ++k){

		newX = currX + diffX[k];
		newY = currY + diffY[k];

		//if we are inside the board and the cell is non-visited
		//then we are moving our knight into it
		if (newX >= 0 && newY >= 0 &&
			newX < boardSize && newY < boardSize &&
			board[newX][newY] == NON_VISITED) {

			if(nextMove(newX, newY, i + 1, boardSize))
                return TRUE;

		}
	}

	//marking the current cell as non-visited
	//when returning back from an unsuccessful
	//recursion call
	board[currX][currY] = NON_VISITED;
	return FALSE;

}



int main() {

	unsigned boardSize, startX, startY;

	printf("board size : ");
	scanf("%u", &boardSize);

	printf("\nknight X position : ");
	scanf("%u", &startX);

	printf("\nknight Y position : ");
	scanf("%u", &startY);

	if (boardSize > BOARD_MAX_SIZE ||
		startX >= boardSize ||
		startY >= boardSize) {

		printf("invalid input!\n");
		return -1;

	}

	init(boardSize);

	if(!nextMove(startX, startY, 1, boardSize))
         printf("solution not found!\n");

	return 0;
}

