/*
 * Simply traversing a maze using depth first search strategy.
 * Searching a path between two cells - from (0, 0) to (ROWS - 1, COLS - 1). Written in plain C.
 * Nicely animated in the console.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <stdio.h>   // printf()
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()
#include <stdbool.h> // bool 

// some constants for easier cell recognition
#define LAVA   -2 // lava
#define UNVGND -1 // unvisited ground
#define VGND    4 // visited by not in the path
#define REACHED_TARGET 5
// some characters for beautiful output
#define LAVA_SYM '#'
#define FINISH_SYM '$'
#define UNVGND_SYM ' '
#define VGND_SYM   '-'

// the maze itself
#define ROWS 4
#define COLS 4
int maze[ROWS][COLS];

// directions
#define N_DIR 4 // number of directions
// difference by x and y
int diff_x[] = { 0, 1,  0, -1 };
int diff_y[] = { 1, 0, -1,  0 };
char dir_sym[] = { '>', 'v', '<', '^' };

// initialize maze's cells
// with 66% change -> available cell (UNVGND)
// with 33% change -> unavailable cell (LAVA)
void init_maze() {

	for (size_t i = 0; i < ROWS; i++)
		for (size_t j = 0; j < COLS; j++)
			maze[i][j] = ((rand() % 30) < 20) - 2; // results in -2 or -1
	// mark the target reachable
	maze[ROWS - 1][COLS - 1] = UNVGND;
}

// simple delay function in C - style
// used to set delay between printing each step
void delay(unsigned secs) {

	time_t ret_time = time(NULL) + secs;   

	while (time(NULL) < ret_time)
		;               
}

void print_maze() {

	for (size_t i = 0; i < ROWS; i++) {
		for (size_t j = 0; j < COLS; j++) {
			switch (maze[i][j]) {
			case LAVA: 
				printf("%2c", LAVA_SYM); break;
			case REACHED_TARGET:
				printf("%2c", FINISH_SYM); break;
			case UNVGND:
				printf("%2c", UNVGND_SYM); break;
			case VGND:
				printf("%2c", VGND_SYM); break;
			default: printf("%2c", dir_sym[maze[i][j]]);
			}
		}
		putchar('\n');
	}
	printf("\n\n\n");
	delay(1);
}

// checks if a point is in the maze or outside
bool is_valid(int x, int y){

	if (x < 0 || y < 0)
		return false;

	if (x >= ROWS || y >= COLS)
		return false;

	return true;
}

bool dfs_find(size_t x , size_t y, int dir) {

	// checks if we have reached the target
	if ((x == ROWS - 1) && (y == COLS - 1)) {
		maze[x][y] = REACHED_TARGET;
		print_maze();
		return true;
	}
	// else marking this cell as visited
	// from the direction passed
	maze[x][y] = dir;
	// current maze look
	print_maze();
	// where to make the next step
	int new_x, new_y;
	// trying all directions
	for (int i = 0; i < N_DIR; i++) {
		// calc next step
		new_x = x + diff_x[i];
		new_y = y + diff_y[i];
		// if we can get there
		if (is_valid(new_x, new_y) && 
			((maze[new_x][new_y] == UNVGND) ||
			(maze[new_x][new_y]  == REACHED_TARGET))) {
			// try to find path from there
			if (dfs_find(new_x, new_y, i))
				return true;
			else { // if this step wasn't winning cut that path
				maze[new_x][new_y] = VGND;
				print_maze();
			}
		}
	}
	
	return false;
}


int main() {

	/* initialize the random generator */
	srand(time(NULL));
	/* create the maze */
	init_maze();
	/* output the starting maze */
	print_maze();
	/* run the algorithm */
	if (dfs_find(0, 0, 0))
		printf("there is a path !\n");
	else
		printf("there isn't a path !\n");

	return 0;
}
