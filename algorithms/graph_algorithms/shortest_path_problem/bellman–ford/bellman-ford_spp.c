/*******************************************************************************
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19 
 *******************************************************************************/

/**
 * @file   bellman-ford_spp.cpp
 * @author Ivan Filipov
 * @date   01.2019
 * @brief  Finding the shortest path from a starting vertex to all others, using Bellman-Ford's algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
 * @note Written in plain C.
 *
 * Difference from Dijkstra - edges can also have negative weights.
 * Also finds out if the graph contains negative cycle.
 */

#include <stdio.h>   // printf(), putchar()
#include <stdbool.h> // bool

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
void print_paths(int v_begin, int dist_vector[]) {
    
    printf("\nfrom %c to:\n", 'A' + v_begin);
    
	for (int i = 0; i < SIZE; i++) {
		if (v_begin == i) continue;
	
		printf("\t%c ", 'A' + i);
		
		if (dist_vector[i] == MAX)
			printf("no such path!\n");
		else
		    printf(" weight %d\n", dist_vector[i]);
	}
}

/**
 * @brief Checks for negative cycle in the output from Bellman-Ford's algo.
 * @param[in] dist_vector: distances between vertices, as outputted from the algo.
 * @retval true if there is a negative cycle
 *
 * If there are two edges (i and j) and the distance to i
 * is greater from the distance to j plus the edge between them
 * we can conclude that the graph contains a negative cycle.
 */
bool find_negative_cycle(int dist_vector[]) {
	
	for (int i = 0; i < SIZE; i++)
		for (int j = i; j < SIZE; j++) {
			if (graph[j][i] == MAX || dist_vector[j] == MAX) continue;
			if (dist_vector[i] > dist_vector[j] + graph[j][i])
				return true;
		}
		
	return false;
}

/**
 * @brief Runs Bellman-Ford's algorithm in the given graph.
 * @param[in] v_begin: staring vertex
 *
 * @note outputs in an inner scoped array of distances
 */
void ford_shortest_paths(int v_begin) {
	// distance to each vertex -> the algorithm's output
	int dist_vector[SIZE]; 
	// initialize distances
	for (int i = 0; i < SIZE; i++)
		dist_vector[i] = graph[v_begin][i];
	
	 // for each vertex between i and j 
	for (size_t k = 0; k <= SIZE / 2; k++)
		for (size_t i = 0; i < SIZE; i++) 
			for (size_t j = 0; j < SIZE; j++) {
				// don optimize path from vertex to itself
				if (i == j) continue;
				// if there is no edge from i to k or from k to j skip this step
				if (graph[j][i] == MAX || dist_vector[j] == MAX) continue;
				 // try to optimize the distance
				if (dist_vector[i] > dist_vector[j] + graph[j][i])
					dist_vector[i] = dist_vector[j] + graph[j][i];
		}
	
	// check the output for negative cycle
	if (find_negative_cycle(dist_vector))
		printf("\nthe given graph contains a negative loop!\n");
	else // if there is no such cycle, output the shortest paths
		print_paths(v_begin, dist_vector);
}

int main() {
	
	/* run the algorithm from 'B' */
	int v_begin = 1;
	ford_shortest_paths(v_begin);
	
	/* run the algorithm from 'E' */
	v_begin = 4; // 'E'
	ford_shortest_paths(v_begin);
	
	/* change the graph a bit, and run the algorithm again */
	printf("\nmodifying the graph to create a negative loop...\n");
	// for better understanding see the graph's visual representation
	graph['D' - 'A']['C' - 'A'] = -11; 
	ford_shortest_paths(v_begin);

	return 0;
}
