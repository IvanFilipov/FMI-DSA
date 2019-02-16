/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   queens_problem.c
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Solution to "eight queens" problem,
 *         as an example of backtracking algorithm.
 *
 * @see    https://en.wikipedia.org/wiki/Eight_queens_puzzle
 */

#include <stdio.h> // printf(),putchar()
#include <time.h>  // time()

/* constants */
#define FIRST_COLUMN   0  //!< index of the first column
#define FREE_CELL      0  //!< marker for a cell with no queen and hit inside
#define BOARD_SIZE     8  //!< chess board's size
#define QUEEN_VAL      9  //!< marker for a cell taken by queen 
#define QUEEN_SYM     'X' //!< drawing symbol for queen 
#define FREE_CELL_SYM '0' //!< drawing symbol for cell without queen
#define DELAY_SECONDS  1  //!< delay between each solution's output

#define REMOVE_HIT -1 //!< value to be added when removing hits
#define ADD_HIT     1 //!< value to be added when adding hits

/* globals */
/// the whole chess board
/// value of board[i][j] means
/// 0: the cell isn't hit by any queen
/// 9: there is a queen on this cell
/// 1 to 8: how many queens hit this cell
unsigned board[BOARD_SIZE][BOARD_SIZE];

/* helper functions*/
/** @brief simple delay function in C - style
  *        used to set delay between printing each solution
  * @param[in] secs - how many seconds to delay
  */
void delay(unsigned secs) {

	time_t ret_time = time(0) + secs;   
	while (time(0) < ret_time)
		;               
}

/// simple helper function to count
/// solutions and output current one's number
void count_solutions() {
	// initializes only once
	static unsigned counter = 0; 
	// printing the incremented counter
	printf("\nsolution number : %d\n", ++counter);
}

/// initializes all cells of the board as FREE_CELL
void board_init() {

	for (unsigned i = 0; i < BOARD_SIZE; i++)
		for (unsigned j = 0; j < BOARD_SIZE; j++)
			board[i][j] = FREE_CELL;
}

/// outputs how the board looks like in
/// the current solution
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

/** 
  * @brief helper function for marking queen hits on the board
  * @param[in] hit_type: the value to be added to all cells (-1) for removing hit
  * @param[in] from_row: x position of the queen
  * @param[in] from_col: y position of the queen
  */
void mark_hits(short hit_type, unsigned from_row, unsigned from_col) {
	// up and down
	for (unsigned rows = 0; rows < BOARD_SIZE; rows++)
		if(rows != from_row)
			board[rows][from_col] += hit_type;
	// left and right
	for (unsigned cols = 0; cols < BOARD_SIZE; cols++)
		if (cols != from_col)
			board[from_row][cols] += hit_type;
	// diagonals
	for (unsigned rows = 0; rows < BOARD_SIZE; rows++)
		for (unsigned cols = 0; cols < BOARD_SIZE; cols++)
			if ((from_row - from_col) == (rows - cols) ||
				(from_row + from_col) == (rows + cols))
				board[rows][cols] += hit_type;
	// because while iterating the diagonal 
	// we are changing our queen's cell value
	// we should remove the hit.
	// the other approach is to add an additional
	// condition in our loop !((cols == from_col) && (rows == from_row))
	board[from_row][from_col] -= hit_type;
}


/**
  * @brief recursive function for placing a queen on the chess board
  * @param[in] col: on which column to try to place a queen
  * @note successful placement of queen on column BOARD_SIZE, means solution is found
  */
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

/// simple wrapper for solving the problem
void solve_queens_problem() {
	
	place_queen(FIRST_COLUMN);
}

int main() {
	
	/* initialize the board */
	board_init();
	
	/* run the algorithm */
	solve_queens_problem();
    
	return 0;
}
