/*
 * Solving "Queen's problem" as an example of backtracking algorithm.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <stdio.h> // printf(),putchar()
#include <time.h>  // time()

// some predefined constants
#define FIRST_COLUMN 0
#define FREE_CELL 0

#define BOARD_SIZE 8
#define QUEEN_VAL 9

#define QUEEN_SYM 'X'
#define FREE_CELL_SYM '0'

#define DELAY_SECONDS 1

#define REMOVE_HIT -1
#define ADD_HIT 1

// the whole chess board
// 0 the cell isn't hit by any queen
// 9 there is a queen on this cell
// 1 - 8 how many queens hit this cell
unsigned board[BOARD_SIZE][BOARD_SIZE];

// simple delay function in C - style
// used to set delay between printing each solution
void delay(unsigned secs) {

	time_t ret_time = time(0) + secs;   
	while (time(0) < ret_time)
		;               
}

void count_solutions() {
	// initializes only once
	static unsigned counter = 0; 
	// printing the incremented counter
	printf("\nsolution number : %d\n", ++counter);
}

void board_init() {

	for (unsigned i = 0; i < BOARD_SIZE; i++)
		for (unsigned j = 0; j < BOARD_SIZE; j++)
			board[i][j] = FREE_CELL;
}

void print_board() {

	count_solutions();

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

void mark_hits(short hitType, unsigned fromRow, unsigned fromCol) {

	// up and down
	for (unsigned rows = 0; rows < BOARD_SIZE; rows++)
		if(rows != fromRow)
			board[rows][fromCol] += hitType;

	// left and right
	for (unsigned cols = 0; cols < BOARD_SIZE; cols++)
		if (cols != fromCol)
			board[fromRow][cols] += hitType;

	// diagonals
	for (unsigned rows = 0; rows < BOARD_SIZE; rows++)
		for (unsigned cols = 0; cols < BOARD_SIZE; cols++)
			if ((fromRow - fromCol) == (rows - cols) ||
				(fromRow + fromCol) == (rows + cols))
				board[rows][cols] += hitType;

	// because while iterating the diagonal 
	// we are changing our queen's cell value
	// we should remove the hit.
	// the other approach is to add an additional
	// condition in our loop !((cols == fromCol) && (rows == fromRow))
	board[fromRow][fromCol] -= hitType;
}


//putting a Queen on a given column 
void place_queen(unsigned col) {
	
	// trying each row 
	for (int row = 0; row < BOARD_SIZE; row++) {
		// if we can place a queen there
		if (board[row][col] == FREE_CELL) {
			// placing the queen
			board[row][col] = QUEEN_VAL;
			// check if we have found a solution
			if (col == BOARD_SIZE - 1)
				print_board();
			else { // not the last queen
				// mark all cells that our queen hits
				mark_hits(ADD_HIT, row, col);
				// proceeding with the next queen 
				place_queen(col + 1);
				// remove the marks  
				mark_hits(REMOVE_HIT, row, col);
			}
			// remove the queen which we have placed
			board[row][col] = FREE_CELL;
		}
	}
}

void solve_queens_problem() {
	
	place_queen(FIRST_COLUMN);
}

int main() {
	
	board_init();
	solve_queens_problem();
    
	return 0;
}
