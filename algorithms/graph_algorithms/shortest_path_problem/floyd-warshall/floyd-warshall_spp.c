/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   floyd-warshall_spp.cpp
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Finding the shortest path from each vertex to all others, using Floyd-Warshall's algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
 * @note Written in plain C.
 *
 * Difference from Dijkstra - edges can also have negative weights, solves all-to-all (SPP).
 */

#include <stdio.h> // printf(), putchar()

/// graph matrix size
#define SIZE 6 
/// "no path" constant, should be maximum INT_MAX / 2
#define MAX 1000
/// helper marco for finding minimum of two numbers
#define min(x, y) ((x) < (y)) ? (x) : (y)

/// the graph is represented as weighing matrix
int graph[SIZE][SIZE] = {
// vertex "to" :
//     A    B    C    D    E    F     // vertex "from" :
	{ MAX, MAX,   6,   2, MAX, MAX }, // A
	{ MAX, MAX, MAX,  -7, MAX, MAX }, // B
	{ MAX,   1, MAX, MAX, MAX, MAX }, // C
	{ MAX, MAX,  11, MAX, MAX, MAX }, // D
	{  15, MAX,  10, MAX, MAX,  -3 }, // E
	{ MAX,   5, MAX, MAX, MAX, MAX }  // F
};

/// simply outputs info about all found paths
void print_paths() {
    
    printf("\nall paths with their weights:\n");
	for (size_t i = 0; i < SIZE; i++) {
		printf("from %c ", 'A' + i);

		for (size_t j = 0; j < SIZE; j++)
			if (graph[i][j] != MAX)
				printf("[ to %c : %d ]", 'A' + j, graph[i][j]);

		putchar('\n');
	}
}

/**
 * @brief Runs Floyd-Warshall'salgorithm in the given graph.
 *
 * @note Outputs the path's weights into the same weighting matrix
 * @note Time complexity : O(n^3)
 */
void floyd_shortest_paths() {

	for (size_t k = 0; k < SIZE; k++)           // for each vertex
		for (size_t i = 0; i < SIZE; i++)       // between i
			for (size_t j = 0; j < SIZE; j++) { // and j
				// don't optimize path from vertex to itself
				if (i == j) continue;
				// if there is no edge from i to k or from k to j skip this step
				if (graph[i][k] == MAX || graph[k][j] == MAX) continue;
				// remember the old value, debug purpose only
				int old = graph[i][j];
				// try to optimize the path
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
				// debug only
				if (old != graph[i][j]) {
					printf("optimizing path from %c to %c through %c (%d->%d)\n", 
						   'A' + i, 'A' + j, 'A' + k, old, graph[i][j]);
				}
			}
}

int main() {
	
	/* run the algorithm */
	floyd_shortest_paths();
	
	/* print the info about all paths */
	print_paths();

	return 0;
}
