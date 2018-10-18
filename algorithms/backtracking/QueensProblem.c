#include<stdio.h> //printf(),putchar()
#include <time.h> //time()

#define FIRST_COLUMN 0
#define FREE_CELL 0

#define BOARD_SIZE 8
#define QUEEN_VAL 9

#define QUEEN_SYM 'X'
#define FREE_CELL_SYM '0'

#define DELAY_SECONDS 1

#define REMOVE_HIT -1
#define ADD_HIT 1

//the chess chess board
//0 the cell isn't hit by any queen
//9 there is a queen on this cell
//1 - 8 how many queens hit this cell
unsigned board[BOARD_SIZE][BOARD_SIZE];


//simple delay function in C - style
//used to set delay between printing each solution
void delay(unsigned secs) {

	time_t retTime = time(0) + secs;   

	while (time(0) < retTime)
		;               
}

void countSolutions() {

	static unsigned counter = 0; //initializes only once

	// printing the incremented counter
	printf("\nsolution number : %d\n",++counter);
}


void boardInit() {

	for (unsigned i = 0; i < BOARD_SIZE; i++)
		for (unsigned j = 0; j < BOARD_SIZE; j++)
			board[i][j] = FREE_CELL;

}

void printBoard(){

	countSolutions();

	for (unsigned i = 0; i < BOARD_SIZE; i++) {
		for (unsigned j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == QUEEN_VAL)
				printf("%2c", QUEEN_SYM);
			else
				printf("%2c", FREE_CELL_SYM);

		putchar('\n');
	}

	delay(DELAY_SECONDS);
}

void markHits(short hitType,unsigned fromRow, unsigned fromCol) {

	//up and down
	for (unsigned rows = 0; rows < BOARD_SIZE; rows++)
		if(rows != fromRow)
			board[rows][fromCol] += hitType;

	//left and right
	for (unsigned cols = 0; cols < BOARD_SIZE; cols++)
		if (cols != fromCol)
			board[fromRow][cols] += hitType;

	//diagonals
	for (unsigned rows = 0; rows < BOARD_SIZE; rows++)
		for (unsigned cols = 0; cols < BOARD_SIZE; cols++)
			if ((fromRow - fromCol) == (rows - cols) ||
				(fromRow + fromCol) == (rows + cols))
				board[rows][cols] += hitType;

	//because while iterating the diagonal 
	//we are changing our queen's cell value

	//the other approach is to add an additional
	//condition in our loop !((cols == fromCol) && (rows == fromRow))
	board[fromRow][fromCol] -= hitType;

}


//putting a Queen on a given column 
void placeQueen(unsigned col){
	
	//trying each row 
	for (int row = 0; row < BOARD_SIZE; row++) {

		if (board[row][col] == FREE_CELL) {

			//placing the queen
			board[row][col] = QUEEN_VAL;

			//we have found a solution
			if (col == BOARD_SIZE - 1)
				printBoard();

			else{

				//mark all cells that our queen hits
				markHits(ADD_HIT, row, col);

				//proceeding with the next queen 
				placeQueen(col + 1);
				
				//remove the marks  
				markHits(REMOVE_HIT, row, col);
			}

			//remove the queen which we have placed
			board[row][col] = FREE_CELL;
		}
	}
}

int main()
{
    
	boardInit();

    placeQueen(FIRST_COLUMN);

	return 0;
}
