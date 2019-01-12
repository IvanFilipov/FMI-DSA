/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   knight_tour.c
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Solution to "knight's tour" problem,
 *         as an example of backtracking algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Knight%27s_tour
 */

#include <stdio.h>   // printf(), scanf(), putchar()
#include <stdbool.h> // bool type

/* constants */
#define NON_VISITED 0     //!< a marker for unvisited cell
#define BOARD_MAX_SIZE 10 //!< maximum board size
#define N_MOVERULES 8     //!< count of movement rules

/* globals */
/// the chess board represented as matrix
unsigned int board[BOARD_MAX_SIZE][BOARD_MAX_SIZE];

/// x + diff_x[i], y + diff_y[i] defines the all reachable positions from x, y
int const diff_x[N_MOVERULES] = { 1, 1, -1, -1, 2, -2, 2, -2 };
int const diff_y[N_MOVERULES] = { 2, -2, 2, -2, 1, 1, -1, -1 };

/* function definitions */
/**
 * @brief initializes all cells from the chess
 *        board as non-visited.
 * @param[in] board_size: size of board to be initialized, should be < BOARD_MAX_SIZE
 */
void init(unsigned board_size) {

	for (unsigned i = 0; i < board_size; ++i)
		for (unsigned j = 0; j < board_size; ++j)
			board[i][j] = NON_VISITED;
}

/**
 * @brief simply output chess board's contain,
 *        which describes the knight's tour.
 * @param[in] board_size: size of board to be printed, should be < BOARD_MAX_SIZE
 */
void print_board(unsigned board_size) {

	printf("\nthe knight's tour looks like :\n");

	for (unsigned i = 0; i < board_size; ++i) {
		for (unsigned j = 0; j < board_size; ++j)
			printf("%3u", board[i][j]);

		putchar('\n');
	}
}

/**
 * @brief recursive function that describes
 *        each step of the backtracking algorithm
 * @param[in] x: current x coordinate of the knight
 * @param[in] y: current y coordinate of the knight
 * @param[in] step: who many steps up to here
 * @param[in] board_size: size of the board
 * @retval    true, when solution is found, false else
 * @note when @p step == @p board_size ^ 2, a solution is found
 */
bool knight_next_move(unsigned x, unsigned y, unsigned step, unsigned board_size) {

	// marking the current cell as visited
	board[x][y] = step;

	// we have found a solution
	if (step == board_size * board_size) {
		print_board(board_size);
		return true;
		// exit(0); alternative approach is to make the function
		// void and just to exit the program when we find solution
	}

	int new_x, new_y;
	// trying each direction
	for (unsigned k = 0; k < N_MOVERULES; ++k){
		// calculate new cell
		new_x = x + diff_x[k];
		new_y = y + diff_y[k];
		// if we are inside the board and the cell is non-visited
		// then we are moving our knight into it
		if (new_x >= 0 && new_y >= 0 &&
			new_x < (int)board_size && new_y < (int)board_size &&
			board[new_x][new_y] == NON_VISITED) {
            // go into that cell
			if (knight_next_move(new_x, new_y, step + 1, board_size))
                return true;
		}
	}

	// marking the current cell as non-visited
	// when returning back from an unsuccessful
	// recursion call
	board[x][y] = NON_VISITED;
	return false;
}

int main() {
	
	// valid solution from size = 6, x = 0, y = 5
	// size = 6, x = 1, y = 5
	/* read inputs */
	unsigned board_size, start_x, start_y;
	
	printf("board size : ");
	scanf("%u", &board_size);

	printf("\nknight X position : ");
	scanf("%u", &start_x);

	printf("\nknight Y position : ");
	scanf("%u", &start_y);
	
	/* validate the input */
	if (board_size > BOARD_MAX_SIZE ||
		start_x >= board_size ||
		start_y >= board_size) {
		printf("invalid input!\n");
		return 1;
	}
	
	/* initialize the board */
	init(board_size);
	
	/* run the algorithm */
	if(!knight_next_move(start_x, start_y, 1, board_size))
         printf("solution not found!\n");
         
	return 0;
}
