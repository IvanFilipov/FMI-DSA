/*
 * Simply traversing a maze using breadth first search strategy.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <cstdio> // std::printf(), std::putchar
#include <cstdlib>// std::exit() 
#include <ctime>  // std::time()
#include <random> // std::rand(), std::srand()
#include <queue>  // std::queue
#include <array>  // std::array

// can't go there
const int UNREACHABLE = -1;
// can go there
const int REACHABLE = 0;
// every other int -> visited

// matrix sizes
const size_t MAXN = 8;
const size_t MAXM = 8;
// the maze itself
int maze[MAXN][MAXM];
// each point is represented by two indexes
using point = std::pair<size_t, size_t>;
// each direction we can have
using directions = std::array<point, 4>;
directions dirs = {
	std::make_pair( 0,  1), // left
	std::make_pair( 0, -1), // right
	std::make_pair( 1,  0), // up
	std::make_pair(-1,  0)  // down
};

// simply prints the maze contain
void print_maze() {

	for (size_t i = 0; i < MAXN; i++) {
		for (size_t j = 0; j < MAXM; j++)
			std::printf("%3d", maze[i][j]);
		std::putchar('\n');
	}
	std::printf("\n\n\n");
}

// initialize maze's cells
// with 66% change -> reachable cell
// with 33% change -> unreachable cell
void init_maze() {

	for (size_t i = 0; i < MAXN; i++)
		for (size_t j = 0; j < MAXM; j++)
           maze[i][j] = ((rand() % 30 ) < 20) - 1;
}
// checks if a point is in the maze or outside
bool is_valid(int x, int y) {

	if (x < 0 || y < 0)
		return false;
		
	if (x > (int)MAXN || y > (int)MAXM)
		return false;

	return true;
}
// runs BFS from starting point "start"
void bfs_traversal(const point& start) {
	// check if the starting point is reachable
	if (maze[start.first][start.second] == UNREACHABLE) {
		std::printf("can't start form this point...\n");
		std::exit(0);
	}
	// marking the first step
	maze[start.first][start.second] = 1;
	// the "wave" of the algorithm
	std::queue<point> wave;
	// adding the first vertex
	wave.push(start);
	// where is the next step
	int new_x, new_y;
	// until the wave is not empty
	while (!wave.empty()) {
		// for each direction
		for (const point& dir : dirs) {
			// get the step indexes
			new_x = wave.front().first + dir.first;
			new_y = wave.front().second + dir.second;
			// if we can go there
			if (is_valid(new_x, new_y) && maze[new_x][new_y] == REACHABLE) {
				// mark the step count
				maze[new_x][new_y] += 
					maze[wave.front().first][wave.front().second] + 1;
				// add the new vertex into the wave
				wave.push(std::make_pair(new_x, new_y));
			}
		}
		// remove the current vertex
		wave.pop();
	}
}

int main() {
	
	/* initialize the random generator */
	std::srand(std::time(nullptr));
	/* create the maze */
	init_maze();
	/* output the starting maze */
	std::printf("starting maze looks like :\n\n");
	print_maze();
	/* create a random start point */
	point start(rand() % MAXN, rand() % MAXM);
	std::printf("starting from (%lu, %lu) :\n", start.first, start.second);
	/* run the algorithm */
	bfs_traversal(start);
	/* output the result */
	std::printf("after traversing all possible vertices from the graph\n\n");
	print_maze();

	return 0;
}
